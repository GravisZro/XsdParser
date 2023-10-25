#pragma once

#include <core/utils/SchemaLocation.h>
#include <core/utils/NamespaceInfo.h>
#include <xsdelements/elementswrapper/ReferenceBase.h>
#include <xsdelements/enums/BlockDefaultEnum.h>
#include <xsdelements/enums/FinalDefaultEnum.h>
#include <xsdelements/enums/FormEnum.h>

#include <xsdelements/XsdAnnotatedElements.h>

class XsdInclude;
class XsdImport;
class XsdSimpleType;
class XsdComplexType;
class XsdGroup;
class XsdAttributeGroup;
class XsdElement;
class XsdAttribute;

class XsdSchema : public XsdAnnotatedElements
{
private:
    /**
     * Specifies if the form attribute for the current {@link XsdSchema} children attributes. The default value is
     * "unqualified". Other possible value is "qualified".
     */
    FormEnum m_attributeFormDefault;

    /**
     * Specifies if the form attribute for the current {@link XsdSchema} children elements. The default value is
     * "unqualified". Other possible value is "qualified".
     */
    FormEnum m_elementFormDefault;

    /**
     * Specifies if the block attribute for the current {@link XsdSchema} children such as {@link XsdElement} and
     * {@link XsdComplexType}. The default value is "". Other possible value are "extension", "restriction",
     * "substitution" and "#all".
     */
    BlockDefaultEnum m_blockDefault;

    /**
     * Specifies if the final attribute for the current {@link XsdSchema} children such as {@link XsdElement},
     * {@link XsdSimpleType} and {@link XsdComplexType}. The default value is "". Other possible value are "extension",
     * "restriction", "list", "union" and "#all".
     */
    FinalDefaultEnum m_finalDefault;

    /**
     * A URI reference of the namespace of this {@link XsdSchema} element.
     */
    std::optional<std::string> m_targetNamespace;

    /**
     * The version of this {@link XsdSchema} element.
     */
    std::optional<std::string> m_version;

    /**
     * A URI reference that specifies one or more namespaces for use in this {@link XsdSchema}. If no prefix is assigned,
     * the schema components of the namespace can be used with unqualified references.
     */
    std::optional<std::string> m_xmlns;

    SchemaLocation m_fileLocation;

    std::map<std::string, NamespaceInfo> m_namespaces;

    /**
     * The children elements contained in this {@link XsdSchema} element.
     */
    std::list<std::shared_ptr<XsdAbstractElement>> m_elements;
public: // ctors
    XsdSchema(std::shared_ptr<XsdParserCore> parser,
              StringMap attributesMap,
              VisitorFunctionType visitorFunction,
              std::shared_ptr<XsdAbstractElement> parent)
      : XsdAnnotatedElements(parser, attributesMap, visitorFunction, parent)
    {}

public:
  virtual void initialize(void) override;
  virtual std::list<std::shared_ptr<XsdAbstractElement>> getXsdElements(void) const override
    {
        return m_elements;
    }

  virtual std::list<std::shared_ptr<ReferenceBase>> getElements(void) const override;

  

public:
  void updatePrefixLocations(std::map<std::string, SchemaLocation> prefixLocations)
  {
    for(auto& pair : prefixLocations)
    {
      assert(m_namespaces.contains(pair.first));
      m_namespaces.at(pair.first).setFile(pair.second);
    }
  }
public:

  void add(std::shared_ptr<XsdAbstractElement> element);

  std::optional<std::string> getAttributeFormDefault(void) const {
        return m_attributeFormDefault.getValue();
    }

  std::optional<std::string> getElementFormDefault(void) const {
        return m_elementFormDefault.getValue();
    }

  std::optional<std::string> getBlockDefault(void) const {
        return m_blockDefault.getValue();
    }

    
  std::optional<std::string> getFinalDefault(void) const {
        return m_finalDefault.getValue();
    }

  std::optional<std::string> getTargetNamespace(void) const {
        return m_targetNamespace;
    }

  std::optional<std::string> getVersion(void) const {
        return m_version;
    }

    /**
     * @return The children elements that are of the type {@link XsdInclude}.
     */
  std::list<std::shared_ptr<XsdInclude>> getChildrenIncludes(void) const;

    /**
     * @return The children elements that are of the type {@link XsdImport}.
     */
  std::list<std::shared_ptr<XsdImport>> getChildrenImports(void) const;

    /**
     * @return The children elements that are of the type {@link XsdAnnotation}.
     */
  std::list<std::shared_ptr<XsdAnnotation>> getChildrenAnnotations(void) const;

    /**
     * @return The children elements that are of the type {@link XsdSimpleType}.
     */
  std::list<std::shared_ptr<XsdSimpleType>> getChildrenSimpleTypes(void) const;

    /**
     * @return The children elements that are of the type {@link XsdComplexType}.
     */
  std::list<std::shared_ptr<XsdComplexType>> getChildrenComplexTypes(void) const;

    /**
     * @return The children elements that are of the type {@link XsdGroup}.
     */
  std::list<std::shared_ptr<XsdGroup>> getChildrenGroups(void) const;

    /**
     * @return The children elements that are of the type {@link XsdAttributeGroup}.
     */
  std::list<std::shared_ptr<XsdAttributeGroup>> getChildrenAttributeGroups(void) const;

    /**
     * @return The children elements that are of the type {@link XsdElement}.
     */
  std::list<std::shared_ptr<XsdElement>> getChildrenElements(void) const;

    /**
     * @return The children elements that are of the type {@link XsdAttribute}.
     */
  std::list<std::shared_ptr<XsdAttribute>> getChildrenAttributes(void) const;

  void resolveNameSpace(std::optional<std::string> Namespace, SchemaLocation schemaLocation);

  std::map<std::string, NamespaceInfo> getNamespaces(void) {
        return m_namespaces;
    }

  SchemaLocation getFileLocation(void) {
        return m_fileLocation;
    }

  void setFileLocation(SchemaLocation filePath)
  {
    m_fileLocation = filePath;
  }
};
