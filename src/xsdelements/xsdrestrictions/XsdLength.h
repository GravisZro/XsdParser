#pragma once

#include <xsdelements/AttributeValidations.h>
#include <xsdelements/XsdAbstractElement.h>
#include <xsdelements/visitors/XsdAbstractElementVisitor.h>

#include <xsdelements/xsdrestrictions/XsdIntegerRestrictions.h>

/**
 * States the exact number of length to a given type, either a {@link std::string}, a {@link List}, or another measurable type.
 * The value is defined as an {@link int}.
 */
class XsdLength : public XsdIntegerRestrictions
{
public: // ctors
  XsdLength(StringMap attributesMap,
            VisitorFunctionType visitorFunction,
            XsdAbstractElement* parent)
    : XsdIntegerRestrictions(attributesMap, visitorFunction, parent)
  {
    assert(haveAttribute(VALUE_TAG));
    m_value = AttributeValidations::validateRequiredNonNegativeInteger(*TAG<XsdLength>::xsd, *VALUE_TAG, getAttribute(VALUE_TAG));
  }

  /**
   * Performs a copy of the current object for replacing purposes. The cloned objects are used to replace
   * {@link UnsolvedReference} objects in the reference solving process.
   * @param placeHolderAttributes The additional attributes to add to the clone.
   * @return A copy of the object from which is called upon.
   */
  XsdLength(const XsdLength& other, XsdAbstractElement* parent = nullptr)
    : XsdLength(other.getAttributesMap(), other.m_visitorFunction, parent)
  {
  }

public:
  void accept(XsdAbstractElementVisitor* xsdAbstractElementVisitor) override
  {
    XsdIntegerRestrictions::accept(xsdAbstractElementVisitor);
    xsdAbstractElementVisitor->visit(static_cast<XsdLength*>(this));
  }
};
