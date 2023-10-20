#pragma once



#include <core/utils/ParseData.h>
#include <xsdelements/elementswrapper/ReferenceBase.h>
#include <xsdelements/visitors/XsdAbstractElementVisitor.h>
#include <xsdelements/XsdAnnotationChildren.h>

#include <map>

/**
 * A class representing the xsd:documentation element. This class extends from {@link XsdAnnotationChildren} since it
 * shares a few similarities with {@link XsdAppInfo}, which is the other possible children of {@link XsdAnnotation}
 * elements. For more information check {@link XsdAnnotationChildren}.
 *
 * @see <a href="https://www.w3schools.com/xml/el_documentation.asp">xsd:documentation element description and usage at w3c</a>
 */
class XsdDocumentation : public XsdAnnotationChildren
{
public:
  using XsdAnnotationChildren::clone;
    constexpr static const std::string_view XSD_TAG = "xsd:documentation";
    constexpr static const std::string_view XS_TAG = "xs:documentation";
    constexpr static const std::string_view TAG = "documentation";

private:
    /**
     * Specifies the language used in the {@link XsdAnnotationChildren#content}
     */
    std::string m_xmlLang;
public:
    XsdDocumentation(std::shared_ptr<XsdParserCore> parser, StringMap attributesMap)
        : XsdAnnotationChildren(parser, attributesMap)
    {
      if(attributesMap.contains(*XML_LANG_TAG))
        m_xmlLang = attributesMap.at(*XML_LANG_TAG);
    }
public:
  void accept(std::shared_ptr<XsdAbstractElementVisitor> xsdAbstractElementVisitor)
    {
        XsdAnnotationChildren::accept(xsdAbstractElementVisitor);
        xsdAbstractElementVisitor->visit(nondeleted_ptr<XsdDocumentation>(this));
    }

  static std::shared_ptr<ReferenceBase> parse(ParseData parseData)
  {
        return xsdAnnotationChildrenParse(parseData.node, std::shared_ptr<XsdAnnotationChildren>(new XsdDocumentation(parseData.parserInstance, XsdAbstractElement::getAttributesMap(parseData.node))));
    }
};