#pragma once


#include <xsdelements/XsdAnnotation.h>
#include <xsdelements/XsdAttribute.h>
#include <xsdelements/XsdAttributeGroup.h>
#include <xsdelements/elementswrapper/ReferenceBase.h>
#include <xsdelements/visitors/XsdNamedElementsVisitor.h>

/**
 * Represents the restrictions of the {@link XsdAttributeGroup} element, which can only contain {@link XsdAttribute}
 * elements as children. Can also have {@link XsdAnnotation} children as per inheritance of
 * {@link XsdAnnotatedElementsVisitor}.
 */
struct XsdAttributeGroupVisitor : XsdNamedElementsVisitor
{
  XsdAttributeGroupVisitor(XsdAttributeGroup* _owner) : owner(_owner) { }

  /**
   * The {@link XsdAttributeGroup} instance which owns this {@link XsdAttributeGroupVisitor} instance. This way this
   * visitor instance can perform changes in the {@link XsdAttributeGroup} object.
   */
  XsdAttributeGroup* owner;

  virtual XsdAbstractElement* getOwner(void) override
    { return static_cast<XsdAbstractElement*>(owner); }

  virtual void visit(XsdAbstractElement* element) override
  {
    XsdNamedElementsVisitor::visit(element);

    if(dynamic_cast<XsdAttribute*>(element) != nullptr)
      owner->addAttribute(ReferenceBase::createFromXsd(element));
    else if(dynamic_cast<XsdAttributeGroup*>(element) != nullptr)
      owner->addAttributeGroup(ReferenceBase::createFromXsd(element));
    else
      assert(false);
  }
};
