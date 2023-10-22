#pragma once


#include <xsdelements/XsdAnnotation.h>
#include <xsdelements/XsdAttribute.h>
#include <xsdelements/XsdAttributeGroup.h>
#include <xsdelements/elementswrapper/ReferenceBase.h>
#include <xsdelements/visitors/XsdAnnotatedElementsVisitor.h>

/**
 * Represents the restrictions of the {@link XsdAttributeGroup} element, which can only contain {@link XsdAttribute}
 * elements as children. Can also have {@link XsdAnnotation} children as per inheritance of
 * {@link XsdAnnotatedElementsVisitor}.
 */
struct XsdAttributeGroupVisitor : XsdAnnotatedElementsVisitor
{
  XsdAttributeGroupVisitor(std::shared_ptr<XsdAttributeGroup> _owner) : owner(_owner) { }

  /**
   * The {@link XsdAttributeGroup} instance which owns this {@link XsdAttributeGroupVisitor} instance. This way this
   * visitor instance can perform changes in the {@link XsdAttributeGroup} object.
   */
  std::shared_ptr<XsdAttributeGroup> owner;

  virtual std::shared_ptr<XsdAbstractElement> getOwner(void) override
    { return std::static_pointer_cast<XsdAbstractElement>(owner); }

  virtual void visit(std::shared_ptr<XsdAbstractElement> element) override
  {
    XsdAnnotatedElementsVisitor::visit(element);

    if(std::dynamic_pointer_cast<XsdAttribute>(element))
      owner->addAttribute(ReferenceBase::createFromXsd(element));
    else if(std::dynamic_pointer_cast<XsdAttributeGroup>(element))
      owner->addAttributeGroup(ReferenceBase::createFromXsd(element));
    else
      assert(false);
  }
};
