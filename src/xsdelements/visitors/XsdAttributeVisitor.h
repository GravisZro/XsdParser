#pragma once


#include <xsdelements/XsdAnnotation.h>
#include <xsdelements/XsdAttribute.h>
#include <xsdelements/XsdSimpleType.h>
#include <xsdelements/elementswrapper/ReferenceBase.h>
#include <xsdelements/visitors/XsdAnnotatedElementsVisitor.h>

/**
 * Represents the restrictions of the {@link XsdAttribute} element, which can only contain {@link XsdSimpleType} elements
 * as children. Can also have {@link XsdAnnotation} children as per inheritance of {@link XsdAnnotatedElementsVisitor}.
 */
class XsdAttributeVisitor : public XsdAnnotatedElementsVisitor
{
private:
    /**
     * The {@link XsdAttribute} instance which owns this {@link XsdAttributeVisitor} instance. This way this visitor
     * instance can perform changes in the {@link XsdAttribute} object.
     */
    std::shared_ptr<XsdAttribute> m_owner;
public:
    using XsdAnnotatedElementsVisitor::visit;
  XsdAttributeVisitor(std::shared_ptr<XsdAttribute> owner)
    : XsdAnnotatedElementsVisitor(owner)
  {
        m_owner = owner;
    }

  std::shared_ptr<XsdAttribute> getOwner(void)
    {
        return m_owner;
    }

  void visit(std::shared_ptr<XsdSimpleType> element)
    {
        XsdAnnotatedElementsVisitor::visit(element);

        m_owner->setSimpleType(ReferenceBase::createFromXsd(element));
    }
}
