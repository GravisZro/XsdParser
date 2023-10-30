#pragma once

#include <xsdelements/elementswrapper/ReferenceBase.h>
#include <xsdelements/XsdMultipleElements.h>
#include <xsdelements/XsdComplexType.h>
#include <xsdelements/XsdGroup.h>
#include <xsdelements/XsdComplexContent.h>
#include <xsdelements/XsdSimpleContent.h>

#include <xsdelements/visitors/AttributesVisitor.h>

/**
 * Represents the restrictions of the {@link XsdComplexType} element, which can contain the following children:
 *      * {@link XsdAll}, {@link XsdSequence}, {@link XsdChoice} (represented by {@link XsdMultipleElements});
 *      * {@link XsdGroup};
 *      * {@link XsdComplexContent};
 *      * {@link XsdSimpleContent};
 * Can also have {@link XsdAttribute} and {@link XsdAttributeGroup} as children as per inheritance of {@link AttributesVisitor}.
 * Can also have {@link XsdAnnotation} children as per inheritance of {@link XsdAnnotatedElementsVisitor}.
 */
struct XsdComplexTypeVisitor : AttributesVisitor
{
  XsdComplexTypeVisitor(XsdComplexType* _owner) : owner(_owner) { }

  /**
   * The {@link XsdComplexType} instance which owns this {@link XsdComplexTypeVisitor} instance. This way this visitor
   * instance can perform changes in the {@link XsdComplexType} object.
   */
  XsdComplexType* owner;

  virtual XsdAbstractElement* getOwner(void) override
    { return static_cast<XsdAbstractElement*>(owner); }

  virtual void visit(XsdAbstractElement* element) override
  {
    XsdNamedElementsVisitor::visit(element);
    AttributesVisitor::visit(element);

    if(dynamic_cast<XsdMultipleElements*>(element) != nullptr ||
       dynamic_cast<XsdGroup*>(element) != nullptr)
      owner->setChildElement(ReferenceBase::createFromXsd(element));
    else if(dynamic_cast<XsdComplexContent*>(element) != nullptr)
      owner->setComplexContent(static_cast<XsdComplexContent*>(element));
    else if(dynamic_cast<XsdSimpleContent*>(element) != nullptr)
      owner->setSimpleContent(static_cast<XsdSimpleContent*>(element));
  }
};
