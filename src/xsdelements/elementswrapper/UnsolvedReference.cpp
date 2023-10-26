#include "UnsolvedReference.h"

#include <xsdelements/XsdAbstractElement.h>
#include <xsdelements/XsdNamedElements.h>


UnsolvedReference::UnsolvedReference(std::shared_ptr<XsdNamedElements> element)
  : ReferenceBase(std::static_pointer_cast<XsdAbstractElement>(element))
{
  m_ref = ReferenceBase::getRef(std::static_pointer_cast<XsdAbstractElement>(element));
  m_isTypeRef = false;
}

UnsolvedReference::UnsolvedReference(std::string refType, std::shared_ptr<XsdNamedElements> element)
  : ReferenceBase(std::static_pointer_cast<XsdAbstractElement>(element))
{
  m_ref = refType;
  m_isTypeRef = true;
}


std::shared_ptr<XsdAbstractElement> UnsolvedReference::getParent(void) const
{
  return m_element->getParent();
}

std::shared_ptr<XsdNamedElements> UnsolvedReference::getElement(void) const
{
  return std::static_pointer_cast<XsdNamedElements>(m_element);
}
