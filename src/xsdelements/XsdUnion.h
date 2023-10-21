#pragma once

#include <core/utils/ParseData.h>
#include <xsdelements/elementswrapper/ReferenceBase.h>
#include <xsdelements/elementswrapper/UnsolvedReference.h>
#include <xsdelements/visitors/XsdAbstractElementVisitor.h>

#include <xsdelements/XsdAnnotatedElements.h>
#include <xsdelements/XsdSimpleType.h>

#include <list>
#include <map>
#include <functional>

/**
 * A class representing the xsd:union element.
 *
 * @see <a href="https://www.w3schools.com/xml/el_union.asp">xsd:union description and usage at w3c</a>
 */
class XsdUnion : public XsdAnnotatedElements
{
public:
  using XsdAnnotatedElements::clone;
    constexpr static const std::string_view XSD_TAG = "xsd:union";
    constexpr static const std::string_view XS_TAG = "xs:union";
    constexpr static const std::string_view TAG = "union";

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
             VisitorFunctionReference visitorFunction,
             std::shared_ptr<XsdAbstractElement> parent)
      : XsdAnnotatedElements(parser, attributesMap, visitorFunction, parent)
    {
      if(haveAttribute(MEMBER_TYPES_TAG))
        m_memberTypes = getAttribute(MEMBER_TYPES_TAG);
    }
public:
  void accept(std::shared_ptr<XsdAbstractElementVisitor> visitorParam)
    {
        XsdAnnotatedElements::accept(visitorParam);
        visitorParam->visit(std::static_pointer_cast<XsdUnion>(shared_from_this()));
    }

  std::shared_ptr<XsdUnion> clone(StringMap placeHolderAttributes);

  std::list<std::shared_ptr<XsdSimpleType>> getUnionElements(){
        return m_simpleTypeList;
    }

  std::list<std::string> getMemberTypesList(void);

  static std::shared_ptr<ReferenceBase> parse(ParseData parseData)
  {
    return xsdParseSkeleton(parseData.node,
                            std::static_pointer_cast<XsdAbstractElement>(
                              create<XsdUnion>(parseData.parserInstance,
                                               getAttributesMap(parseData.node),
                                               parseData.visitorFunction,
                                               nullptr)));
  }

  void add(std::shared_ptr<XsdSimpleType> simpleType) {
        m_simpleTypeList.push_back(simpleType);
    }
};
