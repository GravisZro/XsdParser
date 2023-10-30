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
  XsdAppInfo(StringMap attributesMap,
             VisitorFunctionType visitorFunction,
             XsdAbstractElement* parent)
    : XsdAnnotationChildren(attributesMap, visitorFunction, parent)
  {
  }

public:
  void accept(XsdAbstractElementVisitor* visitorParam) override
  {
    XsdAnnotationChildren::accept(visitorParam);
    visitorParam->visit(static_cast<XsdAppInfo*>(this));
  }
};
