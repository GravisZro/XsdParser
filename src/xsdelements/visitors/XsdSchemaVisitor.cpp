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


void XsdSchemaVisitor::visit(XsdAbstractElement* element)
{
  AttributesVisitor::visit(element);

  assert(dynamic_cast<XsdInclude       *>(element) != nullptr ||
         dynamic_cast<XsdImport        *>(element) != nullptr ||
         dynamic_cast<XsdAnnotation    *>(element) != nullptr ||
         dynamic_cast<XsdSimpleType    *>(element) != nullptr ||
         dynamic_cast<XsdComplexType   *>(element) != nullptr ||
         dynamic_cast<XsdGroup         *>(element) != nullptr ||
         dynamic_cast<XsdAttributeGroup*>(element) != nullptr ||
         dynamic_cast<XsdElement       *>(element) != nullptr ||
         dynamic_cast<XsdAttribute     *>(element) != nullptr);
  owner->add(element);
}
