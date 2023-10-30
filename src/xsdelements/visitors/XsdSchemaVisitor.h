#pragma once

#include <xsdelements/visitors/AttributesVisitor.h>
#include <xsdelements/XsdSchema.h>

struct XsdSchemaVisitor : AttributesVisitor
{
  XsdSchemaVisitor(XsdSchema* _owner) : owner(_owner) { }

  XsdSchema* owner;

  virtual XsdAbstractElement* getOwner(void) override
    { return static_cast<XsdAbstractElement*>(owner); }

  virtual void visit(XsdAbstractElement* element) override;
};
