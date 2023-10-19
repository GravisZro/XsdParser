#pragma once


#include <xsdelements/XsdNamedElements.h>

class XsdBuiltInDataType : public XsdNamedElements
{
public:
  using XsdNamedElements::clone;
  XsdBuiltInDataType(std::shared_ptr<XsdParserCore> parser,
                     StringMap attributesMap,
                     std::shared_ptr<XsdAbstractElement> parent)
    : XsdNamedElements(parser, attributesMap, nullptr)
  {
    setParent(parent);
  }

  std::shared_ptr<XsdNamedElements> clone([[maybe_unused]] StringMap placeHolderAttributes)
    {
        return std::make_shared<XsdBuiltInDataType>(getParser(), m_attributesMap, m_parent);
    }
};
