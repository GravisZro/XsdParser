#pragma once

#include <xsdelements/AttributeValidations.h>
#include <xsdelements/XsdAbstractElement.h>
#include <xsdelements/visitors/XsdAbstractElementVisitor.h>

#include <xsdelements/xsdrestrictions/XsdIntegerRestrictions.h>

/**
 * States the number of total digits allowed in a numeric type. The value is defined as an {@link int}.
 */
class XsdTotalDigits : public XsdIntegerRestrictions
{
public: // ctors
  XsdTotalDigits(StringMap attributesMap,
                 VisitorFunctionType visitorFunction,
                 XsdAbstractElement* parent)
        : XsdIntegerRestrictions(attributesMap, visitorFunction, parent)
  {
    assert(haveAttribute(VALUE_TAG));
    m_value = AttributeValidations::validateRequiredPositiveInteger(*TAG<XsdTotalDigits>::xsd, *VALUE_TAG, getAttribute(VALUE_TAG));
  }

  /**
   * Performs a copy of the current object for replacing purposes. The cloned objects are used to replace
   * {@link UnsolvedReference} objects in the reference solving process.
   * @param placeHolderAttributes The additional attributes to add to the clone.
   * @return A copy of the object from which is called upon.
   */
  XsdTotalDigits(const XsdTotalDigits& other, XsdAbstractElement* parent = nullptr)
    : XsdTotalDigits(other.getAttributesMap(), other.m_visitorFunction, parent)
  {
  }
public:
  void accept(XsdAbstractElementVisitor* xsdAbstractElementVisitor) override
  {
    XsdIntegerRestrictions::accept(xsdAbstractElementVisitor);
    xsdAbstractElementVisitor->visit(static_cast<XsdTotalDigits*>(this));
  }
};
