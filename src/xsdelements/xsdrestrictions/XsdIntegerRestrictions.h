#pragma once



#include <xsdelements/AttributeValidations.h>
#include <xsdelements/XsdAbstractElement.h>
#include <xsdelements/visitors/XsdAbstractElementVisitor.h>

#include <xsdelements/XsdAnnotatedElements.h>

/**
 * This class serves as a base to every different restriction that has its restricting parameter defined as an {@link int}.
 * Classes like {@link XsdMaxLength} or {@link XsdLength} should extend this class.
 * i.e. xsd:maxLength or xsd:length.
 */
class XsdIntegerRestrictions : public XsdAnnotatedElements
{
public: // ctors
  XsdIntegerRestrictions(StringMap attributesMap,
                         VisitorFunctionType visitorFunction,
                         XsdAbstractElement* parent)
    : XsdAnnotatedElements(attributesMap, visitorFunction, parent),
      m_fixed(false),
      m_value(INT_MIN)
  {
    if(hasAttribute(FIXED_TAG))
      m_fixed = AttributeValidations::validateBoolean(getAttribute(FIXED_TAG));
  }

public:
  int getValue(void) const
  {
    return m_value;
  }

  bool isFixed(void) const
  {
    return m_fixed;
  }

protected:
  /**
   * Indicates if the value is fixed.
   */
  bool m_fixed;

  /**
   * The value of associated with a given restriction. This field has different meanings depending on the concrete
   * restriction, e.g. if the concrete class is {@link XsdLength} this field means that the attribute which
   * has the restriction can only have the length specified in this field..
   */
  int m_value;
};
