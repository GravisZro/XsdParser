#pragma once

#include <filesystem>

#include <core/utils/CommonOperations.h>
#include <core/XsdParserCore.h>
#include <core/utils/ParseData.h>
#include <xsdelements/elementswrapper/ReferenceBase.h>
#include <xsdelements/visitors/XsdAbstractElementVisitor.h>
#include <xsdelements/XsdAnnotatedElements.h>

/**
 * A class representing the xsd:include element.
 *
 * @see <a href="https://www.w3schools.com/xml/el_include.asp">xsd:include description and usage at w3c</a>
 */
class XsdInclude : public XsdAnnotatedElements
{
public:
  using XsdAnnotatedElements::clone;
    constexpr static const std::string_view XSD_TAG = "xsd:include";
    constexpr static const std::string_view XS_TAG = "xs:include";
    constexpr static const std::string_view TAG = "include";

private:
    /**
     * Specifies the URI to the schema for the imported namespace.
     * In this project this attribute is used to specify another file location that contains more element definitions
     * that belong to the same XSD language definition.
     */
    std::filesystem::path m_schemaLocation;
public:
    XsdInclude(std::shared_ptr<XsdParserCore> parser, StringMap attributesMap, VisitorFunctionReference visitorFunction)
      : XsdAnnotatedElements(parser, attributesMap, visitorFunction)
    {
      if(attributesMap.contains(*SCHEMA_LOCATION))
        m_schemaLocation = attributesMap.at(*SCHEMA_LOCATION);

      if (!m_schemaLocation.empty())
      {
        parser->addFileToParse(m_schemaLocation);
      }
    }
public:
  static std::shared_ptr<ReferenceBase> parse(ParseData parseData)
  {
    return xsdParseSkeleton(parseData.node, std::static_pointer_cast<XsdAbstractElement>(std::make_shared<XsdInclude>(parseData.parserInstance, XsdAbstractElement::getAttributesMap(parseData.node), parseData.visitorFunction)));
  }

  void accept(std::shared_ptr<XsdAbstractElementVisitor> visitorParam)
    {
        XsdAnnotatedElements::accept(visitorParam);
        visitorParam->visit(std::shared_ptr<XsdInclude>(this));
    }

  std::filesystem::path getSchemaLocation(void) {
        return m_schemaLocation;
    }
};
