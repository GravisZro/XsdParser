#include "XsdComplexContent.h"

#include <xsdelements/XsdExtension.h>
#include <xsdelements/XsdRestriction.h>

/**
 * Performs a copy of the current object for replacing purposes. The cloned objects are used to replace
 * {@link UnsolvedReference} objects in the reference solving process.
 * @param placeHolderAttributes The additional attributes to add to the clone.
 * @return A copy of the object from which is called upon.
 */
XsdComplexContent::XsdComplexContent(const XsdComplexContent& other, XsdAbstractElement* parent)
  : XsdComplexContent(other.getAttributesMap(), other.m_visitorFunction, parent)
{
  m_restriction = new ReferenceBase(other.m_restriction, this);
  m_extension = new ReferenceBase(other.m_extension, this);
  setCloneOf(&other);
}

XsdExtension* XsdComplexContent::getXsdExtension(void) const
{
  if(auto x = dynamic_cast<ConcreteElement*>(m_extension); x != nullptr)
    return static_cast<XsdExtension*>(x->getElement());
  return nullptr;
}

XsdRestriction* XsdComplexContent::getXsdRestriction(void) const
{
  if(auto x = dynamic_cast<ConcreteElement*>(m_restriction); x != nullptr)
    return static_cast<XsdRestriction*>(x->getElement());
  return nullptr;
}
