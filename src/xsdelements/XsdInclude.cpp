#include "XsdInclude.h"

#include <core/XsdParserCore.h>

XsdInclude::XsdInclude(StringMap attributesMap,
                       VisitorFunctionType visitorFunction,
                       XsdAbstractElement* parent)
  : XsdAnnotatedElements(attributesMap, visitorFunction, parent)
{
  if(haveAttribute(SCHEMA_LOCATION))
  {
    m_schemaLocation = getAttribute(SCHEMA_LOCATION);
    getParser()->addLocationToParse(m_schemaLocation);
  }
}
