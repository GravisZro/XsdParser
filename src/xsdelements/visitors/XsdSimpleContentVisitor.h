#pragma once


#include <xsdelements/XsdAnnotation.h>
#include <xsdelements/XsdExtension.h>
#include <xsdelements/XsdRestriction.h>
#include <xsdelements/XsdSimpleContent.h>
#include <xsdelements/elementswrapper/ReferenceBase.h>
#include <xsdelements/visitors/XsdAnnotatedElementsVisitor.h>

/**
 * Represents the restrictions of the {@link XsdSimpleContent} element, which can only contain {@link XsdRestriction} or
 * {@link XsdExtension} as children. Can also have {@link XsdAnnotation} as children as per inheritance of
 * {@link XsdAnnotatedElementsVisitor}.
 */
struct XsdSimpleContentVisitor : XsdAnnotatedElementsVisitor
{
  XsdSimpleContentVisitor(std::shared_ptr<XsdSimpleContent> _owner) : owner(_owner) { }

  /**
   * The {@link XsdSimpleContent} instance which owns this {@link XsdSimpleContentVisitor} instance. This way this
   * visitor instance can perform changes in the {@link XsdSimpleContent} object.
   */
  std::shared_ptr<XsdSimpleContent> owner;

  virtual std::shared_ptr<XsdAbstractElement> getOwner(void) override
    { return std::static_pointer_cast<XsdAbstractElement>(owner); }

  void visit(std::shared_ptr<XsdAbstractElement> element) override
  {
    XsdAnnotatedElementsVisitor::visit(element);
    if(std::dynamic_pointer_cast<XsdRestriction>(element))
      owner->setRestriction(ReferenceBase::createFromXsd(element));
    else if(std::dynamic_pointer_cast<XsdExtension>(element))
      owner->setExtension(ReferenceBase::createFromXsd(element));
    else
      assert(false);
  }
};
