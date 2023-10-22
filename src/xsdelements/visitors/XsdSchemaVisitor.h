#pragma once

#include <xsdelements/visitors/AttributesVisitor.h>
#include <xsdelements/XsdSchema.h>

struct XsdSchemaVisitor : AttributesVisitor
{
  XsdSchemaVisitor(std::shared_ptr<XsdSchema> _owner) : owner(_owner) { }

  std::shared_ptr<XsdSchema> owner;

  virtual std::shared_ptr<XsdAbstractElement> getOwner(void) override
    { return std::static_pointer_cast<XsdAbstractElement>(owner); }

  virtual void visit(std::shared_ptr<XsdAbstractElement> element) override;
};
