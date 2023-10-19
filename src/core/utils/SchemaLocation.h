#ifndef SCHEMALOCATION_H
#define SCHEMALOCATION_H

#include <set>
#include <string>

class SchemaLocation : public std::set<std::string>
{
public:
  SchemaLocation(std::string entry)
    : std::set<std::string>({ entry }) { }

  template<typename... Args>
  SchemaLocation(Args... args)
    : std::set<std::string>(args...) { }

  bool operator ==(const SchemaLocation& other);
  bool operator ==(const std::string& entry) const { return contains(entry); }
  operator bool (void) const { return !empty(); }
};

#endif // SCHEMALOCATION_H
