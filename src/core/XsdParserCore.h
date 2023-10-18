#pragma once

#include <core/utils/CommonTypes.h>
#include <pugixml.hpp>


#include <xsdelements/elementswrapper/ConcreteElement.h>
#include <xsdelements/elementswrapper/NamedConcreteElement.h>
#include <xsdelements/elementswrapper/ReferenceBase.h>
#include <xsdelements/elementswrapper/UnsolvedReference.h>
#include <xsdelements/exceptions/ParentAvailableException.h>
#include <core/utils/ConfigEntryData.h>
#include <core/utils/UnsolvedReferenceItem.h>
#include <core/utils/ParserConfig.h>

class XsdElement;
class XsdSchema;

class XsdParserCore
{
private:
    static ParserConfig config;
    /**
     * A {@link Map} object that contains the all the XSD types and their respective types in the Java
     * language.
     */
    static StringMap xsdTypesToJava;


    /**
     * A {@link List} of {@link UnsolvedReference} elements that weren't solved. This list is consulted after all the
     * elements are parsed in order to find if there is any suitable parsed element to replace the unsolved element.
     */
    std::map<std::string, std::list<std::shared_ptr<UnsolvedReference>>> m_unsolvedElements;

    /**
     * A {@link List} containing all the elements that even after parsing all the elements on the file, don't have a
     * suitable object to replace the reference. This list can be consulted after the parsing process to assert if there
     * is any missing information in the XSD file.
     */
    std::list<std::shared_ptr<UnsolvedReferenceItem>> m_parserUnsolvedElementsMap;

protected:
    std::string m_currentFile;

public:

    /**
     * A {@link Map} object that contains a parse function to each {@link XsdAbstractElement} concrete
     * type supported by this mapper, this way based on the concrete {@link XsdAbstractElement} tag the according parse
     * method can be invoked.
     */
    static std::map<std::string, ConfigEntryData> parseMappers;// = config.getParseMappers();

    /**
     * A {@link List} which contains all the top elements parsed by this class.
     */
  std::map<std::string, std::list<std::shared_ptr<ReferenceBase>>> m_parseElements;
    /**
     * A {@link List} containing the paths of files that were present in either {@link XsdInclude} or {@link XsdImport}
     * objects that are present in the original or subsequent files. These paths are stored to be parsed as well, the
     * parsing process only ends when all the files present in this {@link List} are parsed.
     */
  std::list<std::string> m_schemaLocations;
  StringMap m_schemaLocationsMap;



  //static auto xsdTypesToJava = config.getXsdTypesToJava();

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
    void resolveRefs(void) {
        resolveInnerRefs();
        resolveOtherNamespaceRefs();
    }

    private:
    void resolveOtherNamespaceRefs(void);
    void replaceUnsolvedImportedReference(std::map<std::string, std::list<std::shared_ptr<NamedConcreteElement>>> concreteElementsMap,
                                          std::shared_ptr<UnsolvedReference> unsolvedReference,
                                          std::string fileName);
    
    void resolveInnerRefs();

    /**
     * Replaces a single {@link UnsolvedReference} object, with the respective {@link NamedConcreteElement} object. If
     * there isn't a {@link NamedConcreteElement} object to replace the {@link UnsolvedReference} object, information
     * is stored informing the user of this Project of the occurrence.
     * @param concreteElementsMap The map containing all named concreteElements.
     * @param unsolvedReference The unsolved reference to solve.
     */
    void replaceUnsolvedReference(std::map<std::string, std::list<std::shared_ptr<NamedConcreteElement>>> concreteElementsMap, UnsolvedReference unsolvedReference, std::string fileName);

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
  std::list<std::shared_ptr<UnsolvedReferenceItem>> getUnsolvedReferences(void)
  {
    return m_parserUnsolvedElementsMap;
  }

    /**
     * @return A list of all the top level parsed xsd:elements by this class. It doesn't return any other elements apart
     * from xsd:elements. To access the whole element tree use {@link XsdParser#getResultXsdSchemas()}
     */
  std::list<std::shared_ptr<XsdElement>> getResultXsdElements(void);

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
  void addFileToParse(std::string schemaLocation);

  static StringMap getXsdTypesToJava(void)
  {
    if(xsdTypesToJava.empty())
      xsdTypesToJava = config.getXsdTypesToJava();
    return xsdTypesToJava;
  }

  static std::map<std::string, ConfigEntryData> getParseMappers(void)
  {
    if(parseMappers.empty())
      parseMappers = config.getParseMappers();
    return parseMappers;
  }

  void addParsedElement(std::shared_ptr<ReferenceBase> wrappedElement)
  {
    if(m_parseElements.contains(m_currentFile))
      m_parseElements.at(m_currentFile).push_back(wrappedElement);
  }

    static void updateConfig(ParserConfig config) {
        xsdTypesToJava = config.getXsdTypesToJava();
        parseMappers = config.getParseMappers();
    }

    protected:
    bool isRelativePath(std::string filePath)
    {
        //return !filePath.matches(".*:.*");
      return false;
    }
};
