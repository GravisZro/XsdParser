#pragma once

#include <core/utils/SchemaLocation.h>
#include <core/utils/CommonTypes.h>

#include <xsdelements/visitors/XsdAbstractElementVisitor.h>
#include <xsdelements/XsdAnnotatedElements.h>


/**
 * A class representing the xsd:import element.
 *
 * @see <a href="https://www.w3schools.com/xml/el_import.asp">xsd:import description and usage at w3c</a>
 */
class XsdImport : public XsdAnnotatedElements
{
public: // ctors
  XsdImport(StringMap attributesMap,
            VisitorFunctionType visitorFunction,
            XsdAbstractElement* parent);

public:
  void accept(XsdAbstractElementVisitor* visitorParam) override
  {
    XsdAnnotatedElements::accept(visitorParam);
    visitorParam->visit(static_cast<XsdImport*>(this));
  }

  std::optional<std::string> getNamespace(void) const
  {
    return m_namespace;
  }

  SchemaLocation getSchemaLocation(void) const
  {
    return m_schemaLocation;
  }

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
  std::string m_schemaLocation;
};
