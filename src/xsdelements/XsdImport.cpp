#include "XsdImport.h"

#include <core/XsdParserCore.h>
#include <core/utils/StringOperations.h>

XsdImport::XsdImport(StringMap attributesMap,
                     VisitorFunctionType visitorFunction,
                     XsdAbstractElement* parent)
  : XsdAnnotatedElements(attributesMap, visitorFunction, parent)
{
  if(hasAttribute(NAMESPACE))
    m_namespace = getAttribute(NAMESPACE);

  if(hasAttribute(SCHEMA_LOCATION))
  {
    m_schemaLocation = getAttribute(SCHEMA_LOCATION);
    getParser()->addLocationToParse(m_schemaLocation);
  }
}

