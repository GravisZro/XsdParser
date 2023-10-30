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
  XsdComplexContentVisitor(XsdComplexContent* _owner) : owner(_owner) { }
  ~XsdComplexContentVisitor(void) { delete owner; owner = nullptr; }

  /**
   * The {@link XsdComplexContent} instance which owns this {@link XsdComplexContentVisitor} instance. This way this
   * visitor instance can perform changes in the {@link XsdComplexContent} object.
   */
  XsdComplexContent* owner;

  virtual XsdAbstractElement* getOwner(void) override
    { return static_cast<XsdAbstractElement*>(owner); }

  virtual void visit(XsdAbstractElement* element) override
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
