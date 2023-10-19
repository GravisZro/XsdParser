#include "XsdImport.h"

#include <core/XsdParserCore.h>
#include <core/utils/CommonOperations.h>

XsdImport::XsdImport(std::shared_ptr<XsdParserCore> parser, StringMap attributesMap, VisitorFunctionReference visitorFunction)
    : XsdAnnotatedElements(parser, attributesMap, visitorFunction)
{
  if(attributesMap.contains(*NAMESPACE))
    m_namespace = attributesMap.at(*NAMESPACE);

  if(attributesMap.contains(*SCHEMA_LOCATION))
  {
    m_schemaLocation = attributesMap.at(*SCHEMA_LOCATION);
    getParser()->addLocationToParse(m_schemaLocation);
  }
}


std::shared_ptr<ReferenceBase> XsdImport::parse(ParseData parseData)
{
  return xsdParseSkeleton(parseData.node, std::static_pointer_cast<XsdAbstractElement>(
                            std::make_shared<XsdImport>(parseData.parserInstance,
                                                        XsdAbstractElement::getAttributesMap(parseData.node),
                                                        parseData.visitorFunction)));
}
