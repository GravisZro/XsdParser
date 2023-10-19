#pragma once

#include <xsdelements/XsdAnnotation.h>
#include <xsdelements/XsdSimpleType.h>
#include <xsdelements/XsdUnion.h>
#include <xsdelements/XsdList.h>
#include <xsdelements/visitors/XsdAnnotatedElementsVisitor.h>

/**
 * Represents the restrictions of the {@link XsdSimpleType} element, which can contain {@link XsdList}, {@link XsdUnion}
 * or {@link XsdRestriction} as children. Can also have {@link XsdAnnotation} as children as per inheritance of
 * {@link XsdAnnotatedElementsVisitor}.
 */

class XsdSimpleTypeVisitor : public XsdAnnotatedElementsVisitor
{
private:
    /**
     * The {@link XsdSimpleType} instance which owns this {@link XsdSimpleTypeVisitor} instance. This way this visitor
     * instance can perform changes in the {@link XsdSimpleType} object.
     */
    std::shared_ptr<XsdSimpleType> m_owner;
public:
    using XsdAnnotatedElementsVisitor::visit;
  XsdSimpleTypeVisitor(std::shared_ptr<XsdSimpleType> owner)
        : XsdAnnotatedElementsVisitor(std::static_pointer_cast<XsdAnnotatedElements>(owner))
  {
        m_owner = owner;
    }

  std::shared_ptr<XsdSimpleType> getOwner(void)
    {
        return m_owner;
    }

  void visit(std::shared_ptr<XsdList> element)
    {
        XsdAnnotatedElementsVisitor::visit(element);
        m_owner->setList(element);
    }

  void visit(std::shared_ptr<XsdUnion> element)
    {
        XsdAnnotatedElementsVisitor::visit(element);
        m_owner->setUnion(element);
    }

  void visit(std::shared_ptr<XsdRestriction> element)
    {
        XsdAnnotatedElementsVisitor::visit(element);
        m_owner->setRestriction(element);
    }
};
