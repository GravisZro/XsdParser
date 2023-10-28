#include "XsdComplexContent.h"

#include <xsdelements/XsdExtension.h>
#include <xsdelements/XsdRestriction.h>

/**
 * Performs a copy of the current object for replacing purposes. The cloned objects are used to replace
 * {@link UnsolvedReference} objects in the reference solving process.
 * @param placeHolderAttributes The additional attributes to add to the clone.
 * @return A copy of the object from which is called upon.
 */
std::shared_ptr<XsdAbstractElement> XsdComplexContent::clone(StringMap placeHolderAttributes)
{
  placeHolderAttributes.merge(getAttributesMap());

  auto elementCopy = create<XsdComplexContent>(getParser(),
                                               placeHolderAttributes,
                                               m_visitorFunction,
                                               nullptr);

  elementCopy->m_restriction = ReferenceBase::clone(getParser(), m_restriction, elementCopy);
  elementCopy->m_extension = ReferenceBase::clone(getParser(), m_extension, elementCopy);
  elementCopy->setCloneOf(shared_from_this());

  return elementCopy;
}

std::shared_ptr<XsdExtension> XsdComplexContent::getXsdExtension(void) const
{
  if(auto x = std::dynamic_pointer_cast<ConcreteElement>(m_extension); x)
    return std::static_pointer_cast<XsdExtension>(x->getElement());
  return nullptr;
}

std::shared_ptr<XsdRestriction> XsdComplexContent::getXsdRestriction(void) const
{
  if(auto x = std::dynamic_pointer_cast<ConcreteElement>(m_restriction); x)
    return std::static_pointer_cast<XsdRestriction>(x->getElement());
  return nullptr;
}
