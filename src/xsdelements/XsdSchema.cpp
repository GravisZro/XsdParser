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
          VisitorFunctionReference visitorFunction)
  : XsdAnnotatedElements(parser, attributesMap, visitorFunction),
    attributeFormDefault(FormEnum::UNQUALIFIED),
    elementFormDefault(FormEnum::UNQUALIFIED),
{
    m_attributeFormDefault = AttributeValidations::belongsToEnum<FormEnum>(attributesMap.getOrDefault(ATTRIBUTE_FORM_DEFAULT, FormEnum::UNQUALIFIED.getValue()));
    m_elementFormDefault = AttributeValidations::belongsToEnum<FormEnum>(attributesMap.getOrDefault(ELEMENT_FORM_DEFAULT, FormEnum::UNQUALIFIED.getValue()));
    m_blockDefault = AttributeValidations::belongsToEnum<BlockDefaultEnum>(attributesMap.getOrDefault(BLOCK_DEFAULT, BlockDefaultEnum::DEFAULT.getValue()));
    m_finalDefault = AttributeValidations::belongsToEnum<FinalDefaultEnum>(attributesMap.getOrDefault(FINAL_DEFAULT, FinalDefaultEnum::DEFAULT.getValue()));
    m_targetNamespace = attributesMap.getOrDefault(TARGET_NAMESPACE, targetNamespace);
    m_version = attributesMap.getOrDefault(VERSION, version);
    m_xmlns = attributesMap.getOrDefault(XMLNS, xmlns);

    for (std::string key : attributesMap.keySet())
    {
        if (key.startsWith(XMLNS) && !key.equals("xmlns:xs") && !key.equals("xmlns:xsd")/*&& !attributesMap.get(key).contains("http")*/){
            std::string namespaceId = key.replace(XMLNS + ":", "");
            namespaces.put(namespaceId, new NamespaceInfo(attributesMap.get(key)));
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

std::shared_ptr<ReferenceBase> XsdSchema::parse(ParseData parseData)
{
      std::shared_ptr<ReferenceBase> xsdSchemaRef = xsdParseSkeleton(parseData.node,
                                                                     std::static_pointer_cast<XsdAbstractElement>(
                                                                       std::make_shared<XsdSchema>(
                                                                         parseData.parserInstance,
                                                                         XsdAbstractElement::getAttributesMap(parseData.node),
                                                                         parseData.visitorFunction)));
      std::shared_ptr<XsdSchema> xsdSchema = std::static_pointer_cast<XsdSchema>(xsdSchemaRef->getElement());

      std::list<std::shared_ptr<XsdImport>> importsList = xsdSchema->getChildrenImports();

      StringMap prefixLocations;

      for(auto& nspair : xsdSchema->getNamespaces())
      {
        for(auto& import : importsList)
          if(import->getNamespace() == nspair.second.getName())
          {
            prefixLocations.emplace(nspair.first, import->getSchemaLocation());
            break;
          }
      }

      xsdSchema->updatePrefixLocations(prefixLocations);
      return xsdSchemaRef;
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
    if(auto i = std::dynamic_pointer_cast<XsdInclude>(element); i)
      includes.push_back(i);
  return includes;
}

/**
 * @return The children elements that are of the type {@link XsdImport}.
 */
std::list<std::shared_ptr<XsdImport>> XsdSchema::getChildrenImports(void)
{
  std::list<std::shared_ptr<XsdImport>> imports;
  for(auto& element : getXsdElements())
    if(auto i = std::dynamic_pointer_cast<XsdImport>(element); i)
      imports.push_back(i);
  return imports;
}

/**
 * @return The children elements that are of the type {@link XsdAnnotation}.
 */
std::list<std::shared_ptr<XsdAnnotation>> XsdSchema::getChildrenAnnotations(void)
{
  std::list<std::shared_ptr<XsdAnnotation>> annotations;
  for(auto& element : getXsdElements())
    if(auto a = std::dynamic_pointer_cast<XsdAnnotation>(element); a)
      annotations.push_back(a);
  return annotations;
}

/**
 * @return The children elements that are of the type {@link XsdSimpleType}.
 */
std::list<std::shared_ptr<XsdSimpleType>> XsdSchema::getChildrenSimpleTypes(void)
{
  std::list<std::shared_ptr<XsdSimpleType>> simple_types;
  for(auto& element : getXsdElements())
    if(auto st = std::dynamic_pointer_cast<XsdSimpleType>(element); st)
      simple_types.push_back(st);
  return simple_types;
}

/**
 * @return The children elements that are of the type {@link XsdComplexType}.
 */
std::list<std::shared_ptr<XsdComplexType>> XsdSchema::getChildrenComplexTypes(void)
{
  std::list<std::shared_ptr<XsdComplexType>> complex_types;
  for(auto& element : getXsdElements())
    if(auto ct = std::dynamic_pointer_cast<XsdComplexType>(element); ct)
      complex_types.push_back(ct);
  return complex_types;
}

/**
 * @return The children elements that are of the type {@link XsdGroup}.
 */
std::list<std::shared_ptr<XsdGroup>> XsdSchema::getChildrenGroups(void)
{
  std::list<std::shared_ptr<XsdGroup>> groups;
  for(auto& element : getXsdElements())
    if(auto g = std::dynamic_pointer_cast<XsdGroup>(element); g)
      groups.push_back(g);
  return groups;
}

/**
 * @return The children elements that are of the type {@link XsdAttributeGroup}.
 */
std::list<std::shared_ptr<XsdAttributeGroup>> XsdSchema::getChildrenAttributeGroups(void)
{
  std::list<std::shared_ptr<XsdAttributeGroup>> attribute_groups;
  for(auto& element : getXsdElements())
    if(auto ag = std::dynamic_pointer_cast<XsdAttributeGroup>(element); ag)
      attribute_groups.push_back(ag);
  return attribute_groups;
}

/**
 * @return The children elements that are of the type {@link XsdElement}.
 */
std::list<std::shared_ptr<XsdElement>> XsdSchema::getChildrenElements(void)
{
  std::list<std::shared_ptr<XsdElement>> rval;
  for(auto& element : getXsdElements())
    if(auto e = std::dynamic_pointer_cast<XsdElement>(element); e)
      rval.push_back(e);
  return rval;
}

/**
 * @return The children elements that are of the type {@link XsdAttribute}.
 */
// @SuppressWarnings("unused")
std::list<std::shared_ptr<XsdAttribute>> XsdSchema::getChildrenAttributes(void)
{
  std::list<std::shared_ptr<XsdAttribute>> attributes;
  for(auto& element : getXsdElements())
    if(auto a = std::dynamic_pointer_cast<XsdAttribute>(element); a)
      attributes.push_back(a);
  return attributes;
}

void XsdSchema::resolveNameSpace(std::optional<std::string> Namespace, std::optional<std::string> schemaLocation)
{
  if (Namespace && schemaLocation &&
      m_namespaces.contains(*Namespace))
  {
    NamespaceInfo namespaceInfo = m_namespaces.at(*Namespace);
    if(!namespaceInfo.getFile())
      namespaceInfo.setFile(*schemaLocation);
  }
}
