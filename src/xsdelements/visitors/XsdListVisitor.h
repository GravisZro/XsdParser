#pragma once


#include <xsdelements/XsdAnnotation.h>
#include <xsdelements/XsdList.h>
#include <xsdelements/XsdSimpleType.h>
#include <xsdelements/exceptions/ParsingException.h>
#include <xsdelements/visitors/XsdAnnotatedElementsVisitor.h>
/**
 * Represents the restrictions of the {@link XsdList} element, which can only contain {@link XsdSimpleType} as children.
 * Can also have {@link XsdAnnotation} children as per inheritance of {@link XsdAnnotatedElementsVisitor}.
 */
class XsdListVisitor : public XsdAnnotatedElementsVisitor
{
private:
    /**
     * The {@link XsdList} instance which owns this {@link XsdListVisitor} instance. This way this visitor instance can
     * perform changes in the {@link XsdList} object.
     */
    std::shared_ptr<XsdList> m_owner;
public:
    using XsdAnnotatedElementsVisitor::visit;
  XsdListVisitor(std::shared_ptr<XsdList> owner)
        : XsdAnnotatedElementsVisitor(owner)
  {
        m_owner = owner;
    }


  virtual std::shared_ptr<XsdAbstractElement> getOwner(void) override
    { return std::static_pointer_cast<XsdAbstractElement>(m_owner); }

  void visit(std::shared_ptr<XsdSimpleType> element) override
    {
        XsdAnnotatedElementsVisitor::visit(element);

        if (m_owner->getItemType())
            throw ParsingException(XsdList::XSD_TAG + " element: The element cannot have both the itemType attribute and a " + XsdSimpleType::XSD_TAG + " element as content at the same time." );

        m_owner->setSimpleType(element);
    }
};
