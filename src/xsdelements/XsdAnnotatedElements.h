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
public: // ctors
  XsdAnnotatedElements(StringMap attributesMap,
                       VisitorFunctionType visitorFunction,
                       XsdAbstractElement* parent)
    : XsdIdentifierElements(attributesMap, visitorFunction, parent),
      m_annotation(nullptr)
  {
  }

public:

  void setAnnotation(XsdAnnotation* annotation)
  {
    m_annotation = annotation;
  }

  XsdAnnotation* getAnnotation(void) const
  {
    return m_annotation;
  }

private:
    /**
     * The {@link XsdAnnotation} that is annotating the concrete instances of this class.
     */
  XsdAnnotation* m_annotation;
};
