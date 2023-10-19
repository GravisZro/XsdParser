#pragma once

#include <map>
#include <string>
#include "ConfigEntryData.h"

class ParserConfig
{
public:
  virtual const StringMap getXsdTypesToJava(void);
  virtual const std::map<std::string_view, ConfigEntryData> getParseMappers(void);
};
