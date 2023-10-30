#pragma once

#include <xsdelements/XsdAnnotation.h>
#include <xsdelements/XsdAppInfo.h>
#include <xsdelements/XsdDocumentation.h>
#include <xsdelements/visitors/XsdAbstractElementVisitor.h>

/**
 * Represents the restrictions of the {@link XsdAnnotation} element, which can only contain {@link XsdAppInfo} and
 * {@link XsdDocumentation} as children.
 */
struct XsdAnnotationVisitor : XsdAbstractElementVisitor
{
  XsdAnnotationVisitor(XsdAnnotation* _owner) : owner(_owner) { }

  /**
   * The {@link XsdAnnotation} instance which owns this {@link XsdAnnotationVisitor} instance. This way this visitor
   * instance can perform changes in the {@link XsdAnnotation} object.
   */
  XsdAnnotation* owner;

  virtual XsdAbstractElement* getOwner(void) override
    { return static_cast<XsdAbstractElement*>(owner); }

  virtual void visit(XsdAbstractElement* element) override
  {
    assert(dynamic_cast<XsdAnnotationChildren*>(element) != nullptr);
    owner->add(static_cast<XsdAnnotationChildren*>(element));
  }
};
