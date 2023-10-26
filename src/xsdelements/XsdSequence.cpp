#include "XsdSequence.h"

#include <xsdelements/elementswrapper/ReferenceBase.h>
#include <xsdelements/XsdChoice.h>
#include <xsdelements/XsdGroup.h>

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
std::shared_ptr<XsdAbstractElement> XsdSequence::clone(StringMap placeHolderAttributes)
{
    placeHolderAttributes.merge(getAttributesMap());

    auto elementCopy = create<XsdSequence>(getParser(),
                                           placeHolderAttributes,
                                           m_visitorFunction,
                                           nullptr);

    for(auto& element : getElements())
        elementCopy->m_elements.push_back(ReferenceBase::clone(getParser(), element, elementCopy));

    elementCopy->setCloneOf(shared_from_this());

    return elementCopy;
}
