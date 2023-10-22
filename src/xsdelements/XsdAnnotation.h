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
public:
  using XsdIdentifierElements::clone;
  constexpr static const std::string_view XSD_TAG = "xsd:annotation";
  constexpr static const std::string_view XS_TAG = "xs:annotation";
  constexpr static const std::string_view TAG = "annotation";

private:
    /**
     * The list of {@link XsdAppInfo} children.
     */
    std::list<std::shared_ptr<XsdAppInfo>> m_appInfoList;

    /**
     * The list of {@link XsdDocumentation} children.
     */
    std::list<std::shared_ptr<XsdDocumentation>> m_documentations;
public: // ctors
  XsdAnnotation(std::shared_ptr<XsdParserCore> parser,
                StringMap attributesMap,
                VisitorFunctionType visitorFunction,
                std::shared_ptr<XsdAbstractElement> parent)
    : XsdIdentifierElements(parser, attributesMap, visitorFunction, parent)
  { }

public:
  virtual void initialize(void) override
  {
    XsdIdentifierElements::initialize();
    m_appInfoList.clear();
    m_documentations.clear();
  }

  void accept(std::shared_ptr<XsdAbstractElementVisitor> visitorParam) override;

  std::list<std::shared_ptr<XsdAppInfo>>& getAppInfoList(void);

  std::list<std::shared_ptr<XsdDocumentation>>& getDocumentations(void);

  void add(std::shared_ptr<XsdAnnotationChildren> element);
  
};
