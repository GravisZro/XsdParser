#include "XsdSchema.h"

#include <xsdelements/elementswrapper/ReferenceBase.h>
#include <xsdelements/XsdInclude.h>
#include <xsdelements/XsdImport.h>
#include <xsdelements/XsdAnnotation.h>
#include <xsdelements/XsdSimpleType.h>
#include <xsdelements/XsdComplexType.h>
#include <xsdelements/XsdGroup.h>
#include <xsdelements/XsdAttributeGroup.h>
#include <xsdelements/XsdElement.h>
#include <xsdelements/XsdAttribute.h>

#include <xsdelements/AttributeValidations.h>
#include <xsdelements/XsdAbstractElement.h>
#include <xsdelements/visitors/XsdAbstractElementVisitor.h>
#include <core/XsdParserCore.h>

void XsdSchema::initialize(void)
{
  XsdAnnotatedElements::initialize();

  m_attributeFormDefault = FormEnum::UNQUALIFIED;
  m_elementFormDefault = FormEnum::UNQUALIFIED;
  m_blockDefault = BlockDefaultEnum::DEFAULT;
  m_finalDefault = FinalDefaultEnum::DEFAULT;

  if(haveAttribute(ATTRIBUTE_FORM_DEFAULT))
    m_attributeFormDefault = AttributeValidations::belongsToEnum<FormEnum>(getAttribute(ATTRIBUTE_FORM_DEFAULT));

  if(haveAttribute(ELEMENT_FORM_DEFAULT))
    m_elementFormDefault = AttributeValidations::belongsToEnum<FormEnum>(getAttribute(ELEMENT_FORM_DEFAULT));

  if(haveAttribute(BLOCK_DEFAULT))
    m_blockDefault = AttributeValidations::belongsToEnum<BlockDefaultEnum>(getAttribute(BLOCK_DEFAULT));

  if(haveAttribute(FINAL_DEFAULT))
    m_finalDefault = AttributeValidations::belongsToEnum<FinalDefaultEnum>(getAttribute(FINAL_DEFAULT));

  if(haveAttribute(TARGET_NAMESPACE))
    m_targetNamespace = getAttribute(TARGET_NAMESPACE);

  if(haveAttribute(VERSION))
    m_version = getAttribute(VERSION);

  if(haveAttribute(XMLNS))
    m_xmlns = getAttribute(XMLNS);

  for (auto& pair : getAttributesMap())
  {
    auto& key = pair.first;
    if (key.starts_with(XMLNS) &&
        key != "xmlns:xs" &&
        key != "xmlns:xsd")
    {
      std::string namespaceId = key.substr(key.find_first_of(':') + 1);
      m_namespaces.emplace(namespaceId, NamespaceInfo(pair.second));
    }
  }
}

std::list<std::shared_ptr<ReferenceBase>> XsdSchema::getElements(void) const
{
  std::list<std::shared_ptr<ReferenceBase>> rval;
  for(auto& element : m_elements)
    rval.push_back(ReferenceBase::createFromXsd(element));
  return rval;
}


void XsdSchema::add(std::shared_ptr<XsdAbstractElement> element)
{
  assert(std::dynamic_pointer_cast<XsdInclude       >(element) ||
         std::dynamic_pointer_cast<XsdImport        >(element) ||
         std::dynamic_pointer_cast<XsdAnnotation    >(element) ||
         std::dynamic_pointer_cast<XsdSimpleType    >(element) ||
         std::dynamic_pointer_cast<XsdComplexType   >(element) ||
         std::dynamic_pointer_cast<XsdGroup         >(element) ||
         std::dynamic_pointer_cast<XsdAttributeGroup>(element) ||
         std::dynamic_pointer_cast<XsdElement       >(element) ||
         std::dynamic_pointer_cast<XsdAttribute     >(element));
  m_elements.push_back(element);
}

void XsdSchema::resolveNameSpace(std::optional<std::string> Namespace, SchemaLocation schemaLocation)
{
  if (Namespace && schemaLocation &&
      m_namespaces.contains(*Namespace))
  {
    NamespaceInfo namespaceInfo = m_namespaces.at(*Namespace);
    if(!namespaceInfo.getLocation())
      namespaceInfo.setLocation(schemaLocation);
  }
}
