#pragma once


// #include <xsdelements/*.h>
#include <xsdelements/visitors/XsdAnnotatedElementsVisitor.h>

/**
 * Represents the restrictions of the {@link XsdSequence} element, which can contain {@link XsdElement}, {@link XsdGroup},
 * {@link XsdChoice} or {@link XsdSequence} as children. Can also have {@link XsdAnnotation} as children as per
 * inheritance of {@link XsdAnnotatedElementsVisitor}.
 */
class XsdSequenceVisitor : public XsdAnnotatedElementsVisitor
{
private:
    /**
     * The {@link XsdSequence} instance which owns this {@link XsdSequenceVisitor} instance. This way this visitor instance
     * can perform changes in the {@link XsdSequence} object.
     */
    std::shared_ptr<XsdSequence> m_owner;
public:
    using XsdAnnotatedElementsVisitor::visit;
  XsdSequenceVisitor(std::shared_ptr<XsdSequence> owner)
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

  void visit(std::shared_ptr<XsdGroup> element) override
    {
        XsdAnnotatedElementsVisitor::visit(element);

        m_owner->addElement(element);
    }

  void visit(std::shared_ptr<XsdChoice> element) override
    {
        XsdAnnotatedElementsVisitor::visit(element);

        m_owner->addElement(element);
    }

  void visit(std::shared_ptr<XsdSequence> element) override
  {
        XsdAnnotatedElementsVisitor::visit(element);
        m_owner->addElement(element);
  }
};
