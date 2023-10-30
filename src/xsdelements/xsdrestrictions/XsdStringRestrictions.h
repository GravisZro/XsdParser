#pragma once

#include <xsdelements/XsdAbstractElement.h>
#include <xsdelements/visitors/XsdAbstractElementVisitor.h>

#include <xsdelements/XsdAnnotatedElements.h>

/**
 * This class serves as a base to every different restriction that has its restricting parameter defined as an {@link std::string}.
 * Classes like {@link XsdPattern} or {@link XsdEnumeration} should extend this class.
 */
class XsdStringRestrictions : public XsdAnnotatedElements
{
public: // ctors
  XsdStringRestrictions(StringMap attributesMap,
                        VisitorFunctionType visitorFunction,
                        XsdAbstractElement* parent)
      : XsdAnnotatedElements(attributesMap, visitorFunction, parent)
  {
    if(haveAttribute(VALUE_TAG))
      m_value = getAttribute(VALUE_TAG);
  }
public:
  std::optional<std::string> getValue(void) const
  {
    return m_value;
  }

private:
  /**
   * The value of associated with a given restriction. This field has different meanings depending on the concrete
   * restriction, e.g. if the concrete class is {@link XsdEnumeration} this field means that the attribute which
   * has the restriction can only have the value that is specified in this field.
   */
  std::optional<std::string> m_value;
};
