#ifndef SCHEMALOCATION_H
#define SCHEMALOCATION_H

#include <set>
#include <string>
#include <memory>

class SchemaLocation : public std::enable_shared_from_this<SchemaLocation>
{
public:
  SchemaLocation(std::string entry)
    : m_data({ entry }) { }

  template<typename... Args>
  SchemaLocation(Args... args)
    : m_data(args...) { }

  void setParent(SchemaLocation* parent) { m_parent = parent; }

  bool contains(const std::string& entry) const;
  void operator =(const std::string& entry);

  bool operator ==(const SchemaLocation& other) const;
  bool operator !=(const SchemaLocation& other) const { return !operator ==(other); }
  bool operator  <(const SchemaLocation& other) const { return !operator ==(other); }

  bool operator ==(const std::string& entry) const { return contains(entry); }
  bool operator !=(const std::string& entry) const { return !operator ==(entry); }

  operator bool (void) const { return !m_data.empty(); }


  void insert(const std::string& entry);
  const std::set<std::string>& data(void) const { return m_data; }
private:
  mutable SchemaLocation* m_parent = nullptr;
  mutable std::set<std::string> m_data;
};

#endif // SCHEMALOCATION_H
