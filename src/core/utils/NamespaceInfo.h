#pragma once

#include <string>
#include <optional>

class NamespaceInfo
{
private:
    std::optional<std::string> m_name;
    std::optional<std::string> m_file;
public:
  NamespaceInfo(std::string name){
        m_name = name;
    }

  std::optional<std::string> getName(void) {
        return m_name;
    }

  std::optional<std::string> getFile(void) {
        return m_file;
    }

  void setFile(std::string file) {
        m_file = file;
    }
};
