#pragma once

#include <core/utils/SchemaLocation.h>
#include <core/utils/CommonTypes.h>
#include <core/utils/ParseData.h>
#include <xsdelements/elementswrapper/ReferenceBase.h>
#include <xsdelements/visitors/XsdAbstractElementVisitor.h>
#include <xsdelements/XsdAnnotatedElements.h>


/**
 * A class representing the xsd:import element.
 *
 * @see <a href="https://www.w3schools.com/xml/el_import.asp">xsd:import description and usage at w3c</a>
 */
class XsdImport : public XsdAnnotatedElements
{
public:
  using XsdAnnotatedElements::clone;
    constexpr static const std::string_view XSD_TAG = "xsd:import";
    constexpr static const std::string_view XS_TAG = "xs:import";
    constexpr static const std::string_view TAG = "import";

private:
    /**
     * Specifies the a namespace to import.
     */
    std::optional<std::string> m_namespace;

    /**
     * Specifies the URI to the schema for the imported namespace.
     * In this project this attribute is used to specify another file location that contains more element definitions
     * that belong to the same XSD language definition.
     */
    SchemaLocation m_schemaLocation;
public: // ctors
    XsdImport(std::shared_ptr<XsdParserCore> parser,
              StringMap attributesMap,
              VisitorFunctionType visitorFunction,
              std::shared_ptr<XsdAbstractElement> parent);
public:
  void accept(std::shared_ptr<XsdAbstractElementVisitor> visitorParam) override
    {
        XsdAnnotatedElements::accept(visitorParam);
        visitorParam->visit(std::static_pointer_cast<XsdImport>(shared_from_this()));
    }

  std::optional<std::string> getNamespace(void) {
        return m_namespace;
    }

  SchemaLocation getSchemaLocation(void) {
        return m_schemaLocation;
    }
};
