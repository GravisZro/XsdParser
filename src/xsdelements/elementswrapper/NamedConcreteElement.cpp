#include "NamedConcreteElement.h"

#include <xsdelements/XsdNamedElements.h>

NamedConcreteElement::NamedConcreteElement(std::shared_ptr<XsdNamedElements> element, std::string name)
  : ConcreteElement(std::static_pointer_cast<XsdAbstractElement>(element))
{
  m_name = name;
}

std::shared_ptr<XsdNamedElements> NamedConcreteElement::getElement(void)
{
  return std::static_pointer_cast<XsdNamedElements>(m_element);
}
