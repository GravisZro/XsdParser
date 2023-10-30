#pragma once

#include <xsdelements/visitors/XsdAbstractElementVisitor.h>
#include <xsdelements/XsdAnnotationChildren.h>

/**
 * A class representing the xsd:documentation element. This class extends from {@link XsdAnnotationChildren} since it
 * shares a few similarities with {@link XsdAppInfo}, which is the other possible children of {@link XsdAnnotation}
 * elements. For more information check {@link XsdAnnotationChildren}.
 *
 * @see <a href="https://www.w3schools.com/xml/el_documentation.asp">xsd:documentation element description and usage at w3c</a>
 */
class XsdDocumentation : public XsdAnnotationChildren
{
public: // ctors
  XsdDocumentation(StringMap attributesMap,
                   VisitorFunctionType visitorFunction,
                   XsdAbstractElement* parent)
    : XsdAnnotationChildren(attributesMap, visitorFunction, parent)
  {
    if(haveAttribute(XML_LANG_TAG))
      m_xmlLang = getAttribute(XML_LANG_TAG);
  }

public:
  void accept(XsdAbstractElementVisitor* xsdAbstractElementVisitor) override
  {
    XsdAnnotationChildren::accept(xsdAbstractElementVisitor);
    xsdAbstractElementVisitor->visit(static_cast<XsdDocumentation*>(this));
  }

private:
  /**
    * Specifies the language used in the {@link XsdAnnotationChildren#content}
    */
  std::string m_xmlLang;
};
