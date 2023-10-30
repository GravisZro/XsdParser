#pragma once

#include <xsdelements/visitors/XsdAbstractElementVisitor.h>

#include <xsdelements/XsdAnnotatedElements.h>
#include <xsdelements/XsdSimpleType.h>

/**
 * A class representing the xsd:union element.
 *
 * @see <a href="https://www.w3schools.com/xml/el_union.asp">xsd:union description and usage at w3c</a>
 */
class XsdUnion : public XsdAnnotatedElements
{
public: // ctors
  XsdUnion(StringMap attributesMap,
           VisitorFunctionType visitorFunction,
           XsdAbstractElement* parent)
    : XsdAnnotatedElements(attributesMap, visitorFunction, parent)
  {
    if(haveAttribute(MEMBER_TYPES_TAG))
      m_memberTypes = getAttribute(MEMBER_TYPES_TAG);
  }

  XsdUnion(const XsdUnion& other, XsdAbstractElement* parent = nullptr);

public:

  void accept(XsdAbstractElementVisitor* visitorParam) override
  {
    XsdAnnotatedElements::accept(visitorParam);
    visitorParam->visit(static_cast<XsdUnion*>(this));
  }

  std::list<XsdSimpleType*> getUnionElements(void) const
  {
    return m_simpleTypeList;
  }

  std::list<std::string> getMemberTypesList(void);

  void add(XsdSimpleType* simpleType) {
    m_simpleTypeList.push_back(simpleType);
  }

private:
  /**
   * A List of {@link XsdSimpleType} instances that represent the {@link XsdUnion}.
   */
  std::list<XsdSimpleType*> m_simpleTypeList;

  /**
   * Specifies a list of built-in data types or {@link XsdSimpleType} instance names defined in a XsdSchema.
   */
  std::string m_memberTypes;
};
