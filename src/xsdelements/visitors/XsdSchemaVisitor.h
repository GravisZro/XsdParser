#pragma once

#include <xsdelements/visitors/AttributesVisitor.h>
#include <xsdelements/XsdSchema.h>

class XsdSchemaVisitor : public AttributesVisitor
{
private:
  std::shared_ptr<XsdSchema> m_owner;
public:
  using AttributesVisitor::visit;
  XsdSchemaVisitor(std::shared_ptr<XsdSchema> owner)
        : AttributesVisitor(std::static_pointer_cast<XsdAnnotatedElements>(owner))
  {
        m_owner = owner;
    }

  std::shared_ptr<XsdSchema> getOwner(void)
    {
        return m_owner;
    }

  void visit(std::shared_ptr<XsdInclude> element);
  void visit(std::shared_ptr<XsdImport> element);
  void visit(std::shared_ptr<XsdAnnotation> element);
  void visit(std::shared_ptr<XsdSimpleType> element);
  void visit(std::shared_ptr<XsdComplexType> element);
  void visit(std::shared_ptr<XsdGroup> element);
  void visit(std::shared_ptr<XsdAttributeGroup> element);
  void visit(std::shared_ptr<XsdElement> element);
  void visit(std::shared_ptr<XsdAttribute> element);
};
