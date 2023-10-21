#include "XsdAll.h"

#include <core/XsdParserCore.h>
#include <core/utils/ParseData.h>
#include <xsdelements/elementswrapper/ReferenceBase.h>
#include <xsdelements/elementswrapper/UnsolvedReference.h>
#include <xsdelements/visitors/XsdAbstractElementVisitor.h>
#include <xsdelements/AttributeValidations.h>




XsdAll::XsdAll(std::shared_ptr<XsdParserCore> parser,
               StringMap attributesMap,
               VisitorFunctionType visitorFunction,
               std::shared_ptr<XsdAbstractElement> parent)
  : XsdMultipleElements(parser, attributesMap, visitorFunction, parent),
    m_minOccurs(1),
    m_maxOccurs(1)
{
  if(haveAttribute(MIN_OCCURS_TAG))
    m_minOccurs = AttributeValidations::validateNonNegativeInteger(*XSD_TAG, *MIN_OCCURS_TAG, getAttribute(MIN_OCCURS_TAG));
  if(haveAttribute(MAX_OCCURS_TAG))
    m_maxOccurs = AttributeValidations::validateNonNegativeInteger(*XSD_TAG, *MAX_OCCURS_TAG, getAttribute(MAX_OCCURS_TAG));
}


void XsdAll::accept(std::shared_ptr<XsdAbstractElementVisitor> visitorParam)
{
    XsdMultipleElements::accept(visitorParam);
    visitorParam->visit(std::static_pointer_cast<XsdAll>(shared_from_this()));
}



/**
 * Performs a copy of the current object for replacing purposes. The cloned objects are used to replace
 * {@link UnsolvedReference} objects in the reference solving process.
 * @param placeHolderAttributes The additional attributes to add to the clone.
 * @return A copy of the object from which is called upon.
 */
std::shared_ptr<XsdAll> XsdAll::clone(StringMap placeHolderAttributes)
{
    placeHolderAttributes.merge(getAttributesMap());

    auto elementCopy = create<XsdAll>(getParser(),
                                      placeHolderAttributes,
                                      m_visitorFunction,
                                      nullptr);

    for(auto& element : getElements())
        elementCopy->m_elements.push_back(ReferenceBase::clone(getParser(), element, elementCopy));

    elementCopy->setCloneOf(shared_from_this());
    return elementCopy;
}
