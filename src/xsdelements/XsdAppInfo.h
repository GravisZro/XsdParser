#pragma once




#include <xsdelements/elementswrapper/ReferenceBase.h>
#include <xsdelements/visitors/XsdAbstractElementVisitor.h>

#include <xsdelements/XsdAnnotationChildren.h>

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

public: // ctors
    XsdAppInfo(std::shared_ptr<XsdParserCore> parser,
               StringMap attributesMap,
               VisitorFunctionType visitorFunction,
               std::shared_ptr<XsdAbstractElement> parent)
      : XsdAnnotationChildren(parser, attributesMap, visitorFunction, parent) { }

public:
  void accept(std::shared_ptr<XsdAbstractElementVisitor> visitorParam) override
    {
        XsdAnnotationChildren::accept(visitorParam);
        visitorParam->visit(std::static_pointer_cast<XsdAppInfo>(shared_from_this()));
    }
};
