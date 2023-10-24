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
  XsdGroupVisitor(std::shared_ptr<XsdGroup> _owner) : owner(_owner) { }

  /**
   * The {@link XsdGroup} instance which owns this {@link XsdGroupVisitor} instance. This way this visitor instance
   * can perform changes in the {@link XsdGroup} object.
   */
  std::shared_ptr<XsdGroup> owner;

  virtual std::shared_ptr<XsdAbstractElement> getOwner(void) override
    { return std::static_pointer_cast<XsdAbstractElement>(owner); }

  void visit(std::shared_ptr<XsdAbstractElement> element) override
  {
    XsdNamedElementsVisitor::visit(element);
    owner->setChildElement(std::static_pointer_cast<XsdMultipleElements>(element));
  }
};
