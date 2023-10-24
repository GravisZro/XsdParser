#pragma once

#include <xsdelements/XsdAll.h>
#include <xsdelements/XsdAnnotation.h>
#include <xsdelements/XsdElement.h>
#include <xsdelements/visitors/XsdNamedElementsVisitor.h>

/**
 * Represents the restrictions of the {@link XsdAll} element, which can only contain {@link XsdElement} as children.
 * Can also have {@link XsdAnnotation} children as per inheritance of {@link XsdAnnotatedElementsVisitor}.
 */
struct XsdAllVisitor : XsdNamedElementsVisitor
{
  XsdAllVisitor(std::shared_ptr<XsdAll> _owner) : owner(_owner) { }

  /**
   * The {@link XsdAll} instance which owns this {@link XsdAllVisitor} instance. This way this visitor instance can
   * perform changes in the {@link XsdAll} object.
   */
  std::shared_ptr<XsdAll> owner;

  virtual std::shared_ptr<XsdAbstractElement> getOwner(void) override
    { return std::static_pointer_cast<XsdAbstractElement>(owner); }

  virtual void visit(std::shared_ptr<XsdAbstractElement> element) override
  {
    XsdNamedElementsVisitor::visit(element);
    std::static_pointer_cast<XsdAll>(owner)->addElement(element);
  }
};
