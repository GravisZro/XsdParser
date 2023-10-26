#pragma once

#include <core/utils/SchemaLocation.h>
#include <core/utils/CommonTypes.h>

#include <pugixml.hpp>


#include <core/utils/ParserConfig.h>
#include <xsdelements/XsdSchema.h>

#include "XsdParserCore.h"

/**
 * {@link XsdParser} in the core class of the XsdParser project. It functions as a one shot class, receiving the name
 * of the file to parse in its constructor and storing the parse results in its multiple fields, which can be consulted
 * after the instance is created.
 */
class XsdParser : public XsdParserCore,
    public std::enable_shared_from_this<XsdParser>
{
public:
  XsdParser(void) = default;
  virtual ~XsdParser(void) = default;
  virtual void initialize(void) { }
#if 0
    /**
     * The XsdParser constructor will parse the XSD file with the {@code filepath} and will also parse all the subsequent
     * XSD files with their path present in xsd:import and xsd:include tags. After parsing all the XSD files present it
     * resolves the references existent in the XSD language, represented by the ref attribute. When this method finishes
     * the parse results and remaining unsolved references are accessible by the {@link XsdParser#getResultXsdSchemas()},
     * {@link XsdParser#getResultXsdElements()} and {@link XsdParser#getUnsolvedReferences()}.
     * @param filePath States the path of the XSD file to be parsed.
     */
  XsdParser(std::string filePath){
        parse(filePath);
    }

    /**
     * The XsdParser constructor will parse the XSD file with the {@code filepath} and will also parse all the subsequent
     * XSD files with their path present in xsd:import and xsd:include tags. After parsing all the XSD files present it
     * resolves the references existent in the XSD language, represented by the ref attribute. When this method finishes
     * the parse results and remaining unsolved references are accessible by the {@link XsdParser#getResultXsdSchemas()},
     * {@link XsdParser#getResultXsdElements()} and {@link XsdParser#getUnsolvedReferences()}.
     * @param filePath States the path of the XSD file to be parsed.
     * @param config Config for the parser.
     */
  XsdParser(std::string filePath, ParserConfig config)
  {
        XsdParserCore::updateConfig(config);
        parse(filePath);
  }
#endif
    void parse(std::string filePath);
private:

    /**
     * Parses a XSD file and all its containing XSD elements. This code iterates on the nodes and parses the supported
     * ones. The supported types are all the XSD types that have their tag present in the {@link XsdParser#parseMappers}
     * field.
     * @param schemaLocation The location of the XSD file.
     */
  void parseLocation(const SchemaLocation& schemaLocation);


  pugi::xml_node getSchemaNode(SchemaLocation schemaLocation);

private:
  std::map<std::string, pugi::xml_document> m_documents;
};
