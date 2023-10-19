#pragma once


//#include <core/XsdParserCore.h>
#include <core/utils/ParseData.h>
#include <xsdelements/elementswrapper/ReferenceBase.h>
//#include <xsdelements/visitors/XsdAbstractElementVisitor.h>

#include <xsdelements/XsdIdentifierElements.h>

#include <list>
#include <map>
#include <functional>
#include <string_view>

class XsdAppInfo;
class XsdDocumentation;
class XsdAbstractElementVisitor;

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
public:
    XsdAnnotation(std::shared_ptr<XsdParserCore> parser,
                  StringMap elementFieldsMapParam,
                  VisitorFunctionReference visitorFunction);
public:
  void accept(std::shared_ptr<XsdAbstractElementVisitor> visitorParam);

  std::list<std::shared_ptr<XsdAppInfo>>& getAppInfoList(void);

  std::list<std::shared_ptr<XsdDocumentation>>& getDocumentations(void);

  void add(std::shared_ptr<XsdAppInfo> appInfo);

  void add(std::shared_ptr<XsdDocumentation> documentation);

  static std::shared_ptr<ReferenceBase> parse(ParseData parseData);
};
