#pragma once

#include <core/utils/SchemaLocation.h>
#include <core/utils/StringOperations.h>
#include <core/XsdParserCore.h>

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
    SchemaLocation m_schemaLocation;
public: // ctors
  XsdInclude(std::shared_ptr<XsdParserCore> parser,
             StringMap attributesMap,
             VisitorFunctionType visitorFunction,
             std::shared_ptr<XsdAbstractElement> parent)
    : XsdAnnotatedElements(parser, attributesMap, visitorFunction, parent)
  {
  }
public:
  virtual void initialize(void) override
  {
    XsdAnnotatedElements::initialize();
    m_schemaLocation.reset();
    if(haveAttribute(SCHEMA_LOCATION))
    {
      m_schemaLocation = getAttribute(SCHEMA_LOCATION);
      getParser()->addLocationToParse(m_schemaLocation);
    }
  }


  void accept(std::shared_ptr<XsdAbstractElementVisitor> visitorParam) override
    {
        XsdAnnotatedElements::accept(visitorParam);
        visitorParam->visit(std::static_pointer_cast<XsdInclude>(shared_from_this()));
    }

  SchemaLocation getSchemaLocation(void) {
        return m_schemaLocation;
    }
};
