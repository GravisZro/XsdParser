#pragma once

#include <xsdelements/visitors/AttributesVisitor.h>

class XsdEnumeration;
class XsdFractionDigits;
class XsdLength;
class XsdMaxExclusive;
class XsdMaxInclusive;
class XsdMaxLength;
class XsdMinExclusive;
class XsdMinInclusive;
class XsdMinLength;
class XsdPattern;
class XsdTotalDigits;
class XsdWhiteSpace;
class XsdAll;
class XsdChoice;
class XsdSequence;
class XsdGroup;
class XsdRestriction;
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
  XsdRestrictionVisitor(std::shared_ptr<XsdRestriction> _owner) : owner(_owner) { }

  /**
   * The {@link XsdRestriction} instance which owns this {@link XsdRestrictionVisitor} instance. This way this
   * visitor instance can perform changes in the {@link XsdRestriction} object.
   */
  std::shared_ptr<XsdRestriction> owner;

  virtual std::shared_ptr<XsdAbstractElement> getOwner(void) override
    { return std::static_pointer_cast<XsdAbstractElement>(owner); }

  virtual void visit(std::shared_ptr<XsdAbstractElement> element) override;
};
