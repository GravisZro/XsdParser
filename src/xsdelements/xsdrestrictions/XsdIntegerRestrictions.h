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
public:
  using XsdAnnotatedElements::clone;
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
public: // ctors
  XsdIntegerRestrictions(std::shared_ptr<XsdParserCore> parser,
                         StringMap attributesMap,
                         VisitorFunctionType visitorFunction,
                         std::shared_ptr<XsdAbstractElement> parent)
    : XsdAnnotatedElements(parser, attributesMap, visitorFunction, parent),
      m_fixed(false),
      m_value(INT_MIN)
  {
  }

public:
  virtual void initialize(void) override
  {
    XsdAnnotatedElements::initialize();
    m_fixed = false;
    m_value = INT_MIN;
    if(haveAttribute(FIXED_TAG))
      m_fixed = AttributeValidations::validateBoolean(getAttribute(FIXED_TAG));
  }

    /**
     * Compares two different objects of this type.
     * @param o1 The first object.
     * @param o2 The object to compare.
     * @return True if the value of both classes is different, False if the value is equal.
     */
  static bool hasDifferentValue(std::shared_ptr<XsdIntegerRestrictions> o1, std::shared_ptr<XsdIntegerRestrictions> o2)
  {
    if (o1 && o2)
      return o1->getValue() != o2->getValue();
    return false;
  }

  int getValue(void) {
        return m_value;
    }

  bool isFixed(void) {
        return m_fixed;
    }
};
