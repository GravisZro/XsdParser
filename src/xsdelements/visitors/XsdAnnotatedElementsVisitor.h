#pragma once

#include <xsdelements/XsdAnnotatedElements.h>
#include <xsdelements/XsdAnnotation.h>

#include <xsdelements/visitors/XsdAbstractElementVisitor.h>

/**
 * Represents the restrictions of all the XSD elements that can have an {@link XsdAnnotation} as children.
 */
class XsdAnnotatedElementsVisitor : public XsdAbstractElementVisitor
{
private:
    /**
     * The {@link XsdAnnotatedElements} instance which owns this {@link XsdAnnotatedElementsVisitor} instance. This way
     * this visitor instance can perform changes in the {@link XsdAnnotatedElements} objects.
     */
  std::shared_ptr<XsdAnnotatedElements> m_owner;
public:
  using XsdAbstractElementVisitor::visit;
  XsdAnnotatedElementsVisitor(std::shared_ptr<XsdAnnotatedElements> owner){
        m_owner = owner;
    }

  void visit(std::shared_ptr<XsdAnnotation> element) override
    {
        XsdAbstractElementVisitor::visit(element);
        m_owner->setAnnotation(element);
    }

  virtual std::shared_ptr<XsdAbstractElement> getOwner(void) override
    { return std::static_pointer_cast<XsdAbstractElement>(m_owner); }
};
