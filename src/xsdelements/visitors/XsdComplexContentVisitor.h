#pragma once


#include <xsdelements/XsdComplexContent.h>
#include <xsdelements/XsdExtension.h>
#include <xsdelements/XsdRestriction.h>
#include <xsdelements/elementswrapper/ReferenceBase.h>
#include <xsdelements/visitors/XsdAnnotatedElementsVisitor.h>

/**
 * Represents the restrictions of the {@link XsdComplexContent} element, which can only contain {@link XsdRestriction}
 * and {@link XsdExtension} as children. Can also have xsd:annotation children as per inheritance of
 * {@link XsdAnnotatedElementsVisitor}.
 */
struct XsdComplexContentVisitor : XsdAnnotatedElementsVisitor
{
  XsdComplexContentVisitor(std::shared_ptr<XsdComplexContent> _owner) : owner(_owner) { }

  /**
   * The {@link XsdComplexContent} instance which owns this {@link XsdComplexContentVisitor} instance. This way this
   * visitor instance can perform changes in the {@link XsdComplexContent} object.
   */
  std::shared_ptr<XsdComplexContent> owner;

  virtual std::shared_ptr<XsdAbstractElement> getOwner(void) override
    { return std::static_pointer_cast<XsdAbstractElement>(owner); }

  virtual void visit(std::shared_ptr<XsdAbstractElement> element) override
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
