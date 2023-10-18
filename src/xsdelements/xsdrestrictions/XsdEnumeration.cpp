#include "XsdEnumeration.h"

#include <xsdelements/visitors/XsdAbstractElementVisitor.h>

XsdEnumeration::XsdEnumeration(std::shared_ptr<XsdParserCore> parser,
               StringMap elementFieldsMapParam,
               VisitorFunctionReference visitorFunction)
      : XsdStringRestrictions(parser, elementFieldsMapParam, visitorFunction)
{
}

void XsdEnumeration::accept(std::shared_ptr<XsdAbstractElementVisitor> xsdAbstractElementVisitor)
{
  XsdStringRestrictions::accept(xsdAbstractElementVisitor);
  xsdAbstractElementVisitor->visit(std::shared_ptr<XsdEnumeration>(this));
}

/**
 * Performs a copy of the current object for replacing purposes. The cloned objects are used to replace
 * {@link UnsolvedReference} objects in the reference solving process.
 * @param placeHolderAttributes The additional attributes to add to the clone.
 * @return A copy of the object from which is called upon.
 */
std::shared_ptr<XsdEnumeration> XsdEnumeration::clone(StringMap placeHolderAttributes)
{
  placeHolderAttributes.merge(m_attributesMap);
  auto elementCopy = std::make_shared<XsdEnumeration>(getParser(), placeHolderAttributes, m_visitorFunction);
  elementCopy->setParent(nullptr);
  return elementCopy;
}

std::shared_ptr<ReferenceBase> XsdEnumeration::parse(ParseData parseData)
{
  return xsdParseSkeleton(parseData.node, std::shared_ptr<XsdAbstractElement>(
                            new XsdEnumeration(parseData.parserInstance,
                                               XsdAbstractElement::getAttributesMap(parseData.node),
                                               parseData.visitorFunction)));
}
