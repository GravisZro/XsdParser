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


void XsdSchemaVisitor::visit(std::shared_ptr<XsdAbstractElement> element)
{
  AttributesVisitor::visit(element);

  assert(std::dynamic_pointer_cast<XsdInclude       >(element) ||
         std::dynamic_pointer_cast<XsdImport        >(element) ||
         std::dynamic_pointer_cast<XsdAnnotation    >(element) ||
         std::dynamic_pointer_cast<XsdSimpleType    >(element) ||
         std::dynamic_pointer_cast<XsdComplexType   >(element) ||
         std::dynamic_pointer_cast<XsdGroup         >(element) ||
         std::dynamic_pointer_cast<XsdAttributeGroup>(element) ||
         std::dynamic_pointer_cast<XsdElement       >(element) ||
         std::dynamic_pointer_cast<XsdAttribute     >(element));
  owner->add(element);
}
