#pragma once

#include <xsdelements/XsdAbstractElement.h>

/**
 * A class that serves as a base to every {@link XsdAbstractElement} concrete type that contains an id field.
 */
class XsdIdentifierElements : public XsdAbstractElement
{
private:
    /**
     * Specifies a unique ID for the element.
     */
  std::optional<std::string> m_id;

public: // ctors
  XsdIdentifierElements(std::shared_ptr<XsdParserCore> parser,
                        StringMap attributesMap,
                        VisitorFunctionType visitorFunction,
                        std::shared_ptr<XsdAbstractElement> parent)
    : XsdAbstractElement(parser, attributesMap, visitorFunction, parent) { }

public:
  virtual void initialize(void) override
  {
    XsdAbstractElement::initialize();
    m_id.reset();
    if(haveAttribute(XsdAbstractElement::ID_TAG))
      m_id = getAttribute(XsdAbstractElement::ID_TAG);
  }

  std::optional<std::string> getId(void) const
  {
    return m_id;
  }
};
