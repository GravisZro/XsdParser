#pragma once


#include <xsdelements/elementswrapper/ReferenceBase.h>
#include <xsdelements/elementswrapper/UnsolvedReference.h>
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
public:
  using XsdAnnotatedElements::clone;
private:
    /**
     * A List of {@link XsdSimpleType} instances that represent the {@link XsdUnion}.
     */
    std::list<std::shared_ptr<XsdSimpleType>> m_simpleTypeList;

    /**
     * Specifies a list of built-in data types or {@link XsdSimpleType} instance names defined in a XsdSchema.
     */
    std::string m_memberTypes;
public: // ctors
  XsdUnion(std::shared_ptr<XsdParserCore> parser,
           StringMap attributesMap,
           VisitorFunctionType visitorFunction,
           std::shared_ptr<XsdAbstractElement> parent)
    : XsdAnnotatedElements(parser, attributesMap, visitorFunction, parent) { }

public:
  virtual void initialize(void) override
  {
    XsdAnnotatedElements::initialize();
    m_simpleTypeList.clear();
    m_memberTypes.clear();

    if(haveAttribute(MEMBER_TYPES_TAG))
      m_memberTypes = getAttribute(MEMBER_TYPES_TAG);
  }

  void accept(std::shared_ptr<XsdAbstractElementVisitor> visitorParam) override
    {
        XsdAnnotatedElements::accept(visitorParam);
        visitorParam->visit(std::static_pointer_cast<XsdUnion>(shared_from_this()));
    }

  std::shared_ptr<XsdUnion> clone(StringMap placeHolderAttributes);

  std::list<std::shared_ptr<XsdSimpleType>> getUnionElements(){
        return m_simpleTypeList;
    }

  std::list<std::string> getMemberTypesList(void);

  void add(std::shared_ptr<XsdSimpleType> simpleType) {
        m_simpleTypeList.push_back(simpleType);
    }
};
