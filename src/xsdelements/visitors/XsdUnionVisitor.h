#pragma once

#include <xsdelements/XsdSimpleType.h>
#include <xsdelements/XsdUnion.h>
#include <xsdelements/visitors/XsdAnnotatedElementsVisitor.h>

/**
 * Represents the restrictions of the {@link XsdUnion} element, which can only contain {@link XsdSimpleType} as children.
 * Can also have {@link XsdAnnotation} as children as per inheritance of {@link XsdAnnotatedElementsVisitor}.
 */
struct XsdUnionVisitor : XsdAnnotatedElementsVisitor
{
  XsdUnionVisitor(std::shared_ptr<XsdUnion> _owner) : owner(_owner) { }

  /**
   * The {@link XsdUnion} instance which owns this {@link XsdUnionVisitor} instance. This way this visitor instance
   * can perform changes in the {@link XsdUnion} object.
   */
  std::shared_ptr<XsdUnion> owner;

  virtual std::shared_ptr<XsdAbstractElement> getOwner(void) override
    { return std::static_pointer_cast<XsdAbstractElement>(owner); }

  void visit(std::shared_ptr<XsdAbstractElement> element) override
  {
    XsdAnnotatedElementsVisitor::visit(element);
    owner->add(std::static_pointer_cast<XsdSimpleType>(element));
  }
};
