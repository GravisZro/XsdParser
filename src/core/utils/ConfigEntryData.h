#pragma once

#include <core/utils/CommonTypes.h>

struct ConfigEntryData
{
  ParserFunctionType parserFunction = nullptr;
  VisitorFunctionType visitorFunction = nullptr;
};
