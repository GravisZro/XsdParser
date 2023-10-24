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
  XsdSimpleTypeVisitor(std::shared_ptr<XsdSimpleType> _owner) : owner(_owner) { }

  /**
   * The {@link XsdSimpleType} instance which owns this {@link XsdSimpleTypeVisitor} instance. This way this visitor
   * instance can perform changes in the {@link XsdSimpleType} object.
   */
  std::shared_ptr<XsdSimpleType> owner;

  virtual std::shared_ptr<XsdAbstractElement> getOwner(void) override
    { return std::static_pointer_cast<XsdAbstractElement>(owner); }

  void visit(std::shared_ptr<XsdAbstractElement> element) override
  {
    XsdNamedElementsVisitor::visit(element);
    if(std::dynamic_pointer_cast<XsdList>(element))
      owner->setList(std::static_pointer_cast<XsdList>(element));
    else if(std::dynamic_pointer_cast<XsdUnion>(element))
      owner->setUnion(std::static_pointer_cast<XsdUnion>(element));
    else if(std::dynamic_pointer_cast<XsdList>(element))
      owner->setRestriction(std::static_pointer_cast<XsdRestriction>(element));
  }
};
