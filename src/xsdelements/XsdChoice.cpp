#include "XsdChoice.h"

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

/**
 * @return The children elements that are of the type {@link XsdChoice}.
 */
std::list<std::shared_ptr<XsdChoice>> XsdChoice::getChildrenChoices(void)
{
  std::list<std::shared_ptr<XsdChoice>> rvals;
  for(auto& element : getXsdElements())
    if(auto x = std::dynamic_pointer_cast<XsdChoice>(element); x)
      rvals.push_back(x);
  return rvals;
}

/**
 * @return The children elements that are of the type {@link XsdSequence}.
 */
std::list<std::shared_ptr<XsdSequence>> XsdChoice::getChildrenSequences(void)
{
  std::list<std::shared_ptr<XsdSequence>> rvals;
  for(auto& element : getXsdElements())
    if(auto x = std::dynamic_pointer_cast<XsdSequence>(element); x)
      rvals.push_back(x);
  return rvals;
}

/**
 * @return The children elements that are of the type {@link XsdGroup}.
 */
std::list<std::shared_ptr<XsdGroup>> XsdChoice::getChildrenGroups(void)
{
  std::list<std::shared_ptr<XsdGroup>> rvals;
  for(auto& element : getXsdElements())
    if(auto x = std::dynamic_pointer_cast<XsdGroup>(element); x)
      rvals.push_back(x);
  return rvals;
}
