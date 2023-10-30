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
  XsdUnionVisitor(XsdUnion* _owner) : owner(_owner) { }
  ~XsdUnionVisitor(void) { delete owner; owner = nullptr; }

  /**
   * The {@link XsdUnion} instance which owns this {@link XsdUnionVisitor} instance. This way this visitor instance
   * can perform changes in the {@link XsdUnion} object.
   */
  XsdUnion* owner;

  virtual XsdAbstractElement* getOwner(void) override
    { return static_cast<XsdAbstractElement*>(owner); }

  void visit(XsdAbstractElement* element) override
  {
    XsdAnnotatedElementsVisitor::visit(element);
    owner->add(static_cast<XsdSimpleType*>(element));
  }
};
