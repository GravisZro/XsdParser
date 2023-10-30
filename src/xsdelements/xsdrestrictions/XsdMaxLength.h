#pragma once

#include <xsdelements/AttributeValidations.h>
#include <xsdelements/XsdAbstractElement.h>
#include <xsdelements/visitors/XsdAbstractElementVisitor.h>

#include <xsdelements/xsdrestrictions/XsdIntegerRestrictions.h>

/**
 * States the maximum length of a given type, either a {@link std::string}, a {@link List} or another measurable type.
 * This limit including the respective value. The value is defined as an {@link int}.
 * Example: If the type has a {@link XsdMaxLength#value} of 5 it means that the {@link std::string}, {@link List} or another
 * measurable type should have a maximum length of 5.
 */
class XsdMaxLength : public XsdIntegerRestrictions
{
public: // ctors
  XsdMaxLength(StringMap attributesMap,
               VisitorFunctionType visitorFunction,
               XsdAbstractElement* parent)
        : XsdIntegerRestrictions(attributesMap, visitorFunction, parent)
  {
    assert(hasAttribute(VALUE_TAG));
    m_value = AttributeValidations::validateRequiredNonNegativeInteger(*TAG<XsdMaxLength>::xsd, *VALUE_TAG, getAttribute(VALUE_TAG));
  }

  /**
   * Performs a copy of the current object for replacing purposes. The cloned objects are used to replace
   * {@link UnsolvedReference} objects in the reference solving process.
   * @param placeHolderAttributes The additional attributes to add to the clone.
   * @return A copy of the object from which is called upon.
   */
  XsdMaxLength(const XsdMaxLength& other, XsdAbstractElement* parent = nullptr)
    : XsdMaxLength(other.getAttributesMap(), other.m_visitorFunction, parent)
  {
  }
public:
  void accept(XsdAbstractElementVisitor* xsdAbstractElementVisitor) override
  {
    XsdIntegerRestrictions::accept(xsdAbstractElementVisitor);
    xsdAbstractElementVisitor->visit(static_cast<XsdMaxLength*>(this));
  }
};
