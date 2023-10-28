#include "XsdChoice.h"

#include <xsdelements/elementswrapper/ReferenceBase.h>
#include <xsdelements/XsdSequence.h>
#include <xsdelements/XsdGroup.h>

/**
 * Performs a copy of the current object for replacing purposes. The cloned objects are used to replace
 * {@link UnsolvedReference} objects in the reference solving process.
 * @param placeHolderAttributes The additional attributes to add to the clone.
 * @return A copy of the object from which is called upon.
 */
std::shared_ptr<XsdAbstractElement> XsdChoice::clone(StringMap placeHolderAttributes)
{
  placeHolderAttributes.merge(getAttributesMap());

  auto elementCopy = create<XsdChoice>(getParser(),
                                       placeHolderAttributes,
                                       m_visitorFunction,
                                       nullptr);
  for(auto& element : getElements())
    elementCopy->m_elements.push_back(ReferenceBase::clone(getParser(), element, elementCopy));

  return elementCopy;
}
