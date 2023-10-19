#include "XsdAbstractElementVisitor.h"


#include <xsdelements/elementswrapper/ReferenceBase.h>
#include <xsdelements/elementswrapper/UnsolvedReference.h>

#include <core/XsdParserCore.h>
//#include <xsdelements/XsdAbstractElement.h>
#include <xsdelements/AttributeValidations.h>
#include <xsdelements/XsdAll.h>
#include <xsdelements/XsdAnnotatedElements.h>
#include <xsdelements/XsdAnnotationChildren.h>
#include <xsdelements/XsdAnnotation.h>
#include <xsdelements/XsdAppInfo.h>
#include <xsdelements/XsdAttributeGroup.h>
#include <xsdelements/XsdAttribute.h>
#include <xsdelements/XsdBuiltInDataType.h>
#include <xsdelements/XsdChoice.h>
#include <xsdelements/XsdComplexContent.h>
#include <xsdelements/XsdComplexType.h>
#include <xsdelements/XsdDocumentation.h>
#include <xsdelements/XsdElement.h>
#include <xsdelements/XsdExtension.h>
#include <xsdelements/XsdGroup.h>
#include <xsdelements/XsdIdentifierElements.h>
#include <xsdelements/XsdImport.h>
#include <xsdelements/XsdInclude.h>
#include <xsdelements/XsdList.h>
#include <xsdelements/XsdMultipleElements.h>
#include <xsdelements/XsdNamedElements.h>
#include <xsdelements/XsdRestriction.h>
#include <xsdelements/XsdSchema.h>
#include <xsdelements/XsdSequence.h>
#include <xsdelements/XsdSimpleContent.h>
#include <xsdelements/XsdSimpleType.h>
#include <xsdelements/XsdUnion.h>


void XsdAbstractElementVisitor::visit(std::shared_ptr<XsdAll> element)
{
  visit(std::static_pointer_cast<XsdMultipleElements>(element));
}

void XsdAbstractElementVisitor::visit(std::shared_ptr<XsdAttribute> element)
{
  visit(std::static_pointer_cast<XsdNamedElements>(element));
}

void XsdAbstractElementVisitor::visit(std::shared_ptr<XsdAttributeGroup> element)
{
  visit(std::static_pointer_cast<XsdNamedElements>(element));
}

void XsdAbstractElementVisitor::visit(std::shared_ptr<XsdChoice> element)
{
  visit(std::static_pointer_cast<XsdMultipleElements>(element));
}

void XsdAbstractElementVisitor::visit(std::shared_ptr<XsdElement> element)
{
  visit(std::static_pointer_cast<XsdNamedElements>(element));
}

void XsdAbstractElementVisitor::visit(std::shared_ptr<XsdGroup> element)
{
  visit(std::static_pointer_cast<XsdNamedElements>(element));
}

void XsdAbstractElementVisitor::visit(std::shared_ptr<XsdSequence> element)
{
  visit(std::static_pointer_cast<XsdMultipleElements>(element));
}

void XsdAbstractElementVisitor::visit(std::shared_ptr<XsdNamedElements> element)
{
  std::shared_ptr<ReferenceBase> referenceBase = ReferenceBase::createFromXsd(std::static_pointer_cast<XsdAbstractElement>(element));
  if(auto x = std::dynamic_pointer_cast<UnsolvedReference>(referenceBase); x)
    element->getParser()->addUnsolvedReference(x);
}

void XsdAbstractElementVisitor::visit([[maybe_unused]] std::shared_ptr<XsdComplexType> element) {}

void XsdAbstractElementVisitor::visit([[maybe_unused]] std::shared_ptr<XsdMultipleElements> element){}

void XsdAbstractElementVisitor::visit([[maybe_unused]] std::shared_ptr<XsdSimpleType> element) {}

void XsdAbstractElementVisitor::visit([[maybe_unused]] std::shared_ptr<XsdRestriction> element) {}

void XsdAbstractElementVisitor::visit([[maybe_unused]] std::shared_ptr<XsdList> element) {}

void XsdAbstractElementVisitor::visit([[maybe_unused]] std::shared_ptr<XsdUnion> element) {}

void XsdAbstractElementVisitor::visit([[maybe_unused]] std::shared_ptr<XsdEnumeration> element) {}

void XsdAbstractElementVisitor::visit([[maybe_unused]] std::shared_ptr<XsdFractionDigits> element) {}

void XsdAbstractElementVisitor::visit([[maybe_unused]] std::shared_ptr<XsdLength> element) {}

void XsdAbstractElementVisitor::visit([[maybe_unused]] std::shared_ptr<XsdMaxExclusive> element) {}

void XsdAbstractElementVisitor::visit([[maybe_unused]] std::shared_ptr<XsdMaxInclusive> element) {}

void XsdAbstractElementVisitor::visit([[maybe_unused]] std::shared_ptr<XsdMaxLength> element) {}

void XsdAbstractElementVisitor::visit([[maybe_unused]] std::shared_ptr<XsdMinExclusive> element) {}

void XsdAbstractElementVisitor::visit([[maybe_unused]] std::shared_ptr<XsdMinInclusive> element) {}

void XsdAbstractElementVisitor::visit([[maybe_unused]] std::shared_ptr<XsdMinLength> element) {}

void XsdAbstractElementVisitor::visit([[maybe_unused]] std::shared_ptr<XsdPattern> element) {}

void XsdAbstractElementVisitor::visit([[maybe_unused]] std::shared_ptr<XsdTotalDigits> element) {}

void XsdAbstractElementVisitor::visit([[maybe_unused]] std::shared_ptr<XsdWhiteSpace> element) {}

void XsdAbstractElementVisitor::visit([[maybe_unused]] std::shared_ptr<XsdExtension> element) {}

void XsdAbstractElementVisitor::visit([[maybe_unused]] std::shared_ptr<XsdComplexContent> element) {}

void XsdAbstractElementVisitor::visit([[maybe_unused]] std::shared_ptr<XsdSimpleContent> element) {}

void XsdAbstractElementVisitor::visit([[maybe_unused]] std::shared_ptr<XsdDocumentation> element) {}

void XsdAbstractElementVisitor::visit([[maybe_unused]] std::shared_ptr<XsdAppInfo> element) {}

void XsdAbstractElementVisitor::visit([[maybe_unused]] std::shared_ptr<XsdAnnotation> element) {}

void XsdAbstractElementVisitor::visit([[maybe_unused]] std::shared_ptr<XsdImport> element) {}

void XsdAbstractElementVisitor::visit([[maybe_unused]] std::shared_ptr<XsdInclude> element) {}
