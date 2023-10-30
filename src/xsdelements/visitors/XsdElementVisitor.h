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
  XsdElementVisitor(XsdElement* _owner) : owner(_owner) { }

  /**
   * The {@link XsdElement} instance which owns this {@link XsdElementVisitor} instance. This way this visitor instance
   * can perform changes in the {@link XsdElement} object.
   */
  XsdElement* owner;

  virtual XsdAbstractElement* getOwner(void) override
    { return static_cast<XsdAbstractElement*>(owner); }

  virtual void visit(XsdAbstractElement* element) override
  {
    XsdNamedElementsVisitor::visit(element);
    if(dynamic_cast<XsdComplexType*>(element) != nullptr)
      owner->setComplexType(ReferenceBase::createFromXsd(element));
    else if(dynamic_cast<XsdSimpleType*>(element) != nullptr)
      owner->setSimpleType(ReferenceBase::createFromXsd(element));
  }
};
