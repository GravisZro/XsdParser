#pragma once

#include <xsdelements/AttributeValidations.h>
#include <xsdelements/XsdAbstractElement.h>
#include <xsdelements/XsdAnnotatedElements.h>
#include <xsdelements/enums/WhiteSpaceEnum.h>
#include <xsdelements/visitors/XsdAbstractElementVisitor.h>

#include <xsdelements/XsdAnnotatedElements.h>

/**
 * States how the whiteSpace characters should be treated. The value is defined as an {@link std::string}.
 */
class XsdWhiteSpace : public XsdAnnotatedElements
{
public: // ctors
  XsdWhiteSpace(StringMap attributesMap,
                VisitorFunctionType visitorFunction,
                XsdAbstractElement* parent)
        : XsdAnnotatedElements(attributesMap, visitorFunction, parent),
          m_fixed(false)
  {
    if(haveAttribute(FIXED_TAG))
      m_fixed = AttributeValidations::validateBoolean(getAttribute(FIXED_TAG));
    if(haveAttribute(VALUE_TAG))
      m_value = AttributeValidations::belongsToEnum<WhiteSpaceEnum>(getAttribute(VALUE_TAG));
  }

  /**
   * Performs a copy of the current object for replacing purposes. The cloned objects are used to replace
   * {@link UnsolvedReference} objects in the reference solving process.
   * @param placeHolderAttributes The additional attributes to add to the clone.
   * @return A copy of the object from which is called upon.
   */
  XsdWhiteSpace(const XsdWhiteSpace& other, XsdAbstractElement* parent = nullptr)
    : XsdWhiteSpace(other.getAttributesMap(), other.m_visitorFunction, parent)
  {
  }

public:
  void accept(XsdAbstractElementVisitor* xsdAbstractElementVisitor) override
  {
    XsdAnnotatedElements::accept(xsdAbstractElementVisitor);
    xsdAbstractElementVisitor->visit(static_cast<XsdWhiteSpace*>(this));
  }

  bool isFixed(void) const
  {
    return m_fixed;
  }

  WhiteSpaceEnum getValue(void) const
  {
    return m_value;
  }

private:
  bool m_fixed;
  WhiteSpaceEnum m_value;
};
