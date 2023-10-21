#pragma once


#include <xsdelements/XsdNamedElements.h>

class XsdBuiltInDataType : public XsdNamedElements
{
public:
  using XsdNamedElements::clone;
public: // ctors
  XsdBuiltInDataType(std::shared_ptr<XsdParserCore> parser,
                     StringMap attributesMap,
                     std::shared_ptr<XsdAbstractElement> parent)
    : XsdNamedElements(parser, attributesMap, nullptr)
  {
    setParent(parent);
  }
public:
  std::shared_ptr<XsdNamedElements> clone([[maybe_unused]] StringMap placeHolderAttributes)
  {
    return create<XsdBuiltInDataType>(getParser(),
                                      getAttributesMap(),
                                      getParent());
  }
};
