#include "XsdParser.h"


#include <core/utils/ConfigEntryData.h>
#include <xsdelements/exceptions/ParsingException.h>


void XsdParser::parse(std::string filePath)
{
    m_schemaLocations.push_back(filePath);
    for(auto& schemaLocation : m_schemaLocations)
      parseFile(schemaLocation);
    resolveRefs();
}

/**
 * Parses a XSD file and all its containing XSD elements. This code iterates on the nodes and parses the supported
 * ones. The supported types are all the XSD types that have their tag present in the {@link XsdParser#parseMappers}
 * field.
 * @param filePath The path to the XSD file.
 */
void XsdParser::parseFile(std::string filePath)
{
  // TODO
  /*
    //https://www.mkyong.com/java/how-to-read-xml-file-in-java-dom-parser/

    try {
        if (!new File(filePath).exists() && isRelativePath(filePath)){
            std::string parentFile = m_schemaLocationsMap.get(filePath);

            filePath  = parentFile.substring(0, parentFile.lastIndexOf('/') + 1).concat(filePath);

            if (!new File(filePath).exists()) {
                throw new FileNotFoundException(filePath);
            }
        }

        m_currentFile = filePath.replace("\\", "/");

        ConfigEntryData xsdSchemaConfig = parseMappers.getOrDefault(XsdSchema::XSD_TAG, parseMappers.getOrDefault(XsdSchema::XS_TAG, null));

        if (xsdSchemaConfig == null){
            throw new ParserConfigurationException("XsdSchema not correctly configured.");
        }

        ReferenceBase schemaReference = xsdSchemaConfig.parserFunction({ std::make_shared<XsdParserCore>(this), getSchemaNode(filePath), xsdSchemaConfig.visitorFunction});
        ((XsdSchema)schemaReference.getElement()).setFilePath(filePath);
    } catch (SAXException | IOException | ParserConfigurationException e) {
        Logger.getAnonymousLogger().log(Level.SEVERE, "Exception while parsing.", e);
        throw new RuntimeException(e);
    }
*/
}


/**
 * This function uses DOM to obtain a list of nodes from a XSD file.
 * @param filePath The path to the XSD file.
 * @throws IOException If the file parsing throws {@link IOException}.
 * @throws SAXException if the file parsing throws {@link SAXException}.
 * @throws ParserConfigurationException If the {@link DocumentBuilderFactory#newDocumentBuilder()} throws
 *      {@link ParserConfigurationException}.
 * @return A list of nodes that represent the node tree of the XSD file with the path received.
 */
pugi::xml_node XsdParser::getSchemaNode(std::string filePath) //throws IOException, SAXException, ParserConfigurationException
{
  pugi::xml_document doc;
  pugi::xml_parse_result result = doc.load_file(filePath.c_str());
  assert(result);

  for(auto& child : doc.children())
    if (isXsdSchema(child))
        return child;

      throw new ParsingException("The top level element of a XSD file should be the xsd:schema node.");
  }
