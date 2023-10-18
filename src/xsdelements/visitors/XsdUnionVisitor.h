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

  std::shared_ptr<XsdUnion> getOwner(void)
    {
        return m_owner;
    }

  void visit(std::shared_ptr<XsdSimpleType> element)
    {
        XsdAnnotatedElementsVisitor::visit(element);

        m_owner->add(element);
    }
};
