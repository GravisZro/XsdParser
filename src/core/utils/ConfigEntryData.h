#pragma once

#include <core/utils/CommonTypes.h>

class ParseData;
class ReferenceBase;

struct ConfigEntryData
{
  std::function<std::shared_ptr<ReferenceBase>(ParseData)> parserFunction;
  VisitorFunctionReference visitorFunction;
};
