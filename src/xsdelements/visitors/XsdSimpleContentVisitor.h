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
  XsdSimpleContentVisitor(XsdSimpleContent* _owner) : owner(_owner) { }

  /**
   * The {@link XsdSimpleContent} instance which owns this {@link XsdSimpleContentVisitor} instance. This way this
   * visitor instance can perform changes in the {@link XsdSimpleContent} object.
   */
  XsdSimpleContent* owner;

  virtual XsdAbstractElement* getOwner(void) override
    { return static_cast<XsdAbstractElement*>(owner); }

  void visit(XsdAbstractElement* element) override
  {
    XsdAnnotatedElementsVisitor::visit(element);
    if(dynamic_cast<XsdRestriction*>(element) != nullptr)
      owner->setRestriction(ReferenceBase::createFromXsd(element));
    else if(dynamic_cast<XsdExtension*>(element) != nullptr)
      owner->setExtension(ReferenceBase::createFromXsd(element));
    else
      assert(false);
  }
};
