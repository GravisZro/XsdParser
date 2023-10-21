#include "XsdImport.h"

#include <core/XsdParserCore.h>
#include <core/utils/CommonOperations.h>

XsdImport::XsdImport(std::shared_ptr<XsdParserCore> parser,
                     StringMap attributesMap,
                     VisitorFunctionReference visitorFunction,
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


std::shared_ptr<ReferenceBase> XsdImport::parse(ParseData parseData)
{
  return xsdParseSkeleton(parseData.node,
                          std::static_pointer_cast<XsdAbstractElement>(
                            create<XsdImport>(parseData.parserInstance,
                                              getAttributesMap(parseData.node),
                                              parseData.visitorFunction,
                                              nullptr)));
}
