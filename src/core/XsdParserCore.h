#pragma once

#include <pugixml.hpp>

#include <core/utils/SchemaLocation.h>
#include <core/utils/CommonTypes.h>

#include <core/utils/ConfigEntryData.h>
#include <core/utils/UnsolvedReferenceItem.h>
#include <core/utils/ParserConfig.h>

#include <xsdelements/elementswrapper/ConcreteElement.h>
#include <xsdelements/elementswrapper/NamedConcreteElement.h>
#include <xsdelements/elementswrapper/ReferenceBase.h>
#include <xsdelements/elementswrapper/UnsolvedReference.h>
#include <xsdelements/exceptions/ParentAvailableException.h>


class XsdElement;
class XsdSchema;

class XsdParserCore
{
private:
    static ParserConfig m_config;
    /**
     * A {@link Map} object that contains the all the XSD types and their respective types in the Java
     * language.
     */
    static StringMap m_xsdTypesToCpp;


    /**
     * A {@link List} of {@link UnsolvedReference} elements that weren't solved. This list is consulted after all the
     * elements are parsed in order to find if there is any suitable parsed element to replace the unsolved element.
     */
    std::map<SchemaLocation, std::list<std::shared_ptr<UnsolvedReference>>> m_unsolvedElements;

    /**
     * A {@link List} containing all the elements that even after parsing all the elements on the file, don't have a
     * suitable object to replace the reference. This list can be consulted after the parsing process to assert if there
     * is any missing information in the XSD file.
     */
    std::list<std::shared_ptr<UnsolvedReferenceItem>> m_parserUnsolvedElements;

protected:
    SchemaLocation m_currentSchemaFile;

    /**
     * A {@link Map} object that contains a parse function to each {@link XsdAbstractElement} concrete
     * type supported by this mapper, this way based on the concrete {@link XsdAbstractElement} tag the according parse
     * method can be invoked.
     */
    static std::map<std::string_view, ConfigEntryData> m_parseMappers;

    /**
     * A {@link List} which contains all the top elements parsed by this class.
     */
  std::map<SchemaLocation, std::list<std::shared_ptr<ReferenceBase>>> m_parseElements;
    /**
     * A {@link List} containing the paths of files that were present in either {@link XsdInclude} or {@link XsdImport}
     * objects that are present in the original or subsequent files. These paths are stored to be parsed as well, the
     * parsing process only ends when all the files present in this {@link List} are parsed.
     */
  std::set<SchemaLocation> m_schemaLocations;
  std::map<SchemaLocation, SchemaLocation> m_schemaLocationsMap;

public:
    /**
     * Verifies if a given {@link DOMNode} object, i.e. {@code node} is a xsd:schema node.
     * @param node The node to verify.
     * @return True if the node is a xsd:schema or xs:schema. False otherwise.
     */
    bool isXsdSchema(pugi::xml_node node);

    /**
     * This method resolves all the remaining {@link UnsolvedReference} objects present after all the elements are parsed.
     * It starts by iterating all {@link XsdParser#parseElements} and inserting all the parsed elements with a name
     * attribute in the concreteElementsMap variable. After that it iterates on the {@link XsdParser#unsolvedElements}
     * list in order to find if any of the unsolvedReferences can be solved by replacing the unsolvedElement by its
     * matching {@link NamedConcreteElement} object, present in the concreteElementsMap. The {@link UnsolvedReference}
     * objects matches a {@link NamedConcreteElement} object by having its ref attribute with the same value as the
     * name attribute of the {@link NamedConcreteElement}.
     */
    void resolveRefs(void)
    {
      resolveInnerRefs();
      resolveOtherNamespaceRefs();
    }

    private:
    void resolveOtherNamespaceRefs(void);
    void replaceUnsolvedImportedReference(std::map<std::string, std::list<std::shared_ptr<NamedConcreteElement>>> concreteElementsMap,
                                          std::shared_ptr<UnsolvedReference> unsolvedReference,
                                          SchemaLocation fileLocation);
    
    void resolveInnerRefs(void);

    /**
     * Replaces a single {@link UnsolvedReference} object, with the respective {@link NamedConcreteElement} object. If
     * there isn't a {@link NamedConcreteElement} object to replace the {@link UnsolvedReference} object, information
     * is stored informing the user of this Project of the occurrence.
     * @param concreteElementsMap The map containing all named concreteElements.
     * @param unsolvedReference The unsolved reference to solve.
     */
    void replaceUnsolvedReference(std::map<std::string, std::list<std::shared_ptr<NamedConcreteElement>>> concreteElementsMap,
                                  std::shared_ptr<UnsolvedReference> unsolvedReference,
                                  SchemaLocation fileLocation);

    /**
     * Saves an occurrence of an element which couldn't be resolved in the {@link XsdParser#replaceUnsolvedReference}
     * method, which can be accessed at the end of the parsing process in order to verify if were there were any
     * references that couldn't be solved.
     * @param unsolvedReference The unsolved reference which couldn't be resolved.
     */
    void storeUnsolvedItem(std::shared_ptr<UnsolvedReference> unsolvedReference);
public:
    /**
     * @return The {@link List} of {@link UnsolvedReferenceItem} that represent all the objects with a reference that couldn't
     * be solved.
     */
  std::list<std::shared_ptr<UnsolvedReferenceItem>> getUnsolvedReferences(void) const
  {
    return m_parserUnsolvedElements;
  }

    /**
     * @return A list of all the top level parsed xsd:elements by this class. It doesn't return any other elements apart
     * from xsd:elements. To access the whole element tree use {@link XsdParser#getResultXsdSchemas()}
     */
  std::list<std::shared_ptr<XsdAbstractElement>> getResultXsdElements(void);

  std::list<std::shared_ptr<XsdElement>> getResultChildrenElements(void);

    /**
     * @return A {@link List} of all the {@link XsdSchema} elements parsed by this class. You can use the {@link XsdSchema}
     * instances to navigate through the whole element tree.
     */
  std::list<std::shared_ptr<XsdSchema>> getResultXsdSchemas(void);



    /**
     * Adds an {@link UnsolvedReference} object to the {@link XsdParser#unsolvedElements} list which should be solved
     * at a later time in the parsing process.
     * @param unsolvedReference The unsolvedReference to add to the unsolvedElements list.
     */
  void addUnsolvedReference(std::shared_ptr<UnsolvedReference> unsolvedReference);

    /**
     * Adds a new file to the parsing queue. This new file appears by having xsd:import or xsd:include tags in the
     * original file to parse.
     * @param schemaLocation A new file path of another XSD file to parse.
     */
  void addLocationToParse(SchemaLocation schemaLocation);

  static StringMap getXsdTypesToCpp(void)
  {
    return m_xsdTypesToCpp;
  }

  static std::map<std::string_view, ConfigEntryData> getParseMappers(void)
  {
    return m_parseMappers;
  }

  void addParsedElement(std::shared_ptr<ReferenceBase> wrappedElement)
  {
    m_parseElements[m_currentSchemaFile].push_back(wrappedElement);
  }

  static void updateConfig(ParserConfig config)
  {
    m_xsdTypesToCpp = config.getXsdTypesToCpp();
    m_parseMappers = config.getParseMappers();
  }
};
