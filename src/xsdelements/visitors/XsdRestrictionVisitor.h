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
class XsdRestrictionVisitor : public AttributesVisitor
{
private:
    /**
     * The {@link XsdRestriction} instance which owns this {@link XsdRestrictionVisitor} instance. This way this
     * visitor instance can perform changes in the {@link XsdRestriction} object.
     */
    std::shared_ptr<XsdRestriction> m_owner;
public:
  using AttributesVisitor::visit;

  XsdRestrictionVisitor(std::shared_ptr<XsdRestriction> owner);

  virtual std::shared_ptr<XsdAbstractElement> getOwner(void) override
    { return std::static_pointer_cast<XsdAbstractElement>(m_owner); }

  void visit(std::shared_ptr<XsdEnumeration> element) override;
  void visit(std::shared_ptr<XsdFractionDigits> element) override;
  void visit(std::shared_ptr<XsdLength> element) override;
  void visit(std::shared_ptr<XsdMaxExclusive> element) override;
  void visit(std::shared_ptr<XsdMaxInclusive> element) override;
  void visit(std::shared_ptr<XsdMaxLength> element) override;
  void visit(std::shared_ptr<XsdMinExclusive> element) override;
  void visit(std::shared_ptr<XsdMinInclusive> element) override;
  void visit(std::shared_ptr<XsdMinLength> element) override;
  void visit(std::shared_ptr<XsdPattern> element) override;
  void visit(std::shared_ptr<XsdTotalDigits> element) override;
  void visit(std::shared_ptr<XsdWhiteSpace> element) override;
  void visit(std::shared_ptr<XsdAll> element) override;
  void visit(std::shared_ptr<XsdChoice> element) override;
  void visit(std::shared_ptr<XsdSequence> element) override;
  void visit(std::shared_ptr<XsdGroup> element) override;
};
