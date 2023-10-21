#pragma once

#include <xsdelements/XsdAnnotation.h>
#include <xsdelements/XsdAppInfo.h>
#include <xsdelements/XsdDocumentation.h>
#include <xsdelements/visitors/XsdAbstractElementVisitor.h>

/**
 * Represents the restrictions of the {@link XsdAnnotation} element, which can only contain {@link XsdAppInfo} and
 * {@link XsdDocumentation} as children.
 */
class XsdAnnotationVisitor : public XsdAbstractElementVisitor
{
private:
    /**
     * The {@link XsdAnnotation} instance which owns this {@link XsdAnnotationVisitor} instance. This way this visitor
     * instance can perform changes in the {@link XsdAnnotation} object.
     */
    std::shared_ptr<XsdAnnotation> m_owner;
public:
    using XsdAbstractElementVisitor::visit;
  XsdAnnotationVisitor(std::shared_ptr<XsdAnnotation> owner){
        m_owner = owner;
    }

  virtual std::shared_ptr<XsdAbstractElement> getOwner(void) override
    { return std::static_pointer_cast<XsdAbstractElement>(m_owner); }

  void visit(std::shared_ptr<XsdAppInfo> element) override
    {
        XsdAbstractElementVisitor::visit(element);

        m_owner->add(element);
    }

  void visit(std::shared_ptr<XsdDocumentation> element) override
    {
        XsdAbstractElementVisitor::visit(element);

        m_owner->add(element);
    }

};
