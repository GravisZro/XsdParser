#pragma once

#include <xsdelements/XsdGroup.h>
#include <xsdelements/visitors/XsdNamedElementsVisitor.h>

/**
 * Represents the restrictions of the {@link XsdGroup} element, which can contain {@link XsdAll}, {@link XsdSequence},
 * {@link XsdChoice} (represented by {@link XsdMultipleElements}) as children. Can also have {@link XsdAnnotation} as
 * children as per inheritance of {@link XsdAnnotatedElementsVisitor}.
 */
struct XsdGroupVisitor : XsdNamedElementsVisitor
{
  XsdGroupVisitor(XsdGroup* _owner) : owner(_owner) { }
  ~XsdGroupVisitor(void) { delete owner; owner = nullptr; }

  /**
   * The {@link XsdGroup} instance which owns this {@link XsdGroupVisitor} instance. This way this visitor instance
   * can perform changes in the {@link XsdGroup} object.
   */
  XsdGroup* owner;

  virtual XsdAbstractElement* getOwner(void) override
    { return static_cast<XsdAbstractElement*>(owner); }

  void visit(XsdAbstractElement* element) override
  {
    XsdNamedElementsVisitor::visit(element);
    owner->setChildElement(static_cast<XsdMultipleElements*>(element));
  }
};
