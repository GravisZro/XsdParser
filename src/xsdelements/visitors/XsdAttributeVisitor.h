#pragma once


#include <xsdelements/XsdAnnotation.h>
#include <xsdelements/XsdAttribute.h>
#include <xsdelements/XsdSimpleType.h>
#include <xsdelements/elementswrapper/ReferenceBase.h>
#include <xsdelements/visitors/XsdNamedElementsVisitor.h>

/**
 * Represents the restrictions of the {@link XsdAttribute} element, which can only contain {@link XsdSimpleType} elements
 * as children. Can also have {@link XsdAnnotation} children as per inheritance of {@link XsdAnnotatedElementsVisitor}.
 */
struct XsdAttributeVisitor : XsdNamedElementsVisitor
{
  XsdAttributeVisitor(std::shared_ptr<XsdAttribute> _owner) : owner(_owner) { }

  /**
   * The {@link XsdAttribute} instance which owns this {@link XsdAttributeVisitor} instance. This way this visitor
   * instance can perform changes in the {@link XsdAttribute} object.
   */
  std::shared_ptr<XsdAttribute> owner;

  virtual std::shared_ptr<XsdAbstractElement> getOwner(void) override
    { return std::static_pointer_cast<XsdAbstractElement>(owner); }

  virtual void visit(std::shared_ptr<XsdAbstractElement> element) override
  {
    XsdNamedElementsVisitor::visit(element);
    owner->setSimpleType(ReferenceBase::createFromXsd(element));
  }
};
