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
  NamedConcreteElement(std::shared_ptr<XsdNamedElements> element, std::string name)
    : ConcreteElement(std::static_pointer_cast<XsdAbstractElement>(element)),
      m_name(name)
  {
  }

  std::string getName(void) const { return m_name; }

  std::shared_ptr<XsdNamedElements> getElement(void) const
  {
    return std::static_pointer_cast<XsdNamedElements>(m_element);
  }
};
