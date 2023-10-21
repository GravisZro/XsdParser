#pragma once

#include <xsdelements/XsdIdentifierElements.h>
#include <xsdelements/visitors/XsdAbstractElementVisitor.h>
#include <xsdelements/XsdAnnotation.h>

#include <map>
#include <functional>

class XsdAnnotation;

/**
 * Serves as a base to every {@link XsdAbstractElement} concrete type which can have xsd:annotation as children. Extends
 * from {@link XsdIdentifierElements} because every concrete type that can contain xsd:annotation has children can also
 * have an {@link XsdIdentifierElements#id} field.
 */
class XsdAnnotatedElements : public XsdIdentifierElements
{
public:
  using XsdIdentifierElements::clone;
  using XsdIdentifierElements::initialize;

private:
    /**
     * The {@link XsdAnnotation} that is annotating the concrete instances of this class.
     */
  std::shared_ptr<XsdAnnotation> m_annotation;

public: // ctors
  XsdAnnotatedElements(std::shared_ptr<XsdParserCore> parser,
                       StringMap elementFieldsMapParam,
                       VisitorFunctionReference visitorFunction,
                       std::shared_ptr<XsdAbstractElement> parent)
    : XsdIdentifierElements(parser, elementFieldsMapParam, visitorFunction, parent) {}

public:
  void setAnnotation(std::shared_ptr<XsdAnnotation> annotation){
        m_annotation = annotation;
    }

  std::shared_ptr<XsdAnnotation> getAnnotation(void) {
        return m_annotation;
    }
};
