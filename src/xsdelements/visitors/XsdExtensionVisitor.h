#pragma once


// #include <xsdelements/*.h>
/*

#include <xsdelements/XsdAbstractElement.h>
#include <xsdelements/XsdAll.h>
#include <xsdelements/XsdAttribute.h>
#include <xsdelements/XsdAttributeGroup.h>
#include <xsdelements/XsdChoice.h>
#include <xsdelements/XsdComplexType.h>
#include <xsdelements/XsdElement.h>
#include <xsdelements/XsdGroup.h>
#include <xsdelements/XsdSequence.h>
#include <xsdelements/XsdMultipleElements.h>
#include <xsdelements/XsdNamedElements.h>
#include <xsdelements/XsdSimpleType.h>
#include <xsdelements/XsdRestriction.h>
#include <xsdelements/XsdList.h>
#include <xsdelements/XsdUnion.h>
#include <xsdelements/XsdEnumeration.h>
#include <xsdelements/XsdFractionDigits.h>
#include <xsdelements/XsdLength.h>
#include <xsdelements/XsdMaxExclusive.h>
#include <xsdelements/XsdMaxInclusive.h>
#include <xsdelements/XsdMaxLength.h>
#include <xsdelements/XsdMinExclusive.h>
#include <xsdelements/XsdMinInclusive.h>
#include <xsdelements/XsdMinLength.h>
#include <xsdelements/XsdPattern.h>
#include <xsdelements/XsdTotalDigits.h>
#include <xsdelements/XsdWhiteSpace.h>
#include <xsdelements/XsdExtension.h>
#include <xsdelements/XsdComplexContent.h>
#include <xsdelements/XsdSimpleContent.h>
#include <xsdelements/XsdDocumentation.h>
#include <xsdelements/XsdAppInfo.h>
#include <xsdelements/XsdAnnotation.h>
#include <xsdelements/XsdImport.h>
#include <xsdelements/XsdInclude.h>
*/

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
class XsdExtensionVisitor : public AttributesVisitor
{
private:
    /**
     * The {@link XsdExtension} instance which owns this {@link XsdExtensionVisitor} instance. This way this visitor
     * instance can perform changes in the {@link XsdExtension} object.
     */
  std::shared_ptr<XsdExtension> m_owner;
public:
  using AttributesVisitor::visit;
  XsdExtensionVisitor(std::shared_ptr<XsdExtension> owner)
    : AttributesVisitor(owner)
  {
    m_owner = owner;
  }

  std::shared_ptr<XsdExtension> getOwner(void)
    {
        return m_owner;
    }

  void visit(std::shared_ptr<XsdMultipleElements> element)
    {
        AttributesVisitor::visit(element);
        m_owner->setChildElement(ReferenceBase::createFromXsd(element));
    }

  void visit(std::shared_ptr<XsdGroup> element)
    {
        AttributesVisitor::visit(element);
        m_owner->setChildElement(ReferenceBase::createFromXsd(element));
    }
};
