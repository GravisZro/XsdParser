#pragma once

#include <core/utils/CommonTypes.h>
#include <pugixml.hpp>

class XsdParserCore;

struct ParseData
{
  std::shared_ptr<XsdParserCore> parserInstance;
  pugi::xml_node node;
  VisitorFunctionType visitorFunction;
};
