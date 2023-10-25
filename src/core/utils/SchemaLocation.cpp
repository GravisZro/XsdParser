#include "SchemaLocation.h"

#include <algorithm>
#include <filesystem>

static bool is_URL(const std::string& target)
{
  return target.starts_with("https://") || target.starts_with("http://");
}


SchemaLocation::SchemaLocation(std::initializer_list<std::string> entries)
{
  for(auto& entry : entries)
    insert(entry);
}

void SchemaLocation::reset(void)
{
  m_parentPaths.clear();
  m_data.clear();
}

void SchemaLocation::setParentPaths(const SchemaLocation& parent)
{
  reset();
  for(const std::string& path : parent.data())
  {
    if(std::filesystem::path entry(path); !entry.parent_path().empty())
      m_parentPaths.insert(entry.parent_path());
  }
}


bool SchemaLocation::contains(const std::string& entry) const
{
  return m_data.contains(entry);
}

void SchemaLocation::operator =(const std::string& entry)
{
  m_data.clear();
  if(!entry.contains(' '))
    insert(entry);
  else
  {
    for(std::size_t pos = 0, last = 0;
        pos = entry.find_first_of(' ', pos),
        pos != std::string::npos;
        last = pos, ++pos)
      if(last + 1 < pos)
        insert(entry.substr(last, pos));
  }
}

bool SchemaLocation::operator ==(const SchemaLocation& other) const
{
  for(const std::string& location : other.m_data)
    if((std::filesystem::path(location).is_absolute() || is_URL(location)) && // only bother with absolute paths and URLs
       m_data.contains(location))
      return true;
  return false;
}

void SchemaLocation::insert(const std::string& entry)
{
  m_data.insert(entry); // insert original reference name (could be relative filename or absolute)
  m_data.insert(std::filesystem::path(entry).filename()); // insert filename (or do nothing if it's a duplicate)
  if(!is_URL(entry) && !std::filesystem::path(entry).is_absolute()) // entry is a relative filename
  {
    for(const auto& parent_path : m_parentPaths)
    {
      auto entrypath = std::filesystem::path(parent_path) / entry; // build (then verify) absolute filepath
      if(std::filesystem::exists(entrypath))
        m_data.insert(std::filesystem::canonical(entrypath)); // insert absolute filepath
    }
  }
}
