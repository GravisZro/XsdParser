#pragma once

#include "ConcreteElement.h"

class XsdNamedElements;

/**
 * NamedConcreteElement is a wrapper class for an {@link XsdNamedElements} object which are {@link XsdAbstractElement}
 * objects which have a name attribute.
 */
class NamedConcreteElement : public ConcreteElement
{
private:
  std::string m_name;

public:
    NamedConcreteElement(std::shared_ptr<XsdNamedElements> element, std::string name);

  std::string getName(void) { return m_name; }

  std::shared_ptr<XsdNamedElements> getElement(void);
};
