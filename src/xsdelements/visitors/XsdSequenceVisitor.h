#pragma once

#include <xsdelements/visitors/XsdAnnotatedElementsVisitor.h>
#include <xsdelements/XsdElement.h>
#include <xsdelements/XsdGroup.h>
#include <xsdelements/XsdChoice.h>
#include <xsdelements/XsdSequence.h>

/**
 * Represents the restrictions of the {@link XsdSequence} element, which can contain {@link XsdElement}, {@link XsdGroup},
 * {@link XsdChoice} or {@link XsdSequence} as children. Can also have {@link XsdAnnotation} as children as per
 * inheritance of {@link XsdAnnotatedElementsVisitor}.
 */
struct XsdSequenceVisitor : XsdAnnotatedElementsVisitor
{
  XsdSequenceVisitor(XsdSequence* _owner) : owner(_owner) { }

  /**
   * The {@link XsdSequence} instance which owns this {@link XsdSequenceVisitor} instance. This way this visitor instance
   * can perform changes in the {@link XsdSequence} object.
   */
  XsdSequence* owner;

  virtual XsdAbstractElement* getOwner(void) override
    { return static_cast<XsdAbstractElement*>(owner); }

  void visit(XsdAbstractElement* element) override
  {
    assert(dynamic_cast<XsdElement* >(element) != nullptr ||
           dynamic_cast<XsdGroup*   >(element) != nullptr ||
           dynamic_cast<XsdChoice*  >(element) != nullptr ||
           dynamic_cast<XsdSequence*>(element) != nullptr);

    XsdAnnotatedElementsVisitor::visit(element);
    owner->addElement(element);
  }
};
