#include "XsdInclude.h"

#include <ranges>


XsdInclude::XsdInclude(std::shared_ptr<XsdParserCore> parser,
                       StringMap attributesMap,
                       VisitorFunctionType visitorFunction,
                       std::shared_ptr<XsdAbstractElement> parent)
  : XsdAnnotatedElements(parser, attributesMap, visitorFunction, parent)
{
  if(haveAttribute(SCHEMA_LOCATION))
  {
    for(auto location : std::ranges::views::split(getAttribute(SCHEMA_LOCATION), '\n'))
      m_schemaLocation.insert(location.data());
    parser->addLocationToParse(m_schemaLocation);
  }
}
