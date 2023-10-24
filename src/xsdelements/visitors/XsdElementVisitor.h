#pragma once

#include <xsdelements/XsdComplexType.h>
#include <xsdelements/XsdElement.h>
#include <xsdelements/XsdSimpleType.h>
#include <xsdelements/elementswrapper/ReferenceBase.h>
#include <xsdelements/visitors/XsdNamedElementsVisitor.h>

/**
 * Represents the restrictions of the {@link XsdElement} element, which can only contain {@link XsdSimpleType} or
 * {@link XsdComplexType} as children. Can also have {@link XsdAnnotation} children as per inheritance of
 * {@link XsdAnnotatedElementsVisitor}.
 */
struct XsdElementVisitor : XsdNamedElementsVisitor
{
  XsdElementVisitor(std::shared_ptr<XsdElement> _owner) : owner(_owner) { }

  /**
   * The {@link XsdElement} instance which owns this {@link XsdElementVisitor} instance. This way this visitor instance
   * can perform changes in the {@link XsdElement} object.
   */
  std::shared_ptr<XsdElement> owner;

  virtual std::shared_ptr<XsdAbstractElement> getOwner(void) override
    { return std::static_pointer_cast<XsdAbstractElement>(owner); }

  virtual void visit(std::shared_ptr<XsdAbstractElement> element) override
  {
    XsdNamedElementsVisitor::visit(element);
    if(std::dynamic_pointer_cast<XsdComplexType>(element))
      owner->setComplexType(ReferenceBase::createFromXsd(element));
    else if(std::dynamic_pointer_cast<XsdSimpleType>(element))
      owner->setSimpleType(ReferenceBase::createFromXsd(element));
  }
};
