#pragma once

#include <core/utils/ParseData.h>
#include <xsdelements/elementswrapper/NamedConcreteElement.h>
#include <xsdelements/elementswrapper/ReferenceBase.h>
#include <xsdelements/elementswrapper/UnsolvedReference.h>
#include <xsdelements/XsdAbstractElement.h>

#include <xsdelements/XsdNamedElements.h>

/**
 * A class is representing xsd:attributeGroup elements. It can have a ref attribute and therefore extends from
 * {@link XsdNamedElements}, which serves as a base to every element type that can have a ref attribute. For more
 * information check {@link XsdNamedElements}.
 *
 * @see <a href="https://www.w3schools.com/xml/el_attributegroup.asp">xsd:attributeGroup element description and usage at w3c</a>
 */
class XsdAttributeGroup : public XsdNamedElements
{
public:
  using XsdNamedElements::clone;
  constexpr static const std::string_view XSD_TAG = "xsd:attributeGroup";
  constexpr static const std::string_view XS_TAG = "xs:attributeGroup";
  constexpr static const std::string_view TAG = "attributeGroup";

private:
    /**
     * A list of {@link XsdAttributeGroup} children instances.
     */
    //This list is populated by the replaceUnsolvedElements and never directly (such as a Visitor method like all else).
    //The UnsolvedReference is placed in the XsdParser queue by the default implementation of the Visitor#visit(std::make_shared<XsdAttributeGroup> element)
    //The reference solving process then sends the XsdAttributeGroup to this class.
    std::list<std::shared_ptr<ReferenceBase>> m_attributeGroups;

    /**
     * A list of {@link XsdAttribute} children instances.
     */
    std::list<std::shared_ptr<ReferenceBase>> m_attributes;
public:
    XsdAttributeGroup(std::shared_ptr<XsdParserCore> parser, StringMap attributesMap, VisitorFunctionReference visitorFunction)
      : XsdNamedElements(parser, attributesMap, visitorFunction) { }

    XsdAttributeGroup(std::shared_ptr<XsdAbstractElement> parent, std::shared_ptr<XsdParserCore> parser, StringMap attributesMap, VisitorFunctionReference visitorFunction)
      : XsdNamedElements(parser, attributesMap, visitorFunction)
    {
        setParent(parent);
    }
public:
  void accept(std::shared_ptr<XsdAbstractElementVisitor> visitorParam)
    {
        XsdNamedElements::accept(visitorParam);
        visitorParam->visit(std::shared_ptr<XsdAttributeGroup>(this));
    }

  std::list<std::shared_ptr<ReferenceBase>> getElements(void);
  std::shared_ptr<XsdNamedElements> clone(StringMap placeHolderAttributes);
  void replaceUnsolvedElements(std::shared_ptr<NamedConcreteElement> element);
  std::list<std::shared_ptr<XsdAttributeGroup>> getXsdAttributeGroups(void);
  std::list<std::shared_ptr<XsdAttributeGroup>> getAllXsdAttributeGroups(void);
  std::list<std::shared_ptr<XsdAttribute>> getXsdAttributes(void);


  static std::shared_ptr<ReferenceBase> parse(ParseData parseData)
  {
        return xsdParseSkeleton(parseData.node, std::static_pointer_cast<XsdAbstractElement>(std::make_shared<XsdAttributeGroup>(parseData.parserInstance, XsdAbstractElement::getAttributesMap(parseData.node), parseData.visitorFunction)));
    }

  void addAttribute(std::shared_ptr<ReferenceBase> attribute)
  {
    m_attributes.push_back(attribute);
  }

  void addAttributeGroup(std::shared_ptr<ReferenceBase> attributeGroup) {
        m_attributeGroups.push_back(attributeGroup);
    }
};
