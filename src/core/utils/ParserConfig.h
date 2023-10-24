#pragma once

#include "ConfigEntryData.h"

struct ParserConfig
{
  virtual ~ParserConfig(void) = default;
  virtual const StringMap getXsdTypesToCpp(void);
  virtual const std::map<std::string_view, ConfigEntryData> getParseMappers(void);
};
