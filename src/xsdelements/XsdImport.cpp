#include "XsdImport.h"

#include <core/XsdParserCore.h>
#include <core/utils/StringOperations.h>

XsdImport::XsdImport(std::shared_ptr<XsdParserCore> parser,
                     StringMap attributesMap,
                     VisitorFunctionType visitorFunction,
                     std::shared_ptr<XsdAbstractElement> parent)
    : XsdAnnotatedElements(parser, attributesMap, visitorFunction, parent)
{
  if(haveAttribute(NAMESPACE))
    m_namespace = getAttribute(NAMESPACE);

  if(haveAttribute(SCHEMA_LOCATION))
  {
    m_schemaLocation = getAttribute(SCHEMA_LOCATION);
    getParser()->addLocationToParse(m_schemaLocation);
  }
}

