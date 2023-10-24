#include "SchemaLocation.h"

#include <algorithm>
#include <filesystem>

static bool is_URL(const std::string& target)
{
  return target.starts_with("https://") || target.starts_with("http://");
}

bool SchemaLocation::contains(const std::string& entry) const
{
  if(m_data.contains(entry))
    return true;

  if(is_URL(entry))
    return false;

  if(m_parent == nullptr)
    return false;

  for(auto& parent : m_parent->data())
    if(auto entrypath = std::filesystem::absolute(std::filesystem::path(parent).parent_path() / entry);
      m_data.contains(entrypath))
    return true;

  return false;
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
  if(std::any_of(std::begin(other.m_data),
                     std::end(other.m_data),
                     [this](const std::string& entry)
                { return operator ==(entry); }))
  {
    if(m_parent == nullptr && other.m_parent != nullptr)
      m_parent = other.m_parent;
    else if(m_parent != nullptr && other.m_parent == nullptr)
      other.m_parent = m_parent; // rule breaker! (mutable)
    m_data.merge(static_cast<std::set<std::string>>(other.m_data));
    return true;
  }
  return false;
}

void SchemaLocation::insert(const std::string& entry)
{
  m_data.insert(entry); // insert original reference name (could be relative filename or absolute)
  m_data.insert(std::filesystem::path(entry).filename()); // insert filename (or do nothing if it's a duplicate)
  if(!is_URL(entry) && !std::filesystem::path(entry).is_absolute()) // entry is a relative filename
  {
    auto entrypath = std::filesystem::current_path() / entry; // build (then verify) absolute filepath
    if(!std::filesystem::exists(entrypath))
      throw std::runtime_error("unable to location file");
    m_data.insert(std::filesystem::canonical(entrypath)); // insert absolute filepath
  }
}
