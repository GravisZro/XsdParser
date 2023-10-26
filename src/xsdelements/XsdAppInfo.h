#pragma once

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
