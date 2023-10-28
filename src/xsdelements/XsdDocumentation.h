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
private:
  /**
    * Specifies the language used in the {@link XsdAnnotationChildren#content}
    */
  std::string m_xmlLang;
public: // ctors
  XsdDocumentation(std::shared_ptr<XsdParserCore> parser,
                   StringMap attributesMap,
                   VisitorFunctionType visitorFunction,
                   std::shared_ptr<XsdAbstractElement> parent)
    : XsdAnnotationChildren(parser, attributesMap, visitorFunction, parent) { }

  virtual void initialize(void) override
  {
    XsdAnnotationChildren::initialize();
    m_xmlLang.clear();
    if(haveAttribute(XML_LANG_TAG))
      m_xmlLang = getAttribute(XML_LANG_TAG);
  }
public:
  void accept(std::shared_ptr<XsdAbstractElementVisitor> xsdAbstractElementVisitor) override
  {
    XsdAnnotationChildren::accept(xsdAbstractElementVisitor);
    xsdAbstractElementVisitor->visit(std::static_pointer_cast<XsdDocumentation>(shared_from_this()));
  }
};
