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

  std::shared_ptr<XsdAll> getOwner(void)
    {
        return m_owner;
    }

  void visit(std::shared_ptr<XsdElement> element)
    {
        XsdAnnotatedElementsVisitor::visit(element);
        m_owner->addElement(element);
    }
};
