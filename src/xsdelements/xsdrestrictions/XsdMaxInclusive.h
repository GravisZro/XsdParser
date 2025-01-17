#pragma once

#include <xsdelements/AttributeValidations.h>
#include <xsdelements/XsdAbstractElement.h>
#include <xsdelements/visitors/XsdAbstractElementVisitor.h>

#include <xsdelements/xsdrestrictions/XsdStringRestrictions.h>

/**
 * States the maximum value that a given type might take, including the respective value. The value is defined
 * as a {@link std::string}.
 * Example: If the type has a {@link XsdMaxInclusive#value} of 5 it means that the maximum value it can take is 5.
 */
class XsdMaxInclusive : public XsdStringRestrictions
{
public: // ctors
  XsdMaxInclusive(StringMap attributesMap,
                  VisitorFunctionType visitorFunction,
                  XsdAbstractElement* parent)
      : XsdStringRestrictions(attributesMap, visitorFunction, parent),
        m_fixed(false)
  {
    if(hasAttribute(FIXED_TAG))
      m_fixed = AttributeValidations::validateBoolean(getAttribute(FIXED_TAG));
  }

  /**
   * Performs a copy of the current object for replacing purposes. The cloned objects are used to replace
   * {@link UnsolvedReference} objects in the reference solving process.
   * @param placeHolderAttributes The additional attributes to add to the clone.
   * @return A copy of the object from which is called upon.
   */
  XsdMaxInclusive(const XsdMaxInclusive& other, XsdAbstractElement* parent = nullptr)
    : XsdMaxInclusive(other.getAttributesMap(), other.m_visitorFunction, parent)
  {
  }
public:
  void accept(XsdAbstractElementVisitor* xsdAbstractElementVisitor) override
  {
    XsdStringRestrictions::accept(xsdAbstractElementVisitor);
    xsdAbstractElementVisitor->visit(static_cast<XsdMaxInclusive*>(this));
  }

  bool isFixed(void) const
  {
    return m_fixed;
  }

private:
  /**
   * Indicates if the value is fixed.
   */
  bool m_fixed;
};
