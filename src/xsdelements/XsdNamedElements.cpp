#include "XsdNamedElements.h"

#include <xsdelements/exceptions/ParsingException.h>
#include <xsdelements/visitors/XsdAbstractElementVisitor.h>

XsdNamedElements::XsdNamedElements(std::shared_ptr<XsdParserCore> parser,
                                   StringMap attributesMap,
                                   VisitorFunctionReference visitorFunction,
                                   std::shared_ptr<XsdAbstractElement> parent)
  : XsdAnnotatedElements(parser, attributesMap, visitorFunction, parent)
{
  if(haveAttribute(XsdAbstractElement::NAME_TAG))
    m_name = getAttribute(XsdAbstractElement::NAME_TAG);
}
