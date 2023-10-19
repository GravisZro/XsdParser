#pragma once


#include <xsdelements/XsdAnnotation.h>
#include <xsdelements/XsdComplexType.h>
#include <xsdelements/XsdElement.h>
#include <xsdelements/XsdSimpleType.h>
#include <xsdelements/elementswrapper/ReferenceBase.h>

/**
 * Represents the restrictions of the {@link XsdElement} element, which can only contain {@link XsdSimpleType} or
 * {@link XsdComplexType} as children. Can also have {@link XsdAnnotation} children as per inheritance of
 * {@link XsdAnnotatedElementsVisitor}.
 */
class XsdElementVisitor : public XsdAnnotatedElementsVisitor
{
private:
    /**
     * The {@link XsdElement} instance which owns this {@link XsdElementVisitor} instance. This way this visitor instance
     * can perform changes in the {@link XsdElement} object.
     */
  std::shared_ptr<XsdElement> m_owner;
public:
  using XsdAnnotatedElementsVisitor::visit;
  XsdElementVisitor(std::shared_ptr<XsdElement> owner)
        : XsdAnnotatedElementsVisitor(owner)
  {
        m_owner = owner;
    }

  std::shared_ptr<XsdElement> getOwner(void)
    {
        return m_owner;
    }

  void visit(std::shared_ptr<XsdComplexType> element)
    {
        XsdAnnotatedElementsVisitor::visit(element);

        m_owner->setComplexType(ReferenceBase::createFromXsd(element));
    }

  void visit(std::shared_ptr<XsdSimpleType> element)
    {
        XsdAnnotatedElementsVisitor::visit(element);

        m_owner->setSimpleType(ReferenceBase::createFromXsd(element));
    }
};
