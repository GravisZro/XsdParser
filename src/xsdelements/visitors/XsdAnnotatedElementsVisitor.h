#pragma once

#include <xsdelements/XsdAnnotatedElements.h>
#include <xsdelements/XsdAnnotation.h>

#include <xsdelements/visitors/XsdAbstractElementVisitor.h>

/**
 * Represents the restrictions of all the XSD elements that can have an {@link XsdAnnotation} as children.
 */
struct XsdAnnotatedElementsVisitor : XsdAbstractElementVisitor
{
  virtual void visit(std::shared_ptr<XsdAbstractElement> element) override
  {
    std::static_pointer_cast<XsdAnnotatedElements>(getOwner())->setAnnotation(
          std::static_pointer_cast<XsdAnnotation>(element));
  }
};

template<typename T>
struct XsdAnnotatedElementsVisitorWrapper : XsdAnnotatedElementsVisitor
{
  XsdAnnotatedElementsVisitorWrapper(std::shared_ptr<T> _owner) : owner(_owner) { }

  /**
   * The {@link XsdAnnotation} instance which owns this {@link XsdAnnotationVisitor} instance. This way this visitor
   * instance can perform changes in the {@link XsdAnnotation} object.
   */
  std::shared_ptr<T> owner;

  virtual std::shared_ptr<XsdAbstractElement> getOwner(void) override
    { return std::static_pointer_cast<XsdAbstractElement>(owner); }
};
