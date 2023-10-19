#pragma once

//#include <core/XsdParserCore.h>
#include <core/utils/ParseData.h>
#include <xsdelements/elementswrapper/ReferenceBase.h>
#include <xsdelements/elementswrapper/UnsolvedReference.h>
#include <xsdelements/visitors/XsdAbstractElementVisitor.h>

#include <xsdelements/XsdAnnotatedElements.h>

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
public:
    XsdUnion(std::shared_ptr<XsdParserCore> parser, StringMap attributesMap, VisitorFunctionReference visitorFunction)
      : XsdAnnotatedElements(parser, attributesMap, visitorFunction)
    {
      if(attributesMap.contains(*MEMBER_TYPES_TAG))
        m_memberTypes = attributesMap.at(*MEMBER_TYPES_TAG);
    }
public:
  void accept(std::shared_ptr<XsdAbstractElementVisitor> visitorParam)
    {
        XsdAnnotatedElements::accept(visitorParam);
        visitorParam->visit(std::shared_ptr<XsdUnion>(this));
    }

    /**
     * Performs a copy of the current object for replacing purposes. The cloned objects are used to replace
     * {@link UnsolvedReference} objects in the reference solving process.
     * @param placeHolderAttributes The additional attributes to add to the clone.
     * @return A copy of the object from which is called upon.
     */
  std::shared_ptr<XsdUnion> clone(StringMap placeHolderAttributes)
    {
        placeHolderAttributes.merge(m_attributesMap);

        auto elementCopy = std::make_shared<XsdUnion>(m_parser, placeHolderAttributes, m_visitorFunction);

        if (m_simpleTypeList.empty()){
          // TODO
            //elementCopy->m_simpleTypeList = m_simpleTypeList.stream().map(simpleType -> (XsdSimpleType) simpleType->clone(simpleType->getAttributesMap(), elementCopy));
        }

        elementCopy->m_parent = nullptr;

        return elementCopy;
    }

  std::list<std::shared_ptr<XsdSimpleType>> getUnionElements(){
        return m_simpleTypeList;
    }

  std::list<std::string> getMemberTypesList(void)
  {
    return {}; // TODO
    //return Arrays.asList(memberTypes.split(" "));
  }

  static std::shared_ptr<ReferenceBase> parse(ParseData parseData)
  {
    return xsdParseSkeleton(parseData.node, std::static_pointer_cast<XsdAbstractElement>(std::make_shared<XsdUnion>(parseData.parserInstance, XsdAbstractElement::getAttributesMap(parseData.node), parseData.visitorFunction)));
  }

  void add(std::shared_ptr<XsdSimpleType> simpleType) {
        m_simpleTypeList.push_back(simpleType);
    }
};
