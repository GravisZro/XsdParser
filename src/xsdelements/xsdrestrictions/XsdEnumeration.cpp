#include "XsdEnumeration.h"

#include <xsdelements/visitors/XsdAbstractElementVisitor.h>

void XsdEnumeration::accept(XsdAbstractElementVisitor* xsdAbstractElementVisitor)
{
  XsdStringRestrictions::accept(xsdAbstractElementVisitor);
  xsdAbstractElementVisitor->visit(this);
}
