#pragma once

#include <xsdelements/visitors/XsdAnnotatedElementsVisitor.h>
#include <xsdelements/XsdSequence.h>

/**
 * Represents the restrictions of the {@link XsdSequence} element, which can contain {@link XsdElement}, {@link XsdGroup},
 * {@link XsdChoice} or {@link XsdSequence} as children. Can also have {@link XsdAnnotation} as children as per
 * inheritance of {@link XsdAnnotatedElementsVisitor}.
 */
struct XsdSequenceVisitor : XsdAnnotatedElementsVisitor
{
  XsdSequenceVisitor(std::shared_ptr<XsdSequence> _owner) : owner(_owner) { }

  /**
   * The {@link XsdSequence} instance which owns this {@link XsdSequenceVisitor} instance. This way this visitor instance
   * can perform changes in the {@link XsdSequence} object.
   */
  std::shared_ptr<XsdSequence> owner;

  virtual std::shared_ptr<XsdAbstractElement> getOwner(void) override
    { return std::static_pointer_cast<XsdAbstractElement>(owner); }

  void visit(std::shared_ptr<XsdAbstractElement> element) override
  {
    assert(std::dynamic_pointer_cast<XsdElement>(element) ||
           std::dynamic_pointer_cast<XsdGroup>(element) ||
           std::dynamic_pointer_cast<XsdChoice>(element) ||
           std::dynamic_pointer_cast<XsdSequence>(element));

    XsdAnnotatedElementsVisitor::visit(element);
    owner->addElement(element);
  }
};
