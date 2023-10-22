#include "XsdAnnotation.h"

#include <xsdelements/XsdDocumentation.h>
#include <xsdelements/XsdAppInfo.h>

void XsdAnnotation::accept(std::shared_ptr<XsdAbstractElementVisitor> visitorParam)
{
    XsdIdentifierElements::accept(visitorParam);
    visitorParam->visit(std::static_pointer_cast<XsdAnnotation>(shared_from_this()));
}

std::list<std::shared_ptr<XsdAppInfo>>& XsdAnnotation::getAppInfoList(void)
{
    return m_appInfoList;
}

std::list<std::shared_ptr<XsdDocumentation>>& XsdAnnotation::getDocumentations(void)
{
    return m_documentations;
}

void XsdAnnotation::add(std::shared_ptr<XsdAnnotationChildren> element)
{
  if(std::dynamic_pointer_cast<XsdAppInfo>(element))
    m_appInfoList.push_back(std::static_pointer_cast<XsdAppInfo>(element));
  else if(std::dynamic_pointer_cast<XsdDocumentation>(element))
    m_documentations.push_back(std::static_pointer_cast<XsdDocumentation>(element));
}
