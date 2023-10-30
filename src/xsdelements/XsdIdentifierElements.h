#pragma once

#include <xsdelements/XsdAbstractElement.h>

/**
 * A class that serves as a base to every {@link XsdAbstractElement} concrete type that contains an id field.
 */
class XsdIdentifierElements : public XsdAbstractElement
{
public: // ctors
  XsdIdentifierElements(StringMap attributesMap,
                        VisitorFunctionType visitorFunction,
                        XsdAbstractElement* parent)
    : XsdAbstractElement(attributesMap, visitorFunction, parent)
  {
    if(haveAttribute(XsdAbstractElement::ID_TAG))
      m_id = getAttribute(XsdAbstractElement::ID_TAG);
  }

public:

  std::optional<std::string> getId(void) const
  {
    return m_id;
  }

private:
  /**
   * Specifies a unique ID for the element.
   */
  std::optional<std::string> m_id;
};
