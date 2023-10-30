#pragma once

#include <xsdelements/AttributeValidations.h>
#include <xsdelements/XsdAbstractElement.h>
#include <xsdelements/visitors/XsdAbstractElementVisitor.h>

#include <xsdelements/xsdrestrictions/XsdIntegerRestrictions.h>

/**
 * States the minimum length of a given type, either a {@link std::string}, a {@link List} or another measurable type. This
 * limit includes the respective value. The value is defined as an {@link int}.
 * Example: If the type has a {@link XsdMinLength#value} of 2 it means that the {@link std::string}, {@link List} or another
 * measurable type should have a minimum length of 2.
 */
class XsdMinLength : public XsdIntegerRestrictions
{
public: // ctors
  XsdMinLength(StringMap attributesMap,
               VisitorFunctionType visitorFunction,
               XsdAbstractElement* parent)
        : XsdIntegerRestrictions(attributesMap, visitorFunction, parent)
  {
    assert(haveAttribute(VALUE_TAG));
    m_value = AttributeValidations::validateRequiredNonNegativeInteger(*TAG<XsdMinLength>::xsd, *VALUE_TAG, getAttribute(VALUE_TAG));
  }

  /**
   * Performs a copy of the current object for replacing purposes. The cloned objects are used to replace
   * {@link UnsolvedReference} objects in the reference solving process.
   * @param placeHolderAttributes The additional attributes to add to the clone.
   * @return A copy of the object from which is called upon.
   */
  XsdMinLength(const XsdMinLength& other, XsdAbstractElement* parent = nullptr)
    : XsdMinLength(other.getAttributesMap(), other.m_visitorFunction, parent)
  {
  }
public:
  void accept(XsdAbstractElementVisitor* xsdAbstractElementVisitor) override
  {
    XsdIntegerRestrictions::accept(xsdAbstractElementVisitor);
    xsdAbstractElementVisitor->visit(static_cast<XsdMinLength*>(this));
  }
};
