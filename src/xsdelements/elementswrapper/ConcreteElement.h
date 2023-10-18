#pragma once

#include <xsdelements/XsdAbstractElement.h>

#include "ReferenceBase.h"

/**
 * ConcreteElement is a wrapper class for an {@link XsdAbstractElement} object which doesn't have a ref attribute.
 */
class ConcreteElement : public ReferenceBase
{
  public:
    ConcreteElement(std::shared_ptr<XsdAbstractElement> element);
};
