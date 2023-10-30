#pragma once

#include <xsdelements/XsdIdentifierElements.h>

struct XsdAbstractElementVisitor;
class XsdAnnotationChildren;
class XsdAppInfo;
class XsdDocumentation;

/**
 * A class representing the xsd:annotation element.
 *
 * @see <a href="https://www.w3schools.com/xml/el_annotation.asp">xsd:annotation element description and usage at w3c</a>
 */
class XsdAnnotation : public XsdIdentifierElements
{
public: // ctors
  XsdAnnotation(StringMap attributesMap,
                VisitorFunctionType visitorFunction,
                XsdAbstractElement* parent)
    : XsdIdentifierElements(attributesMap, visitorFunction, parent)
  {
  }

public:
  void accept(XsdAbstractElementVisitor* visitorParam) override;

  const std::list<XsdAppInfo*>& getAppInfoList(void) const
  {
    return m_appInfoList;
  }

  const std::list<XsdDocumentation*>& getDocumentations(void) const
  {
    return m_documentations;
  }

  void add(XsdAnnotationChildren* element);  

private:
  /**
   * The list of {@link XsdAppInfo} children.
   */
  std::list<XsdAppInfo*> m_appInfoList;

  /**
   * The list of {@link XsdDocumentation} children.
   */
  std::list<XsdDocumentation*> m_documentations;
};
