#include "XsdSchemaVisitor.h"

#include <xsdelements/XsdInclude.h>
#include <xsdelements/XsdImport.h>
#include <xsdelements/XsdAnnotation.h>
#include <xsdelements/XsdSimpleType.h>
#include <xsdelements/XsdComplexType.h>
#include <xsdelements/XsdGroup.h>
#include <xsdelements/XsdAttributeGroup.h>
#include <xsdelements/XsdElement.h>
#include <xsdelements/XsdAttribute.h>


void XsdSchemaVisitor::visit(std::shared_ptr<XsdInclude> element)
  {
      AttributesVisitor::visit(element);

      m_owner->add(element);
  }

void XsdSchemaVisitor::visit(std::shared_ptr<XsdImport> element)
  {
      AttributesVisitor::visit(element);

      m_owner->add(element);
  }

void XsdSchemaVisitor::visit(std::shared_ptr<XsdAnnotation> element)
  {
      AttributesVisitor::visit(element);

      m_owner->add(element);
  }

void XsdSchemaVisitor::visit(std::shared_ptr<XsdSimpleType> element)
  {
      AttributesVisitor::visit(element);

      m_owner->add(element);
  }

void XsdSchemaVisitor::visit(std::shared_ptr<XsdComplexType> element)
  {
      AttributesVisitor::visit(element);

      m_owner->add(element);
  }

void XsdSchemaVisitor::visit(std::shared_ptr<XsdGroup> element)
  {
      AttributesVisitor::visit(element);

      m_owner->add(element);
  }

void XsdSchemaVisitor::visit(std::shared_ptr<XsdAttributeGroup> element)
  {
      AttributesVisitor::visit(element);

      m_owner->add(element);
  }

void XsdSchemaVisitor::visit(std::shared_ptr<XsdElement> element)
  {
      AttributesVisitor::visit(element);

      m_owner->add(element);
  }

void XsdSchemaVisitor::visit(std::shared_ptr<XsdAttribute> element)
  {
      AttributesVisitor::visit(element);

      m_owner->add(element);
  }
