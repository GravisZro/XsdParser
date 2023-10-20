#include "XsdAll.h"

#include <core/XsdParserCore.h>
#include <core/utils/ParseData.h>
#include <xsdelements/elementswrapper/ReferenceBase.h>
#include <xsdelements/elementswrapper/UnsolvedReference.h>
#include <xsdelements/visitors/XsdAbstractElementVisitor.h>
#include <xsdelements/AttributeValidations.h>




XsdAll::XsdAll(std::shared_ptr<XsdParserCore> parser,
       StringMap attributesMap,
       VisitorFunctionReference visitorFunction)
  : XsdMultipleElements(parser, attributesMap, visitorFunction),
    m_minOccurs(1),
    m_maxOccurs(1)
{
  if(attributesMap.contains(*MIN_OCCURS_TAG))
    m_minOccurs = AttributeValidations::validateNonNegativeInteger(*XSD_TAG, *MIN_OCCURS_TAG, attributesMap.at(*MIN_OCCURS_TAG));
  if(attributesMap.contains(*MAX_OCCURS_TAG))
    m_maxOccurs = AttributeValidations::validateNonNegativeInteger(*XSD_TAG, *MAX_OCCURS_TAG, attributesMap.at(*MAX_OCCURS_TAG));
}


void XsdAll::accept(std::shared_ptr<XsdAbstractElementVisitor> visitorParam)
{
    XsdMultipleElements::accept(visitorParam);
    visitorParam->visit(nondeleted_ptr<XsdAll>(this));
}


std::shared_ptr<ReferenceBase> XsdAll::parse(ParseData parseData)
{
  return xsdParseSkeleton(parseData.node, std::static_pointer_cast<XsdAbstractElement>(std::make_shared<XsdAll>(parseData.parserInstance, XsdAbstractElement::getAttributesMap(parseData.node), parseData.visitorFunction)));
}



/**
 * Performs a copy of the current object for replacing purposes. The cloned objects are used to replace
 * {@link UnsolvedReference} objects in the reference solving process.
 * @param placeHolderAttributes The additional attributes to add to the clone.
 * @return A copy of the object from which is called upon.
 */
std::shared_ptr<XsdAll> XsdAll::clone(StringMap placeHolderAttributes)
{
    placeHolderAttributes.merge(m_attributesMap);

    auto elementCopy = std::make_shared<XsdAll>(getParser(), placeHolderAttributes, m_visitorFunction);

    for(auto& element : getElements())
        elementCopy->m_elements.push_back(ReferenceBase::clone(getParser(), element, elementCopy));

    elementCopy->m_cloneOf = nondeleted_ptr<XsdAbstractElement>(this);
    elementCopy->setParent(nullptr);

    return elementCopy;
}
