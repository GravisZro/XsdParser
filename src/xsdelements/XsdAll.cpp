#include "XsdAll.h"

#include <core/XsdParserCore.h>

#include <xsdelements/elementswrapper/ReferenceBase.h>
#include <xsdelements/visitors/XsdAbstractElementVisitor.h>

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
std::shared_ptr<XsdAbstractElement> XsdAll::clone(StringMap placeHolderAttributes)
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
