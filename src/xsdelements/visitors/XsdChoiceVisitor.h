#pragma once


// #include <xsdelements/*.h>
#include <xsdelements/XsdElement.h>
#include <xsdelements/XsdChoice.h>
#include <xsdelements/visitors/XsdAnnotatedElementsVisitor.h>

/**
 * Represents the restrictions of the {@link XsdChoice} element, which can contain {@link XsdElement}, {@link XsdChoice},
 * {@link XsdGroup} or {@link XsdSequence} as children. Can also have {@link XsdAnnotation} children as per inheritance
 * of {@link XsdAnnotatedElementsVisitor}.
 */
class XsdChoiceVisitor : public XsdAnnotatedElementsVisitor
{
private:
    /**
     * The {@link XsdChoice} instance which owns this {@link XsdChoiceVisitor} instance. This way this visitor instance
     * can perform changes in the {@link XsdChoice} object.
     */
    std::shared_ptr<XsdChoice> m_owner;
public:
    using XsdAnnotatedElementsVisitor::visit;
  XsdChoiceVisitor(std::shared_ptr<XsdChoice> owner)
    : XsdAnnotatedElementsVisitor(owner)
  {
        m_owner = owner;
    }

  std::shared_ptr<XsdChoice> getOwner(void)
    {
        return m_owner;
    }

  void visit(std::shared_ptr<XsdElement> element)
    {
        XsdAnnotatedElementsVisitor::visit(element);
        m_owner->addElement(element);
    }

  void visit(std::shared_ptr<XsdGroup> element)
    {
        XsdAnnotatedElementsVisitor::visit(element);
        m_owner->addElement(element);
    }

  void visit(std::shared_ptr<XsdChoice> element)
    {
        XsdAnnotatedElementsVisitor::visit(element);
        m_owner->addElement(element);
    }

  void visit(std::shared_ptr<XsdSequence> element)
    {
        XsdAnnotatedElementsVisitor::visit(element);
        m_owner->addElement(element);
    }
};
