#include "XsdNamedElements.h"

#include <xsdelements/exceptions/ParsingException.h>
#include <xsdelements/visitors/XsdAbstractElementVisitor.h>

XsdNamedElements::XsdNamedElements(std::shared_ptr<XsdParserCore> parser,
                 StringMap attributesMap,
                 VisitorFunctionReference visitorFunction)
  : XsdAnnotatedElements(parser, attributesMap, visitorFunction)
{
  if(attributesMap.contains(*XsdAbstractElement::NAME_TAG))
    m_name = attributesMap.at(*XsdAbstractElement::NAME_TAG);
}
