#include "XsdInclude.h"

#include <core/XsdParserCore.h>

void XsdInclude::initialize(void)
{
  XsdAnnotatedElements::initialize();
  m_schemaLocation.reset();
  if(haveAttribute(SCHEMA_LOCATION))
  {
    m_schemaLocation = getAttribute(SCHEMA_LOCATION);
    getParser()->addLocationToParse(m_schemaLocation);
  }
}
