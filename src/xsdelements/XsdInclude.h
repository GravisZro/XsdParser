#pragma once

#include <core/utils/SchemaLocation.h>
#include <core/utils/StringOperations.h>

#include <xsdelements/visitors/XsdAbstractElementVisitor.h>
#include <xsdelements/XsdAnnotatedElements.h>

/**
 * A class representing the xsd:include element.
 *
 * @see <a href="https://www.w3schools.com/xml/el_include.asp">xsd:include description and usage at w3c</a>
 */
class XsdInclude : public XsdAnnotatedElements
{
public: // ctors
  XsdInclude(StringMap attributesMap,
             VisitorFunctionType visitorFunction,
             XsdAbstractElement* parent);
public:
  void accept(XsdAbstractElementVisitor* visitorParam) override
  {
    XsdAnnotatedElements::accept(visitorParam);
    visitorParam->visit(static_cast<XsdInclude*>(this));
  }

  SchemaLocation getSchemaLocation(void) const
  {
    return m_schemaLocation;
  }

private:
  /**
   * Specifies the URI to the schema for the imported namespace.
   * In this project this attribute is used to specify another file location that contains more element definitions
   * that belong to the same XSD language definition.
   */
  std::string m_schemaLocation;
};
