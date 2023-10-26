#include "XsdComplexTypeVisitor.h"

#include <xsdelements/elementswrapper/ReferenceBase.h>
#include <xsdelements/XsdMultipleElements.h>
#include <xsdelements/XsdGroup.h>
#include <xsdelements/XsdComplexContent.h>
#include <xsdelements/XsdSimpleContent.h>

void XsdComplexTypeVisitor::visit(std::shared_ptr<XsdAbstractElement> element)
{
  XsdNamedElementsVisitor::visit(element);
  AttributesVisitor::visit(element);

  if(std::dynamic_pointer_cast<XsdMultipleElements>(element) ||
     std::dynamic_pointer_cast<XsdGroup>(element))
    owner->setChildElement(ReferenceBase::createFromXsd(element));
  else if(std::dynamic_pointer_cast<XsdComplexContent>(element))
    owner->setComplexContent(std::static_pointer_cast<XsdComplexContent>(element));
  else if(std::dynamic_pointer_cast<XsdComplexContent>(element))
    owner->setSimpleContent(std::static_pointer_cast<XsdSimpleContent>(element));
}
