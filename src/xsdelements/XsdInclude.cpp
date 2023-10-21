#include "XsdInclude.h"

#include <ranges>


XsdInclude::XsdInclude(std::shared_ptr<XsdParserCore> parser, StringMap attributesMap, VisitorFunctionReference visitorFunction)
  : XsdAnnotatedElements(parser, attributesMap, visitorFunction)
{
  if(haveAttribute(SCHEMA_LOCATION))
  {
    for(auto location : std::ranges::views::split(getAttribute(SCHEMA_LOCATION), '\n'))
      m_schemaLocation.insert(location.data());
    parser->addLocationToParse(m_schemaLocation);
  }
}
