#pragma once

#include <xsdelements/XsdSimpleType.h>
#include <xsdelements/XsdUnion.h>
#include <xsdelements/visitors/XsdAnnotatedElementsVisitor.h>

/**
 * Represents the restrictions of the {@link XsdUnion} element, which can only contain {@link XsdSimpleType} as children.
 * Can also have {@link XsdAnnotation} as children as per inheritance of {@link XsdAnnotatedElementsVisitor}.
 */
class XsdUnionVisitor : public XsdAnnotatedElementsVisitor
{
private:
    /**
     * The {@link XsdUnion} instance which owns this {@link XsdUnionVisitor} instance. This way this visitor instance
     * can perform changes in the {@link XsdUnion} object.
     */
    std::shared_ptr<XsdUnion> m_owner;
public:
    using XsdAnnotatedElementsVisitor::visit;
  XsdUnionVisitor(std::shared_ptr<XsdUnion> owner)
        : XsdAnnotatedElementsVisitor(owner)
  {
        m_owner = owner;
    }

  virtual std::shared_ptr<XsdAbstractElement> getOwner(void) override
    { return std::static_pointer_cast<XsdAbstractElement>(m_owner); }

  void visit(std::shared_ptr<XsdSimpleType> element) override
    {
        XsdAnnotatedElementsVisitor::visit(element);
        m_owner->add(element);
    }
};
