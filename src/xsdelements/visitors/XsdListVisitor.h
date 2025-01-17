#pragma once

#include <xsdelements/XsdAnnotation.h>
#include <xsdelements/XsdList.h>
#include <xsdelements/XsdSimpleType.h>
#include <xsdelements/exceptions/ParsingException.h>
#include <xsdelements/visitors/XsdAnnotatedElementsVisitor.h>
/**
 * Represents the restrictions of the {@link XsdList} element, which can only contain {@link XsdSimpleType} as children.
 * Can also have {@link XsdAnnotation} children as per inheritance of {@link XsdAnnotatedElementsVisitor}.
 */
struct XsdListVisitor : XsdAnnotatedElementsVisitor
{
  XsdListVisitor(XsdList* _owner) : owner(_owner) { }
  ~XsdListVisitor(void) { delete owner; owner = nullptr; }

  /**
   * The {@link XsdList} instance which owns this {@link XsdListVisitor} instance. This way this visitor instance can
   * perform changes in the {@link XsdList} object.
   */
  XsdList* owner;

  virtual XsdAbstractElement* getOwner(void) override
    { return static_cast<XsdAbstractElement*>(owner); }

  void visit(XsdAbstractElement* element) override
  {
    XsdAnnotatedElementsVisitor::visit(element);

    if (owner->getItemType())
      throw ParsingException(TAG<XsdList>::xsd + " element: The element cannot have both the itemType attribute and a " + TAG<XsdSimpleType>::xsd + " element as content at the same time." );

    owner->setSimpleType(static_cast<XsdSimpleType*>(element));
  }
};
