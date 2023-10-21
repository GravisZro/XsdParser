#pragma once

#include <xsdelements/XsdAll.h>
#include <xsdelements/XsdAnnotation.h>
#include <xsdelements/XsdElement.h>
#include <xsdelements/visitors/XsdAnnotatedElementsVisitor.h>

/**
 * Represents the restrictions of the {@link XsdAll} element, which can only contain {@link XsdElement} as children.
 * Can also have {@link XsdAnnotation} children as per inheritance of {@link XsdAnnotatedElementsVisitor}.
 */
class XsdAllVisitor : public XsdAnnotatedElementsVisitor
{
private:
    /**
     * The {@link XsdAll} instance which owns this {@link XsdAllVisitor} instance. This way this visitor instance can
     * perform changes in the {@link XsdAll} object.
     */
    std::shared_ptr<XsdAll> m_owner;
public:
    using XsdAnnotatedElementsVisitor::visit;
  XsdAllVisitor(std::shared_ptr<XsdAll> owner)
    : XsdAnnotatedElementsVisitor(owner)
  {
    m_owner = owner;
  }

  virtual std::shared_ptr<XsdAbstractElement> getOwner(void) override
    { return std::static_pointer_cast<XsdAbstractElement>(m_owner); }

  void visit(std::shared_ptr<XsdElement> element) override
    {
        XsdAnnotatedElementsVisitor::visit(element);
        m_owner->addElement(element);
    }
};
