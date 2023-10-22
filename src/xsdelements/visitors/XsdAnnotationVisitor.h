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
  XsdAnnotationVisitor(std::shared_ptr<XsdAnnotation> _owner) : owner(_owner) { }

  /**
   * The {@link XsdAnnotation} instance which owns this {@link XsdAnnotationVisitor} instance. This way this visitor
   * instance can perform changes in the {@link XsdAnnotation} object.
   */
  std::shared_ptr<XsdAnnotation> owner;

  virtual std::shared_ptr<XsdAbstractElement> getOwner(void) override
    { return std::static_pointer_cast<XsdAbstractElement>(owner); }

  virtual void visit(std::shared_ptr<XsdAbstractElement> element) override
  {
    assert(std::dynamic_pointer_cast<XsdAnnotationChildren>(element));
    owner->add(std::static_pointer_cast<XsdAnnotationChildren>(element));
  }
};
