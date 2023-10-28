#include "XsdImport.h"

#include <core/XsdParserCore.h>
#include <core/utils/StringOperations.h>

void XsdImport::initialize(void)
{
  XsdAnnotatedElements::initialize();
  m_namespace.reset();
  m_schemaLocation.clear();

  if(haveAttribute(NAMESPACE))
    m_namespace = getAttribute(NAMESPACE);

  if(haveAttribute(SCHEMA_LOCATION))
  {
    m_schemaLocation = getAttribute(SCHEMA_LOCATION);
    getParser()->addLocationToParse(m_schemaLocation);
  }
}

