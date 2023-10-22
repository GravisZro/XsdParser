#pragma once

#include <core/utils/SchemaLocation.h>
#include <core/utils/CommonTypes.h>

class NamespaceInfo
{
private:
    std::optional<std::string> m_name;
    SchemaLocation m_file;
public:
  NamespaceInfo(std::string name)
    : m_name(name) { }

  std::optional<std::string> getName(void) const { return m_name; }
  SchemaLocation getFile(void) const { return m_file; }

  void setFile(SchemaLocation file) { m_file = file; }
  void setFile(std::string file) { m_file = file; }
};
