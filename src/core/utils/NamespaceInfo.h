#pragma once

#include <core/utils/SchemaLocation.h>
#include <core/utils/CommonTypes.h>

class NamespaceInfo
{
private:
    std::optional<std::string> m_name;
    SchemaLocation m_schemaLocation;
public:
  NamespaceInfo(std::string name)
    : m_name(name) { }

  std::optional<std::string> getName(void) const { return m_name; }
  SchemaLocation getLocation(void) const { return m_schemaLocation; }

  void setLocation(SchemaLocation file) { m_schemaLocation = file; }
};
