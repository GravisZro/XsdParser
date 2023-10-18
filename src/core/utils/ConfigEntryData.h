#pragma once

#include <core/utils/CommonTypes.h>

class ParseData;
class ReferenceBase;

struct ConfigEntryData
{
  std::function<ReferenceBase(ParseData)> parserFunction;
  VisitorFunctionReference visitorFunction;
};
