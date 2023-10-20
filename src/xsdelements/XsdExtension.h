#pragma once


#include <core/utils/CommonTypes.h>

#include <xsdelements/XsdAnnotatedElements.h>
#include <xsdelements/elementswrapper/ReferenceBase.h>

class XsdBuiltInDataType;

/**
 * A class representing the xsd:extension element.
 *
 * @see <a href="https://www.w3schools.com/xml/el_extension.asp">xsd:extension description and usage at w3c</a>
 */
class XsdExtension : public XsdAnnotatedElements
{
public:
  using XsdAnnotatedElements::clone;
    constexpr static const std::string_view XSD_TAG = "xsd:extension";
    constexpr static const std::string_view XS_TAG = "xs:extension";
    constexpr static const std::string_view TAG = "extension";

private:
    /**
     * The child element of the {@link XsdExtension} instance. Either a {@link XsdGroup}, {@link XsdAll},
     * {@link XsdSequence} or a {@link XsdChoice} instance wrapped in a {@link ReferenceBase} object.
     */
    std::shared_ptr<ReferenceBase> m_childElement;

    /**
     * A {@link XsdElement} instance wrapped in a {@link ReferenceBase} object from which this {@link XsdExtension}
     * instance extends.
     */
    std::shared_ptr<ReferenceBase> m_base;
public:
    XsdExtension(std::shared_ptr<XsdParserCore> parser, StringMap attributesMap, VisitorFunctionReference visitorFunction);

public:
  void replaceUnsolvedElements(std::shared_ptr<NamedConcreteElement> element);

  void accept(std::shared_ptr<XsdAbstractElementVisitor> visitorParam)
    {
        XsdAnnotatedElements::accept(visitorParam);
        visitorParam->visit(nondeleted_ptr<XsdExtension>(this));
    }

  std::shared_ptr<XsdExtension> clone(StringMap placeHolderAttributes);
  std::list<std::shared_ptr<ReferenceBase>> getElements(void);
  std::shared_ptr<XsdNamedElements> getBase(void);

  std::shared_ptr<XsdComplexType> getBaseAsComplexType(void);
  std::shared_ptr<XsdSimpleType> getBaseAsSimpleType(void);
  std::shared_ptr<XsdBuiltInDataType> getBaseAsBuiltInDataType(void);

  static std::shared_ptr<ReferenceBase> parse(ParseData parseData);

  std::list<std::shared_ptr<XsdAttribute>> getXsdAttributes(void);
  std::list<std::shared_ptr<XsdAttributeGroup>> getXsdAttributeGroup(void);
  std::shared_ptr<XsdAbstractElement> getXsdChildElement();

  void setChildElement(std::shared_ptr<ReferenceBase> childElement) {
        m_childElement = childElement;
    }

  std::shared_ptr<XsdGroup> getChildAsGroup(void);
  std::shared_ptr<XsdAll> getChildAsAll(void);
  std::shared_ptr<XsdChoice> getChildAsChoice(void);
  std::shared_ptr<XsdSequence> getChildAsSequence(void);
};
