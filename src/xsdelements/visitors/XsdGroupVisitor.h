#pragma once

#include <xsdelements/XsdGroup.h>
#include <xsdelements/visitors/XsdAnnotatedElementsVisitor.h>

/**
 * Represents the restrictions of the {@link XsdGroup} element, which can contain {@link XsdAll}, {@link XsdSequence},
 * {@link XsdChoice} (represented by {@link XsdMultipleElements}) as children. Can also have {@link XsdAnnotation} as
 * children as per inheritance of {@link XsdAnnotatedElementsVisitor}.
 */
class XsdGroupVisitor : public XsdAnnotatedElementsVisitor
{
private:
    /**
     * The {@link XsdGroup} instance which owns this {@link XsdGroupVisitor} instance. This way this visitor instance
     * can perform changes in the {@link XsdGroup} object.
     */
  std::shared_ptr<XsdGroup> m_owner;
public:
  using XsdAnnotatedElementsVisitor::visit;
  XsdGroupVisitor(std::shared_ptr<XsdGroup> owner)
        : XsdAnnotatedElementsVisitor(owner)
  {
        m_owner = owner;
    }

  virtual std::shared_ptr<XsdAbstractElement> getOwner(void) override
    { return std::static_pointer_cast<XsdAbstractElement>(m_owner); }

  void visit(std::shared_ptr<XsdMultipleElements> element) override
    {
        XsdAnnotatedElementsVisitor::visit(element);
        m_owner->setChildElement(element);
    }
};
