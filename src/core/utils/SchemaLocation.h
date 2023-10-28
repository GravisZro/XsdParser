#ifndef SCHEMALOCATION_H
#define SCHEMALOCATION_H

#include <iostream>

#include <set>
#include <string>
#include <memory>
#include <initializer_list>

class SchemaLocation : public std::enable_shared_from_this<SchemaLocation>
{
public:
  SchemaLocation(void) = default;

  SchemaLocation(std::string location) { operator=(location); }
  SchemaLocation(std::set<std::string> locations) { insert(locations); }

  void setParentPaths(const SchemaLocation& parent);


  bool contains(const std::string& location) const { return operator ==(location); }

  bool operator ==(const std::string& location) const { return m_data.contains(location); }
  bool operator  <(const std::string& location) const;
  void operator =(const std::string& location);

  bool operator ==(const SchemaLocation& other) const;
  bool operator !=(const SchemaLocation& other) const { return !operator ==(other); }
  bool operator  <(const SchemaLocation& other) const;

  operator bool (void) const { return !m_data.empty(); }


  void insert(std::set<std::string> locations);
  void insert(const std::string& location);
  const std::set<std::string>& data(void) const { return m_data; }

  void reset(void);
private:
  std::set<std::string> m_parentPaths;
  std::set<std::string> m_data;
};

#endif // SCHEMALOCATION_H
