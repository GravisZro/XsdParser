#pragma once

#include <core/utils/CommonTypes.h>

#ifdef DEBUG
struct ConfigEntryData
{
  std::string_view parserForType; // Debug info
  ParserFunctionType parserFunction = nullptr;
  std::string_view visitorForType; // Debug info
  VisitorFunctionType visitorFunction = nullptr;
};
#else
struct ConfigEntryData
{
  ParserFunctionType parserFunction = nullptr;
  VisitorFunctionType visitorFunction = nullptr;
};
#endif
