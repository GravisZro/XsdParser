#include "XsdComplexTypeVisitor.h"

#include <xsdelements/XsdMultipleElements.h>
#include <xsdelements/XsdGroup.h>
#include <xsdelements/XsdComplexContent.h>

void XsdComplexTypeVisitor::visit(std::shared_ptr<XsdMultipleElements> element)
  {
      AttributesVisitor::visit(element);

      m_owner->setChildElement(ReferenceBase::createFromXsd(element));
  }

void XsdComplexTypeVisitor::visit(std::shared_ptr<XsdGroup> element)
  {
      AttributesVisitor::visit(element);

      m_owner->setChildElement(ReferenceBase::createFromXsd(element));
  }

void XsdComplexTypeVisitor::visit(std::shared_ptr<XsdComplexContent> element)
  {
      AttributesVisitor::visit(element);

      m_owner->setComplexContent(element);
  }

void XsdComplexTypeVisitor::visit(std::shared_ptr<XsdSimpleContent> element)
  {
      AttributesVisitor::visit(element);

      m_owner->setSimpleContent(element);
  }
