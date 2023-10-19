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
  std::shared_ptr<XsdRestriction> getOwner(void)
  {
    return m_owner;
  }

  void visit(std::shared_ptr<XsdEnumeration> element);
  void visit(std::shared_ptr<XsdFractionDigits> element);
  void visit(std::shared_ptr<XsdLength> element);
  void visit(std::shared_ptr<XsdMaxExclusive> element);
  void visit(std::shared_ptr<XsdMaxInclusive> element);
  void visit(std::shared_ptr<XsdMaxLength> element);
  void visit(std::shared_ptr<XsdMinExclusive> element);
  void visit(std::shared_ptr<XsdMinInclusive> element);
  void visit(std::shared_ptr<XsdMinLength> element);
  void visit(std::shared_ptr<XsdPattern> element);
  void visit(std::shared_ptr<XsdTotalDigits> element);
  void visit(std::shared_ptr<XsdWhiteSpace> element);
  void visit(std::shared_ptr<XsdAll> element);
  void visit(std::shared_ptr<XsdChoice> element);
  void visit(std::shared_ptr<XsdSequence> element);
  void visit(std::shared_ptr<XsdGroup> element);
};
