#pragma once

#include <xsdelements/XsdIdentifierElements.h>
#include <xsdelements/XsdAnnotation.h>

/**
 * Serves as a base to every {@link XsdAbstractElement} concrete type which can have xsd:annotation as children. Extends
 * from {@link XsdIdentifierElements} because every concrete type that can contain xsd:annotation has children can also
 * have an {@link XsdIdentifierElements#id} field.
 */
class XsdAnnotatedElements : public XsdIdentifierElements
{
public:
  using XsdIdentifierElements::clone;
  
private:
    /**
     * The {@link XsdAnnotation} that is annotating the concrete instances of this class.
     */
  std::shared_ptr<XsdAnnotation> m_annotation;

public: // ctors
  XsdAnnotatedElements(std::shared_ptr<XsdParserCore> parser,
                       StringMap attributesMap,
                       VisitorFunctionType visitorFunction,
                       std::shared_ptr<XsdAbstractElement> parent)
    : XsdIdentifierElements(parser, attributesMap, visitorFunction, parent) { }

public:
  virtual void initialize(void) override
  {
    XsdIdentifierElements::initialize();
    m_annotation.reset();
  }

  void setAnnotation(std::shared_ptr<XsdAnnotation> annotation){
        m_annotation = annotation;
    }

  std::shared_ptr<XsdAnnotation> getAnnotation(void) {
        return m_annotation;
    }
};
