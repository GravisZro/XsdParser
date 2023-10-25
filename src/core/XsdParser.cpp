#include "XsdParser.h"

#include <iostream>
#include <filesystem>

#include <core/utils/ConfigEntryData.h>
#include <xsdelements/exceptions/ParsingException.h>

void XsdParser::parse(std::string filePath)
{
  m_currentFile.setParentPaths(std::filesystem::current_path().string());
  m_currentFile = filePath;
  if(!m_schemaLocations.contains(filePath))
    m_schemaLocations.insert(filePath);

  for(auto& schemaLocation : m_schemaLocations)
  {
    addLocationToParse(schemaLocation);
    parseLocation(schemaLocation);
  }
  resolveRefs();
}

/**
 * Parses a XSD file and all its containing XSD elements. This code iterates on the nodes and parses the supported
 * ones. The supported types are all the XSD types that have their tag present in the {@link XsdParser#parseMappers}
 * field.
 * @param filePath The path to the XSD file.
 */
void XsdParser::parseLocation(const SchemaLocation& fileLocation)
{
  m_currentFile = fileLocation;
  ConfigEntryData xsdSchemaConfig;

  if(m_parseMappers.contains(TAG<XsdSchema>::xsd))
    xsdSchemaConfig = m_parseMappers.at(TAG<XsdSchema>::xsd);
  else if(m_parseMappers.contains(TAG<XsdSchema>::xs))
    xsdSchemaConfig = m_parseMappers.at(TAG<XsdSchema>::xs);

  if (xsdSchemaConfig.parserFunction == nullptr &&
      xsdSchemaConfig.visitorFunction == nullptr)
    throw std::runtime_error("XsdSchema not correctly configured.");

  auto schemaReference = xsdSchemaConfig.parserFunction(shared_from_this(),
                                                        getSchemaNode(fileLocation),
                                                        xsdSchemaConfig.visitorFunction,
                                                        nullptr);
  std::static_pointer_cast<XsdSchema>(schemaReference->getElement())->setFileLocation(fileLocation);
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
pugi::xml_node XsdParser::getSchemaNode(SchemaLocation fileLocation)
{
  std::optional<std::string> filePath;
  for(const std::string& location : fileLocation.data())
  {
    if(std::filesystem::exists(location))
    {
      filePath = location;
      break;
    }
  }
  assert(filePath);

  std::cout << "file path: " << *filePath << std::endl;

  pugi::xml_document& doc = m_documents[*filePath];
  pugi::xml_parse_result result = m_documents[*filePath].load_file(filePath->c_str());
  assert(result);

  for(auto& child : doc.children())
    if (isXsdSchema(child))
      return child;

  throw ParsingException("The top level element of a XSD file should be the xsd:schema node.");
}
