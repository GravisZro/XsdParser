#pragma once

#include <core/utils/ConfigEntryData.h>

#include <core/utils/ParserConfig.h>
#include <xsdelements/XsdSchema.h>
#include <xsdelements/elementswrapper/ReferenceBase.h>
#include <xsdelements/exceptions/ParsingException.h>
#include <core/XsdParserCore.h>



class XsdParserJar : public XsdParserCore
{

    private static ClassLoader classLoader;

    /**
     * Adds the jar file represented the jarPath to the classpath and proceeds by parsing the file present in the
     * previous jar with the path filePath.
     * @param jarPath The path to the jar file.
     * @param filePath The filePath of the XSD file to parse. Relative to the Jar structure.
     */
  XsdParserJar(std::string jarPath, std::string filePath){
        parse(jarPath, filePath);
    }

    /**
     * Adds the jar file represented the jarPath to the classpath and proceeds by parsing the file present in the
     * previous jar with the path filePath.
     * @param jarPath The path to the jar file.
     * @param filePath The filePath of the XSD file to parse. Relative to the Jar structure.
     * @param config Config for the parser.
     */
  XsdParserJar(std::string jarPath, std::string filePath, ParserConfig config){
        XsdParserCore::updateConfig(config);

        parse(jarPath, filePath);
    }

    private void parse(std::string jarPath, std::string filePath){
        setClassLoader(jarPath);

        parseJarFile(filePath);

        int index = 0;

        while (m_unparsedSchemaLocations.size() > index){
            std::string schemaLocation = m_schemaLocations.get(index);
            parseJarFile(schemaLocation);
            ++index;
        }

        resolveRefs();
    }

    /**
     * Parses the XSD file represented by the received InputStream.
     * @param filePath The filePath of the XSD file.
     */
    private void parseJarFile(std::string filePath) {
        //https://www.mkyong.com/java/how-to-read-xml-file-in-java-dom-parser/
        m_currentSchemaLocation = filePath.replace("\\", "/");
        InputStream inputStream = classLoader.getResourceAsStream(filePath);

        try {
//            DOMNode schemaNode = getSchemaNode(inputStream);
//
//            if (isXsdSchema(schemaNode)){
//                ConfigEntryData xsdSchemaConfig = parseMappers.getOrDefault(TAG<XsdSchema>::xsd, parseMappers.getOrDefault(XsdSchema::XS_TAG, null));
//
//                if (xsdSchemaConfig == null){
//                    throw ParserConfigurationException("XsdSchema not correctly configured.");
//                }
//
//                xsdSchemaConfig.parserFunction( ParseData { nondeleted_ptr<XsdParserCore>(this), schemaNode, xsdSchemaConfig.visitorFunction }));
//            } else {
//                throw ParsingException("The top level element of a XSD file should be the xsd:schema node.");
//            }

            ConfigEntryData xsdSchemaConfig = m_parseMappers.getOrDefault(TAG<XsdSchema>::xsd, m_parseMappers.getOrDefault(XsdSchema::XS_TAG, null));

            if (xsdSchemaConfig == null){
                throw ParserConfigurationException("XsdSchema not correctly configured.");
            }

            ReferenceBase schemaReference = xsdSchemaConfig.parserFunction( ParseData { nondeleted_ptr<XsdParserCore>(this), getSchemaNode(inputStream), xsdSchemaConfig.visitorFunction }));
        } catch (SAXException | IOException | ParserConfigurationException e) {
            Logger.getAnonymousLogger().log(Level.SEVERE, "Exception while parsing.", e);
            throw RuntimeException(e);
        }
    }

private:
  pugi::xml_node getSchemaNode(InputStream inputStream) // throws ParserConfigurationException, IOException, SAXException
  {
        DOMDocument doc;

        doc.getDocumentElement().normalize();

        DOMNodeList nodes = doc.getChildNodes();

        for (int i = 0; i < nodes.getLength(); i++) {
            pugi::xml_node node = nodes.item(i);
            if (isXsdSchema(node)){
                return node;
            }
        }

        throw ParsingException("The top level element of a XSD file should be the xsd:schema node.");
    }

    /**
     * Creates a new class loader, replacing the current one, having another path added to the classpath. The new
     * path is the path to the jar received in this class constructor.
     * @param jarPath The path of the jar file.
     */
    private void setClassLoader(std::string jarPath) {
        if (!jarPath.endsWith(".jar")){
            throw ParsingException("The jarPath received doesn't represent a jar file.");
        }

        ClassLoader originalCl = Thread.currentThread().getContextClassLoader();

        URL url = originalCl.getResource(jarPath);

        if (url == null){
            try {
                url = new URL("file:/" + jarPath);
            } catch (MalformedURLException e) {
                throw ParsingException("Invalid jar name.");
            }
        }

        // Create class loader using given codebase
        // Use prevCl as parent to maintain current visibility
        ClassLoader urlCl = URLClassLoader.newInstance(new URL[]{url}, originalCl);

        Thread.currentThread().setContextClassLoader(urlCl);

        classLoader = urlCl;
    }
}
