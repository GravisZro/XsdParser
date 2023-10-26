#pragma once

#include "ReferenceBase.h"
#include <xsdelements/XsdNamedElements.h>

/**
 * UnsolvedReference is a wrapper class for all objects which should be resolved in the parsing process, if possible.
 */
class UnsolvedReference : public ReferenceBase
{
private:
  std::optional<std::string> m_ref;
  bool m_isTypeRef;

public:
  UnsolvedReference(std::shared_ptr<XsdNamedElements> element)
    : ReferenceBase(std::static_pointer_cast<XsdAbstractElement>(element)),
      m_ref(ReferenceBase::getRef(std::static_pointer_cast<XsdAbstractElement>(element))),
      m_isTypeRef(false)
  {
  }

  UnsolvedReference(std::optional<std::string> refType, std::shared_ptr<XsdNamedElements> element)
    : ReferenceBase(std::static_pointer_cast<XsdAbstractElement>(element)),
      m_ref(refType),
      m_isTypeRef(true)
  {
  }

  std::optional<std::string> getRef(void) const { return m_ref; }

  bool isTypeRef(void) const { return m_isTypeRef; }

  std::shared_ptr<XsdAbstractElement> getParent(void) const
  {
    return m_element->getParent();
  }

  std::shared_ptr<XsdNamedElements> getElement(void) const
  {
    return std::static_pointer_cast<XsdNamedElements>(m_element);
  }
};
