#include "XsdInclude.h"

XsdInclude::XsdInclude(std::shared_ptr<XsdParserCore> parser,
                       StringMap attributesMap,
                       VisitorFunctionType visitorFunction,
                       std::shared_ptr<XsdAbstractElement> parent)
  : XsdAnnotatedElements(parser, attributesMap, visitorFunction, parent)
{
  if(haveAttribute(SCHEMA_LOCATION))
  {
    m_schemaLocation = getAttribute(SCHEMA_LOCATION);
    parser->addLocationToParse(m_schemaLocation);
  }
}
