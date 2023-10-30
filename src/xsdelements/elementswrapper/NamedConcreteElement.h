#pragma once

#include "ConcreteElement.h"

#include <xsdelements/XsdNamedElements.h>

/**
 * NamedConcreteElement is a wrapper class for an {@link XsdNamedElements} object which are {@link XsdAbstractElement}
 * objects which have a name attribute.
 */
class NamedConcreteElement : public ConcreteElement
{
private:
  std::string m_name;

public:
  NamedConcreteElement(XsdNamedElements* element, std::string name)
    : ConcreteElement(static_cast<XsdAbstractElement*>(element)),
      m_name(name)
  {
  }

  std::string getName(void) const { return m_name; }

  XsdNamedElements* getElement(void) const
  {
    return static_cast<XsdNamedElements*>(m_element);
  }
};
