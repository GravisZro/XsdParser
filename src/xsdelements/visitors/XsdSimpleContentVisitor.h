#pragma once


#include <xsdelements/XsdAnnotation.h>
#include <xsdelements/XsdExtension.h>
#include <xsdelements/XsdRestriction.h>
#include <xsdelements/XsdSimpleContent.h>
#include <xsdelements/elementswrapper/ReferenceBase.h>
#include <xsdelements/visitors/XsdAnnotatedElementsVisitor.h>

/**
 * Represents the restrictions of the {@link XsdSimpleContent} element, which can only contain {@link XsdRestriction} or
 * {@link XsdExtension} as children. Can also have {@link XsdAnnotation} as children as per inheritance of
 * {@link XsdAnnotatedElementsVisitor}.
 */
class XsdSimpleContentVisitor : public XsdAnnotatedElementsVisitor
{
private:
    /**
     * The {@link XsdSimpleContent} instance which owns this {@link XsdSimpleContentVisitor} instance. This way this
     * visitor instance can perform changes in the {@link XsdSimpleContent} object.
     */
    std::shared_ptr<XsdSimpleContent> m_owner;
public:
    using XsdAnnotatedElementsVisitor::visit;
  XsdSimpleContentVisitor(std::shared_ptr<XsdSimpleContent> owner)
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
