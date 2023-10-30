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
  UnsolvedReference(XsdNamedElements* element)
    : ReferenceBase(static_cast<XsdAbstractElement*>(element)),
      m_isTypeRef(false)
  {
    if(element->hasAttribute(XsdNamedElements::REF_TAG))
      m_ref = element->getAttribute(XsdNamedElements::REF_TAG);
  }

  UnsolvedReference(std::optional<std::string> refType, XsdNamedElements* element)
    : ReferenceBase(static_cast<XsdAbstractElement*>(element)),
      m_ref(refType),
      m_isTypeRef(true)
  {
  }

  std::optional<std::string> getRef(void) const { return m_ref; }

  bool isTypeRef(void) const { return m_isTypeRef; }

  XsdAbstractElement* getParent(void) const
  {
    return m_element->getParent();
  }

  XsdNamedElements* getElement(void) const
  {
    return static_cast<XsdNamedElements*>(m_element);
  }
};
