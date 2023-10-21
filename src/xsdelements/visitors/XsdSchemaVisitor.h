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

  virtual std::shared_ptr<XsdAbstractElement> getOwner(void) override
    { return std::static_pointer_cast<XsdAbstractElement>(m_owner); }

  void visit(std::shared_ptr<XsdInclude> element) override;
  void visit(std::shared_ptr<XsdImport> element) override;
  void visit(std::shared_ptr<XsdAnnotation> element) override;
  void visit(std::shared_ptr<XsdSimpleType> element) override;
  void visit(std::shared_ptr<XsdComplexType> element) override;
  void visit(std::shared_ptr<XsdGroup> element) override;
  void visit(std::shared_ptr<XsdAttributeGroup> element) override;
  void visit(std::shared_ptr<XsdElement> element) override;
  void visit(std::shared_ptr<XsdAttribute> element) override;
};
