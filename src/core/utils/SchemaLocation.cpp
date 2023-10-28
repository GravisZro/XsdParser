#include "SchemaLocation.h"

#include <cassert>
#include <algorithm>
#include <filesystem>

static bool is_URL(const std::string& target)
{
  return target.starts_with("https://") || target.starts_with("http://");
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
    if(std::filesystem::path location(path); !location.parent_path().empty())
      m_parentPaths.insert(location.parent_path());
  }
}


bool SchemaLocation::operator <(const std::string& location) const
{
  if(is_URL(location))
  {
    for(const std::string& entry : m_data)
      if(is_URL(entry))
        return location < entry;
  }
  else if(std::filesystem::path(location).is_absolute())
  {
    for(const std::string& entry : m_data)
      if(std::filesystem::path(entry).is_absolute())
        return location < entry;
  }
  else if(std::filesystem::path(location).is_relative())
  {
    for(const std::string& entry : m_data)
      if(std::filesystem::path(entry).is_relative())
        return location < entry;
  }

  return false;
}

void SchemaLocation::operator =(const std::string& location)
{
  m_data.clear();
  if(!location.contains(' '))
    insert(location);
  else
  {
    for(std::size_t pos = 0, last = 0;
        pos = location.find_first_of(' ', pos),
        pos != std::string::npos;
        last = pos, ++pos)
      if(last + 1 < pos)
        insert(location.substr(last, pos));
  }
}

bool SchemaLocation::operator ==(const SchemaLocation& other) const
{
  for(const std::string& location : other.m_data)
  {
    assert(!is_URL(location));
    if((std::filesystem::path(location).is_absolute() || is_URL(location)) && // only bother with absolute paths and URLs
       m_data.contains(location))
      return true;
  }
  return false;
}

bool SchemaLocation::operator <(const SchemaLocation& other) const
{
  for(const std::string& location : other.m_data)
    if(std::filesystem::path(location).is_absolute())
      return operator <(location);

  for(const std::string& location : other.m_data)
    if(std::filesystem::path(location).is_relative())
      return operator <(location);

  for(const std::string& location : other.m_data)
    if(is_URL(location))
      return operator <(location);

  return false;
}

void SchemaLocation::insert(std::set<std::string> locations)
{
  for(auto& location : locations)
    insert(location);
}

void SchemaLocation::insert(const std::string& location)
{
  m_data.insert(location); // insert original reference name (could be relative filename or absolute)
  m_data.insert(std::filesystem::path(location).filename()); // insert filename (or do nothing if it's a duplicate)
  if(!is_URL(location) && !std::filesystem::path(location).is_absolute()) // location is a relative filename
  {
    for(const auto& parent_path : m_parentPaths)
    {
      auto locationpath = std::filesystem::path(parent_path) / location; // build (then verify) absolute filepath
      if(std::filesystem::exists(locationpath))
        m_data.insert(std::filesystem::canonical(locationpath)); // insert absolute filepath
    }
  }
}
