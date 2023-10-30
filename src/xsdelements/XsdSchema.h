#pragma once

#include <core/utils/SchemaLocation.h>
#include <core/utils/NamespaceInfo.h>
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
class ReferenceBase;

class XsdSchema : public XsdAnnotatedElements
{
public: // ctors
  XsdSchema(StringMap attributesMap,
            VisitorFunctionType visitorFunction,
            XsdAbstractElement* parent);
public:
  std::list<XsdAbstractElement*> getXsdElements(void) const override
  {
    return m_elements;
  }

  virtual std::list<ReferenceBase*> getElements(void) const override;

  void updatePrefixLocations(std::map<std::string, SchemaLocation> prefixLocations)
  {
    for(auto& pair : prefixLocations)
    {
      assert(m_namespaces.contains(pair.first));
      m_namespaces.at(pair.first).setLocation(pair.second);
    }
  }

  void add(XsdAbstractElement* element);

  std::optional<std::string> getAttributeFormDefault(void) const
  {
    return m_attributeFormDefault;
  }

  std::optional<std::string> getElementFormDefault(void) const
  {
    return m_elementFormDefault;
  }

  std::optional<std::string> getBlockDefault(void) const
  {
    return m_blockDefault;
  }
    
  std::optional<std::string> getFinalDefault(void) const
  {
    return m_finalDefault;
  }

  std::optional<std::string> getTargetNamespace(void) const
  {
    return m_targetNamespace;
  }

  std::optional<std::string> getVersion(void) const
  {
    return m_version;
  }

  /**
   * @tparam One of the following classes:
   *      * {@link XsdInclude}
   *      * {@link XsdImport}
   *      * {@link XsdAnnotation}
   *      * {@link XsdSimpleType}
   *      * {@link XsdComplexType}
   *      * {@link XsdGroup}
   *      * {@link XsdAttributeGroup}
   *      * {@link XsdElement}
   *      * {@link XsdAttribute}
   * @return The children elements that are of the templated type.
   */
  template<typename T, std::enable_if_t<std::is_same_v<XsdInclude       , T> ||
                                        std::is_same_v<XsdImport        , T> ||
                                        std::is_same_v<XsdAnnotation    , T> ||
                                        std::is_same_v<XsdSimpleType    , T> ||
                                        std::is_same_v<XsdComplexType   , T> ||
                                        std::is_same_v<XsdGroup         , T> ||
                                        std::is_same_v<XsdAttributeGroup, T> ||
                                        std::is_same_v<XsdElement       , T> ||
                                        std::is_same_v<XsdAttribute     , T>, bool> = true>
  std::list<T*> getChildren(void) const
  {
    std::list<T*> targets;
    for(auto& element : getXsdElements())
      if(auto x = dynamic_cast<T*>(element); x != nullptr)
        targets.push_back(x);
    return targets;
  }

  void resolveNameSpace(std::optional<std::string> Namespace, SchemaLocation schemaLocation);

  std::map<std::string, NamespaceInfo> getNamespaces(void) const
  {
    return m_namespaces;
  }

  SchemaLocation getSchemaLocation(void) const
  {
    return m_schemaLocation;
  }

  void setSchemaLocation(SchemaLocation schemaLocation)
  {
    m_schemaLocation = schemaLocation;
  }

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

  SchemaLocation m_schemaLocation;

  std::map<std::string, NamespaceInfo> m_namespaces;

  /**
   * The children elements contained in this {@link XsdSchema} element.
   */
  std::list<XsdAbstractElement*> m_elements;
};
