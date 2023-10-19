#include "XsdAnnotation.h"

#include <xsdelements/XsdDocumentation.h>
#include <xsdelements/XsdAppInfo.h>


XsdAnnotation::XsdAnnotation(std::shared_ptr<XsdParserCore> parser,
              StringMap elementFieldsMapParam,
              VisitorFunctionReference visitorFunction)
  : XsdIdentifierElements(parser, elementFieldsMapParam, visitorFunction)
{ }

void XsdAnnotation::accept(std::shared_ptr<XsdAbstractElementVisitor> visitorParam)
{
    XsdIdentifierElements::accept(visitorParam);
    visitorParam->visit(std::shared_ptr<XsdAnnotation>(this));
}

std::list<std::shared_ptr<XsdAppInfo>>& XsdAnnotation::getAppInfoList(void)
{
    return m_appInfoList;
}

std::list<std::shared_ptr<XsdDocumentation>>& XsdAnnotation::getDocumentations(void)
{
    return m_documentations;
}

void XsdAnnotation::add(std::shared_ptr<XsdAppInfo> appInfo)
{
    m_appInfoList.push_back(appInfo);
}

void XsdAnnotation::add(std::shared_ptr<XsdDocumentation> documentation)
{
    m_documentations.push_back(documentation);
}

std::shared_ptr<ReferenceBase> XsdAnnotation::parse(ParseData parseData)
{
    return xsdParseSkeleton(parseData.node, std::static_pointer_cast<XsdAbstractElement>(std::make_shared<XsdAnnotation>(parseData.parserInstance, XsdAbstractElement::getAttributesMap(parseData.node), parseData.visitorFunction)));
}
