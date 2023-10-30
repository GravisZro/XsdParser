#pragma once

#include <xsdelements/visitors/AttributesVisitor.h>
#include <xsdelements/XsdRestriction.h>

/**
 * Represents the restrictions of the {@link XsdRestriction} element, which can contain the following children:
 *      * {@link XsdEnumeration}
 *      * {@link XsdFractionDigits}
 *      * {@link XsdLength}
 *      * {@link XsdMaxExclusive}
 *      * {@link XsdMaxInclusive}
 *      * {@link XsdMaxLength}
 *      * {@link XsdMinExclusive}
 *      * {@link XsdMinInclusive}
 *      * {@link XsdMinLength}
 *      * {@link XsdPattern}
 *      * {@link XsdTotalDigits}
 *      * {@link XsdWhiteSpace}
 *      * {@link XsdSimpleType}
 * Can also have {@link XsdAttribute} and {@link XsdAttributeGroup} children as per inheritance of {@link AttributesVisitor}.
 * Can also have {@link XsdAnnotation} children as per inheritance of {@link XsdAnnotatedElementsVisitor}.
 */
struct XsdRestrictionVisitor : AttributesVisitor
{
  XsdRestrictionVisitor(XsdRestriction* _owner) : owner(_owner) { }
  ~XsdRestrictionVisitor(void) { delete owner; owner = nullptr; }

  /**
   * The {@link XsdRestriction} instance which owns this {@link XsdRestrictionVisitor} instance. This way this
   * visitor instance can perform changes in the {@link XsdRestriction} object.
   */
  XsdRestriction* owner;

  virtual XsdAbstractElement* getOwner(void) override
    { return static_cast<XsdAbstractElement*>(owner); }

  virtual void visit(XsdAbstractElement* element) override;
};
