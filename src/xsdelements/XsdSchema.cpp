#include "XsdSchema.h"

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

XsdSchema::XsdSchema(std::shared_ptr<XsdParserCore> parser,
                     StringMap attributesMap,
                     VisitorFunctionType visitorFunction,
                     std::shared_ptr<XsdAbstractElement> parent)
  : XsdAnnotatedElements(parser, attributesMap, visitorFunction, parent),
    m_attributeFormDefault(FormEnum::UNQUALIFIED),
    m_elementFormDefault(FormEnum::UNQUALIFIED),
    m_blockDefault(BlockDefaultEnum::DEFAULT),
    m_finalDefault(FinalDefaultEnum::DEFAULT)
{
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

  for (auto& pair : attributesMap)
  {
    auto& key = pair.first;
    if (key.starts_with(XMLNS) &&
        key != "xmlns:xs" &&
        key != "xmlns:xsd")
    {
      std::string namespaceId = key.substr(key.find_first_of(':') + 1);
      m_namespaces.emplace(namespaceId, NamespaceInfo(attributesMap.at(key)));
    }
  }
}

std::list<std::shared_ptr<ReferenceBase>> XsdSchema::getElements(void)
{
  std::list<std::shared_ptr<ReferenceBase>> rval;
  for(auto& element : m_elements)
    rval.push_back(ReferenceBase::createFromXsd(element));
  return rval;
}

void XsdSchema::add(std::shared_ptr<XsdInclude> element) {
      m_elements.push_back(std::static_pointer_cast<XsdAbstractElement>(element));
  }

void XsdSchema::add(std::shared_ptr<XsdImport> element) {
      m_elements.push_back(std::static_pointer_cast<XsdAbstractElement>(element));
  }

void XsdSchema::add(std::shared_ptr<XsdAnnotation> element) {
      m_elements.push_back(std::static_pointer_cast<XsdAbstractElement>(element));
  }

void XsdSchema::add(std::shared_ptr<XsdSimpleType> element) {
      m_elements.push_back(std::static_pointer_cast<XsdAbstractElement>(element));
  }

void XsdSchema::add(std::shared_ptr<XsdComplexType> element) {
      m_elements.push_back(std::static_pointer_cast<XsdAbstractElement>(element));
  }

void XsdSchema::add(std::shared_ptr<XsdGroup> element) {
      m_elements.push_back(std::static_pointer_cast<XsdAbstractElement>(element));
  }

void XsdSchema::add(std::shared_ptr<XsdAttributeGroup> element) {
      m_elements.push_back(std::static_pointer_cast<XsdAbstractElement>(element));
  }

void XsdSchema::add(std::shared_ptr<XsdElement> element) {
      m_elements.push_back(std::static_pointer_cast<XsdAbstractElement>(element));
  }

void XsdSchema::add(std::shared_ptr<XsdAttribute> element) {
      m_elements.push_back(std::static_pointer_cast<XsdAbstractElement>(element));
  }






/**
 * @return The children elements that are of the type {@link XsdInclude}.
 */
std::list<std::shared_ptr<XsdInclude>> XsdSchema::getChildrenIncludes(void)
{
  std::list<std::shared_ptr<XsdInclude>> includes;
  for(auto& element : getXsdElements())
    if(auto x = std::dynamic_pointer_cast<XsdInclude>(element); x)
      includes.push_back(x);
  return includes;
}

/**
 * @return The children elements that are of the type {@link XsdImport}.
 */
std::list<std::shared_ptr<XsdImport>> XsdSchema::getChildrenImports(void)
{
  std::list<std::shared_ptr<XsdImport>> imports;
  for(auto& element : getXsdElements())
    if(auto x = std::dynamic_pointer_cast<XsdImport>(element); x)
      imports.push_back(x);
  return imports;
}

/**
 * @return The children elements that are of the type {@link XsdAnnotation}.
 */
std::list<std::shared_ptr<XsdAnnotation>> XsdSchema::getChildrenAnnotations(void)
{
  std::list<std::shared_ptr<XsdAnnotation>> annotations;
  for(auto& element : getXsdElements())
    if(auto x = std::dynamic_pointer_cast<XsdAnnotation>(element); x)
      annotations.push_back(x);
  return annotations;
}

/**
 * @return The children elements that are of the type {@link XsdSimpleType}.
 */
std::list<std::shared_ptr<XsdSimpleType>> XsdSchema::getChildrenSimpleTypes(void)
{
  std::list<std::shared_ptr<XsdSimpleType>> simple_types;
  for(auto& element : getXsdElements())
    if(auto x = std::dynamic_pointer_cast<XsdSimpleType>(element); x)
      simple_types.push_back(x);
  return simple_types;
}

/**
 * @return The children elements that are of the type {@link XsdComplexType}.
 */
std::list<std::shared_ptr<XsdComplexType>> XsdSchema::getChildrenComplexTypes(void)
{
  std::list<std::shared_ptr<XsdComplexType>> complex_types;
  for(auto& element : getXsdElements())
    if(auto x = std::dynamic_pointer_cast<XsdComplexType>(element); x)
      complex_types.push_back(x);
  return complex_types;
}

/**
 * @return The children elements that are of the type {@link XsdGroup}.
 */
std::list<std::shared_ptr<XsdGroup>> XsdSchema::getChildrenGroups(void)
{
  std::list<std::shared_ptr<XsdGroup>> groups;
  for(auto& element : getXsdElements())
    if(auto x = std::dynamic_pointer_cast<XsdGroup>(element); x)
      groups.push_back(x);
  return groups;
}

/**
 * @return The children elements that are of the type {@link XsdAttributeGroup}.
 */
std::list<std::shared_ptr<XsdAttributeGroup>> XsdSchema::getChildrenAttributeGroups(void)
{
  std::list<std::shared_ptr<XsdAttributeGroup>> attribute_groups;
  for(auto& element : getXsdElements())
    if(auto x = std::dynamic_pointer_cast<XsdAttributeGroup>(element); x)
      attribute_groups.push_back(x);
  return attribute_groups;
}

/**
 * @return The children elements that are of the type {@link XsdElement}.
 */
std::list<std::shared_ptr<XsdElement>> XsdSchema::getChildrenElements(void)
{
  std::list<std::shared_ptr<XsdElement>> rval;
  for(auto& element : getXsdElements())
    if(auto x = std::dynamic_pointer_cast<XsdElement>(element); x)
      rval.push_back(x);
  return rval;
}

/**
 * @return The children elements that are of the type {@link XsdAttribute}.
 */
std::list<std::shared_ptr<XsdAttribute>> XsdSchema::getChildrenAttributes(void)
{
  std::list<std::shared_ptr<XsdAttribute>> attributes;
  for(auto& element : getXsdElements())
    if(auto x = std::dynamic_pointer_cast<XsdAttribute>(element); x)
      attributes.push_back(x);
  return attributes;
}

void XsdSchema::resolveNameSpace(std::optional<std::string> Namespace, SchemaLocation schemaLocation)
{
  if (Namespace && schemaLocation &&
      m_namespaces.contains(*Namespace))
  {
    NamespaceInfo namespaceInfo = m_namespaces.at(*Namespace);
    if(!namespaceInfo.getFile())
      namespaceInfo.setFile(schemaLocation);
  }
}
