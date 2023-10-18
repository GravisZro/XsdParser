#include "ConcreteElement.h"

#include <xsdelements/XsdAbstractElement.h>


ConcreteElement::ConcreteElement(std::shared_ptr<XsdAbstractElement> element)
  : ReferenceBase(element)
{ }
