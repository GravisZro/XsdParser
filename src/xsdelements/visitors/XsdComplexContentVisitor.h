#pragma once


#include <xsdelements/XsdComplexContent.h>
#include <xsdelements/XsdExtension.h>
#include <xsdelements/XsdRestriction.h>
#include <xsdelements/elementswrapper/ReferenceBase.h>
#include <xsdelements/visitors/XsdAnnotatedElementsVisitor.h>

/**
 * Represents the restrictions of the {@link XsdComplexContent} element, which can only contain {@link XsdRestriction}
 * and {@link XsdExtension} as children. Can also have xsd:annotation children as per inheritance of
 * {@link XsdAnnotatedElementsVisitor}.
 */
class XsdComplexContentVisitor : public XsdAnnotatedElementsVisitor
{
private:
    /**
     * The {@link XsdComplexContent} instance which owns this {@link XsdComplexContentVisitor} instance. This way this
     * visitor instance can perform changes in the {@link XsdComplexContent} object.
     */
    std::shared_ptr<XsdComplexContent> m_owner;
public:
    using XsdAnnotatedElementsVisitor::visit;
  XsdComplexContentVisitor(std::shared_ptr<XsdComplexContent> owner)
        : XsdAnnotatedElementsVisitor(owner)
  {
        m_owner = owner;
    }

  virtual std::shared_ptr<XsdAbstractElement> getOwner(void) override
    { return std::static_pointer_cast<XsdAbstractElement>(m_owner); }

  void visit(std::shared_ptr<XsdRestriction> element) override
    {
        XsdAnnotatedElementsVisitor::visit(element);

        m_owner->setRestriction(ReferenceBase::createFromXsd(element));
    }

  void visit(std::shared_ptr<XsdExtension> element) override
    {
        XsdAnnotatedElementsVisitor::visit(element);

        m_owner->setExtension(ReferenceBase::createFromXsd(element));
    }
};
