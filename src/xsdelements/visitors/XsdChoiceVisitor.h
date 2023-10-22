#pragma once

#include <xsdelements/XsdChoice.h>
#include <xsdelements/visitors/XsdAnnotatedElementsVisitor.h>

class XsdElement;
class XsdGroup;
class XsdChoice;
class XsdSequence;

/**
 * Represents the restrictions of the {@link XsdChoice} element, which can contain {@link XsdElement}, {@link XsdChoice},
 * {@link XsdGroup} or {@link XsdSequence} as children. Can also have {@link XsdAnnotation} children as per inheritance
 * of {@link XsdAnnotatedElementsVisitor}.
 */
struct XsdChoiceVisitor : XsdAnnotatedElementsVisitor
{
  XsdChoiceVisitor(std::shared_ptr<XsdChoice> _owner) : owner(_owner) { }

  /**
   * The {@link XsdChoice} instance which owns this {@link XsdChoiceVisitor} instance. This way this visitor instance
   * can perform changes in the {@link XsdChoice} object.
   */
  std::shared_ptr<XsdChoice> owner;

  virtual std::shared_ptr<XsdAbstractElement> getOwner(void) override
    { return std::static_pointer_cast<XsdAbstractElement>(owner); }

  virtual void visit(std::shared_ptr<XsdAbstractElement> element) override
  {
    assert(std::dynamic_pointer_cast<XsdElement >(element) ||
           std::dynamic_pointer_cast<XsdGroup   >(element) ||
           std::dynamic_pointer_cast<XsdChoice  >(element) ||
           std::dynamic_pointer_cast<XsdSequence>(element));

    XsdAnnotatedElementsVisitor::visit(element);
    owner->addElement(element);
  }
};
