#pragma once


#include <xsdelements/XsdAnnotation.h>
#include <xsdelements/XsdAttribute.h>
#include <xsdelements/XsdAttributeGroup.h>
#include <xsdelements/elementswrapper/ReferenceBase.h>
#include <xsdelements/visitors/XsdAnnotatedElementsVisitor.h>

/**
 * Represents the restrictions of the {@link XsdAttributeGroup} element, which can only contain {@link XsdAttribute}
 * elements as children. Can also have {@link XsdAnnotation} children as per inheritance of
 * {@link XsdAnnotatedElementsVisitor}.
 */
class XsdAttributeGroupVisitor : public XsdAnnotatedElementsVisitor
{
private:
    /**
     * The {@link XsdAttributeGroup} instance which owns this {@link XsdAttributeGroupVisitor} instance. This way this
     * visitor instance can perform changes in the {@link XsdAttributeGroup} object.
     */
    std::shared_ptr<XsdAttributeGroup> m_owner;
public:
    using XsdAnnotatedElementsVisitor::visit;
  XsdAttributeGroupVisitor(std::shared_ptr<XsdAttributeGroup> owner)
    : XsdAnnotatedElementsVisitor(owner)
  {
    m_owner = owner;
  }

  std::shared_ptr<XsdAttributeGroup> getOwner(void)
    {
        return m_owner;
    }

  void visit(std::shared_ptr<XsdAttribute> element)
    {
        XsdAnnotatedElementsVisitor::visit(element);

        m_owner->addAttribute(ReferenceBase::createFromXsd(element));
    }

  void visit(std::shared_ptr<XsdAttributeGroup> element)
    {
        XsdAnnotatedElementsVisitor::visit(element);

        m_owner->addAttributeGroup(ReferenceBase::createFromXsd(element));
    }
};
