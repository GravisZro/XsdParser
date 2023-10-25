#ifndef SCHEMALOCATION_H
#define SCHEMALOCATION_H

#include <set>
#include <string>
#include <memory>
#include <initializer_list>

class SchemaLocation : public std::enable_shared_from_this<SchemaLocation>
{
public:
  SchemaLocation(void) = default;

  SchemaLocation(std::string entry) { operator=(entry); }
  SchemaLocation(std::initializer_list<std::string> entries);

  void setParentPaths(const SchemaLocation& parent);

  bool contains(const std::string& entry) const;
  void operator =(const std::string& entry);

  bool operator ==(const SchemaLocation& other) const;
  bool operator !=(const SchemaLocation& other) const { return !operator ==(other); }
  bool operator  <(const SchemaLocation& other) const { return !operator ==(other); }

  operator bool (void) const { return !m_data.empty(); }


  void insert(const std::string& entry);
  const std::set<std::string>& data(void) const { return m_data; }

  void reset(void);
private:
  mutable std::set<std::string> m_parentPaths;
  mutable std::set<std::string> m_data;
};

#endif // SCHEMALOCATION_H
