#pragma once

#include <xsdelements/XsdAnnotatedElements.h>
#include <xsdelements/XsdAnnotation.h>

#include <xsdelements/visitors/XsdAbstractElementVisitor.h>

/**
 * Represents the restrictions of all the XSD elements that can have an {@link XsdAnnotation} as children.
 */
struct XsdAnnotatedElementsVisitor : XsdAbstractElementVisitor
{
  virtual void visit(XsdAbstractElement* element) override
  {
    static_cast<XsdAnnotatedElements*>(getOwner())->setAnnotation(
          static_cast<XsdAnnotation*>(element));
  }
};

template<typename T>
struct XsdAnnotatedElementsVisitorWrapper : XsdAnnotatedElementsVisitor
{
  XsdAnnotatedElementsVisitorWrapper(T* _owner) : owner(_owner) { }

  /**
   * The {@link XsdAnnotation} instance which owns this {@link XsdAnnotationVisitor} instance. This way this visitor
   * instance can perform changes in the {@link XsdAnnotation} object.
   */
  T* owner;

  virtual XsdAbstractElement* getOwner(void) override
    { return static_cast<XsdAbstractElement*>(owner); }
};
