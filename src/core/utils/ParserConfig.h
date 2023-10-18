#pragma once

#include <map>
#include <string>
#include "ConfigEntryData.h"

class ParserConfig
{
public:
  virtual const StringMap getXsdTypesToJava(void);
  virtual const std::map<std::string, ConfigEntryData> getParseMappers(void);
};
