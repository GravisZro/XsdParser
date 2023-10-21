#include "XsdSequence.h"

#include <xsdelements/AttributeValidations.h>

#include <xsdelements/XsdChoice.h>
#include <xsdelements/XsdGroup.h>

XsdSequence::XsdSequence(std::shared_ptr<XsdParserCore> parser, StringMap attributesMap, VisitorFunctionReference visitorFunction)
  : XsdMultipleElements(parser, attributesMap, visitorFunction),
    m_minOccurs(1),
    m_maxOccurs("1")
{
  if(haveAttribute(MIN_OCCURS_TAG))
    m_minOccurs = AttributeValidations::validateNonNegativeInteger(*XSD_TAG, *MIN_OCCURS_TAG, getAttribute(MIN_OCCURS_TAG));

  if(haveAttribute(MAX_OCCURS_TAG))
    m_maxOccurs = AttributeValidations::maxOccursValidation(*XSD_TAG, getAttribute(MAX_OCCURS_TAG));
}

void XsdSequence::accept(std::shared_ptr<XsdAbstractElementVisitor> visitorParam)
{
    XsdMultipleElements::accept(visitorParam);
    visitorParam->visit(std::static_pointer_cast<XsdSequence>(shared_from_this()));
}

/**
 * Performs a copy of the current object for replacing purposes. The cloned objects are used to replace
 * {@link UnsolvedReference} objects in the reference solving process.
 * @param placeHolderAttributes The additional attributes to add to the clone.
 * @return A copy of the object from which is called upon.
 */
std::shared_ptr<XsdSequence> XsdSequence::clone(StringMap placeHolderAttributes)
{
    placeHolderAttributes.merge(getAttributesMap());

    auto elementCopy = create<XsdSequence>(getParser(),
                                           placeHolderAttributes,
                                           m_visitorFunction);

    for(auto& element : getElements())
        elementCopy->m_elements.push_back(ReferenceBase::clone(getParser(), element, elementCopy));

    elementCopy->setCloneOf(shared_from_this());
    elementCopy->setParent(nullptr);

    return elementCopy;
}

/**
 * @return The children elements that are of the type {@link XsdChoice}.
 */
std::list<std::shared_ptr<XsdChoice>> XsdSequence::getChildrenChoices(void)
{
std::list<std::shared_ptr<XsdChoice>> rval;
for(auto& element : getXsdElements())
  if(auto x = std::dynamic_pointer_cast<XsdChoice>(element); x)
    rval.push_back(x);
return rval;
}

/**
 * @return The children elements that are of the type {@link XsdSequence}.
 */
std::list<std::shared_ptr<XsdSequence>> XsdSequence::getChildrenSequences(void)
{
std::list<std::shared_ptr<XsdSequence>> rval;
for(auto& element : getXsdElements())
  if(auto x = std::dynamic_pointer_cast<XsdSequence>(element); x)
    rval.push_back(x);
return rval;
}

/**
 * @return The children elements that are of the type {@link XsdGroup}.
 */
std::list<std::shared_ptr<XsdGroup>> XsdSequence::getChildrenGroups(void)
{
std::list<std::shared_ptr<XsdGroup>> rval;
for(auto& element : getXsdElements())
  if(auto x = std::dynamic_pointer_cast<XsdGroup>(element); x)
    rval.push_back(x);
return rval;
}
