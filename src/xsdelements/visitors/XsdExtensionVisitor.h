#pragma once

#include <xsdelements/XsdExtension.h>
#include <xsdelements/XsdMultipleElements.h>
#include <xsdelements/XsdGroup.h>

#include <xsdelements/visitors/AttributesVisitor.h>
#include <xsdelements/elementswrapper/ReferenceBase.h>

/**
 * Represents the restrictions of the {@link XsdExtension} element, which can contain the following children:
 *      * {@link XsdAll}, {@link XsdSequence} , {@link XsdChoice} (represented by {@link XsdMultipleElements});
 *      * {@link XsdGroup};
 * Can also have {@link XsdAttribute} and {@link XsdAttributeGroup} children as per inheritance of {@link AttributesVisitor}.
 * Can also have {@link XsdAnnotation} children as per inheritance of {@link XsdAnnotatedElementsVisitor}.
 */
struct XsdExtensionVisitor : AttributesVisitor
{
  XsdExtensionVisitor(XsdExtension* _owner) : owner(_owner) { }

    /**
     * The {@link XsdExtension} instance which owns this {@link XsdExtensionVisitor} instance. This way this visitor
     * instance can perform changes in the {@link XsdExtension} object.
     */
  XsdExtension* owner;

  virtual XsdAbstractElement* getOwner(void) override
    { return static_cast<XsdAbstractElement*>(owner); }

  virtual void visit(XsdAbstractElement* element) override
  {
    AttributesVisitor::visit(element);
    if(dynamic_cast<XsdMultipleElements*>(element) != nullptr ||
       dynamic_cast<XsdGroup*>(element) != nullptr)
      owner->setChildElement(ReferenceBase::createFromXsd(element));
  }
};
