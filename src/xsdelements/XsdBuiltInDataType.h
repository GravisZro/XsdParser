#pragma once

#include <xsdelements/XsdNamedElements.h>

class XsdBuiltInDataType : public XsdNamedElements
{
public: // ctors
  XsdBuiltInDataType(StringMap attributesMap,
                     VisitorFunctionType visitorFunction,
                     XsdAbstractElement* parent)
    : XsdNamedElements(attributesMap, visitorFunction, parent)
  {
  }

  XsdBuiltInDataType(const XsdBuiltInDataType& other)
    : XsdNamedElements(other.getAttributesMap(), nullptr, other.getParent())
  {
  }
};
