#pragma once

#include <xsdelements/XsdElement.h>
#include <xsdelements/XsdGroup.h>
#include <xsdelements/XsdChoice.h>
#include <xsdelements/XsdSequence.h>
#include <xsdelements/visitors/XsdAnnotatedElementsVisitor.h>


/**
 * Represents the restrictions of the {@link XsdChoice} element, which can contain {@link XsdElement}, {@link XsdChoice},
 * {@link XsdGroup} or {@link XsdSequence} as children. Can also have {@link XsdAnnotation} children as per inheritance
 * of {@link XsdAnnotatedElementsVisitor}.
 */
struct XsdChoiceVisitor : XsdAnnotatedElementsVisitor
{
  XsdChoiceVisitor(XsdChoice* _owner) : owner(_owner) { }
  ~XsdChoiceVisitor(void) { delete owner; owner = nullptr; }

  /**
   * The {@link XsdChoice} instance which owns this {@link XsdChoiceVisitor} instance. This way this visitor instance
   * can perform changes in the {@link XsdChoice} object.
   */
  XsdChoice* owner;

  virtual XsdAbstractElement* getOwner(void) override
    { return static_cast<XsdAbstractElement*>(owner); }

  virtual void visit(XsdAbstractElement* element) override
  {
    assert(dynamic_cast<XsdElement *>(element) != nullptr ||
           dynamic_cast<XsdGroup   *>(element) != nullptr ||
           dynamic_cast<XsdChoice  *>(element) != nullptr ||
           dynamic_cast<XsdSequence*>(element) != nullptr);

    XsdAnnotatedElementsVisitor::visit(element);
    owner->addElement(element);
  }
};
