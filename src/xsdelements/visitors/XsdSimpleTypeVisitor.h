#pragma once

#include <xsdelements/XsdAnnotation.h>
#include <xsdelements/XsdSimpleType.h>
#include <xsdelements/XsdUnion.h>
#include <xsdelements/XsdList.h>
#include <xsdelements/XsdRestriction.h>
#include <xsdelements/visitors/XsdNamedElementsVisitor.h>

/**
 * Represents the restrictions of the {@link XsdSimpleType} element, which can contain {@link XsdList}, {@link XsdUnion}
 * or {@link XsdRestriction} as children. Can also have {@link XsdAnnotation} as children as per inheritance of
 * {@link XsdAnnotatedElementsVisitor}.
 */

struct XsdSimpleTypeVisitor : XsdNamedElementsVisitor
{
  XsdSimpleTypeVisitor(XsdSimpleType* _owner) : owner(_owner) { }
  ~XsdSimpleTypeVisitor(void) { delete owner; owner = nullptr; }

  /**
   * The {@link XsdSimpleType} instance which owns this {@link XsdSimpleTypeVisitor} instance. This way this visitor
   * instance can perform changes in the {@link XsdSimpleType} object.
   */
  XsdSimpleType* owner;

  virtual XsdAbstractElement* getOwner(void) override
    { return static_cast<XsdAbstractElement*>(owner); }

  void visit(XsdAbstractElement* element) override
  {
    XsdNamedElementsVisitor::visit(element);
    if(dynamic_cast<XsdList*>(element) != nullptr)
      owner->setList(static_cast<XsdList*>(element));
    else if(dynamic_cast<XsdUnion*>(element) != nullptr)
      owner->setUnion(static_cast<XsdUnion*>(element));
    else if(dynamic_cast<XsdRestriction*>(element) != nullptr)
      owner->setRestriction(static_cast<XsdRestriction*>(element));
  }
};
