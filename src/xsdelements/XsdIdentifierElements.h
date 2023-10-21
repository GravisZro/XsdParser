#pragma once

#include <core/utils/CommonOperations.h>

#include <xsdelements/XsdAbstractElement.h>
#include <xsdelements/visitors/XsdAbstractElementVisitor.h>


#include <map>
#include <functional>
#include <string>

/**
 * A class that serves as a base to every {@link XsdAbstractElement} concrete type that contains an id field.
 */
class XsdIdentifierElements : public XsdAbstractElement
{
public:
  using XsdAbstractElement::clone;
  using XsdAbstractElement::initialize;
private:
    /**
     * Specifies a unique ID for the element.
     */
  std::optional<std::string> m_id;

public: // ctors
    XsdIdentifierElements(std::shared_ptr<XsdParserCore> parser,
                          StringMap attributesMap,
                          VisitorFunctionReference visitorFunction,
                          std::shared_ptr<XsdAbstractElement> parent)
      : XsdAbstractElement(parser, attributesMap, visitorFunction, parent)
    {
      if(haveAttribute(XsdAbstractElement::ID_TAG))
        m_id = getAttribute(XsdAbstractElement::ID_TAG);
    }
public:
  std::optional<std::string> getId(void) {
        return m_id;
    }
};
