#pragma once


// #include <xsdelements/*.h>
#include <xsdelements/elementswrapper/ReferenceBase.h>
#include <xsdelements/visitors/AttributesVisitor.h>
#include <xsdelements/XsdComplexType.h>

/**
 * Represents the restrictions of the {@link XsdComplexType} element, which can contain the following children:
 *      * {@link XsdAll}, {@link XsdSequence}, {@link XsdChoice} (represented by {@link XsdMultipleElements});
 *      * {@link XsdGroup};
 *      * {@link XsdComplexContent};
 *      * {@link XsdSimpleContent};
 * Can also have {@link XsdAttribute} and {@link XsdAttributeGroup} as children as per inheritance of {@link AttributesVisitor}.
 * Can also have {@link XsdAnnotation} children as per inheritance of {@link XsdAnnotatedElementsVisitor}.
 */
class XsdComplexTypeVisitor : public AttributesVisitor
{
private:
    /**
     * The {@link XsdComplexType} instance which owns this {@link XsdComplexTypeVisitor} instance. This way this visitor
     * instance can perform changes in the {@link XsdComplexType} object.
     */
    std::shared_ptr<XsdComplexType> m_owner;
public:
    using AttributesVisitor::visit;
  XsdComplexTypeVisitor(std::shared_ptr<XsdComplexType> owner)
        : AttributesVisitor(std::static_pointer_cast<XsdAnnotatedElements>(owner))
  {
    m_owner = owner;
  }

  virtual std::shared_ptr<XsdAbstractElement> getOwner(void) override
    { return std::static_pointer_cast<XsdAbstractElement>(m_owner); }

  void visit(std::shared_ptr<XsdMultipleElements> element) override;
  void visit(std::shared_ptr<XsdGroup> element) override;
  void visit(std::shared_ptr<XsdComplexContent> element) override;
  void visit(std::shared_ptr<XsdSimpleContent> element) override;
};
