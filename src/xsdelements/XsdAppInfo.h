#pragma once



#include <core/utils/ParseData.h>
#include <xsdelements/elementswrapper/ReferenceBase.h>
#include <xsdelements/visitors/XsdAbstractElementVisitor.h>

#include <xsdelements/XsdAnnotationChildren.h>

#include <string_view>
#include <string>
#include <map>


/**
 * A class representing the xsd:appInfo element. This class extends form {@link XsdAnnotationChildren} since it shares
 * a few similarities with {@link XsdDocumentation}, which is the other possible children of {@link XsdAnnotation}
 * elements. For more information check {@link XsdAnnotationChildren}.
 *
 * @see <a href="https://www.w3schools.com/xml/el_appinfo.asp">xsd:appInfo element description and usage at w3c</a>
 */
class XsdAppInfo : public XsdAnnotationChildren
{
public:
  using XsdAnnotationChildren::clone;
    constexpr static const std::string_view XSD_TAG = "xsd:appinfo";
    constexpr static const std::string_view XS_TAG = "xs:appinfo";
    constexpr static const std::string_view TAG = "appinfo";

private:
    XsdAppInfo(std::shared_ptr<XsdParserCore> parser,
               StringMap elementFieldsMapParam)
      : XsdAnnotationChildren(parser, elementFieldsMapParam) { }

public:
  void accept(std::shared_ptr<XsdAbstractElementVisitor> visitorParam)
    {
        XsdAnnotationChildren::accept(visitorParam);
        visitorParam->visit(nondeleted_ptr<XsdAppInfo>(this));
    }

  static std::shared_ptr<ReferenceBase> parse(ParseData parseData)
    {
        return xsdAnnotationChildrenParse(parseData.node, std::shared_ptr<XsdAnnotationChildren>(new XsdAppInfo(parseData.parserInstance, XsdAbstractElement::getAttributesMap(parseData.node))));
    }
};
