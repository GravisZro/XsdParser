#pragma once

#include <xsdelements/XsdNamedElements.h>

class XsdBuiltInDataType : public XsdNamedElements
{
public: // ctors
  XsdBuiltInDataType(std::shared_ptr<XsdParserCore> parser,
                     StringMap attributesMap,
                     VisitorFunctionType visitorFunction,
                     std::shared_ptr<XsdAbstractElement> parent)
    : XsdNamedElements(parser, attributesMap, visitorFunction, parent)
  {
  }
public:
  virtual std::shared_ptr<XsdAbstractElement> clone([[maybe_unused]] StringMap placeHolderAttributes) override
  {
    return create<XsdBuiltInDataType>(getParser(),
                                      getAttributesMap(),
                                      nullptr,
                                      getParent());
  }
};
