#include "XsdAnnotation.h"

#include <xsdelements/XsdDocumentation.h>
#include <xsdelements/XsdAppInfo.h>

void XsdAnnotation::accept(XsdAbstractElementVisitor* visitorParam)
{
  XsdIdentifierElements::accept(visitorParam);
  visitorParam->visit(static_cast<XsdAnnotation*>(this));
}

void XsdAnnotation::add(XsdAnnotationChildren* element)
{
  if(dynamic_cast<XsdAppInfo*>(element) != nullptr)
    m_appInfoList.push_back(static_cast<XsdAppInfo*>(element));
  else if(dynamic_cast<XsdDocumentation*>(element) != nullptr)
    m_documentations.push_back(static_cast<XsdDocumentation*>(element));
}
