#pragma once

#include <xsdelements/XsdNamedElements.h>

class XsdBuiltInDataType : public XsdNamedElements
{
public:
  using XsdNamedElements::clone;
public: // ctors
  XsdBuiltInDataType(std::shared_ptr<XsdParserCore> parser,
                     StringMap attributesMap,
                     VisitorFunctionType visitorFunction,
                     std::shared_ptr<XsdAbstractElement> parent)
    : XsdNamedElements(parser, attributesMap, visitorFunction, parent)
  {
  }
public:
  std::shared_ptr<XsdNamedElements> clone([[maybe_unused]] StringMap placeHolderAttributes)
  {
    return create<XsdBuiltInDataType>(getParser(),
                                      getAttributesMap(),
                                      nullptr,
                                      getParent());
  }
};
