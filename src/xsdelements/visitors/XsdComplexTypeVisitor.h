#pragma once

#include <xsdelements/elementswrapper/ReferenceBase.h>
#include <xsdelements/visitors/AttributesVisitor.h>
#include <xsdelements/XsdComplexType.h>

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
  XsdComplexTypeVisitor(std::shared_ptr<XsdComplexType> _owner) : owner(_owner) { }

  /**
   * The {@link XsdComplexType} instance which owns this {@link XsdComplexTypeVisitor} instance. This way this visitor
   * instance can perform changes in the {@link XsdComplexType} object.
   */
  std::shared_ptr<XsdComplexType> owner;

  virtual std::shared_ptr<XsdAbstractElement> getOwner(void) override
    { return std::static_pointer_cast<XsdAbstractElement>(owner); }

  virtual void visit(std::shared_ptr<XsdAbstractElement> element) override;
};
