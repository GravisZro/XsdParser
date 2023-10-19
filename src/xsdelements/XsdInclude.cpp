#include "XsdInclude.h"

#include <ranges>


XsdInclude::XsdInclude(std::shared_ptr<XsdParserCore> parser, StringMap attributesMap, VisitorFunctionReference visitorFunction)
  : XsdAnnotatedElements(parser, attributesMap, visitorFunction)
{
  if(attributesMap.contains(*SCHEMA_LOCATION))
  {
    for(auto location : std::ranges::views::split(attributesMap.at(*SCHEMA_LOCATION), '\n'))
      m_schemaLocation.insert(location.data());
    parser->addLocationToParse(m_schemaLocation);
  }
}
