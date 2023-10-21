#pragma once

#include <core/utils/ParseData.h>
#include <xsdelements/elementswrapper/ConcreteElement.h>
#include <xsdelements/elementswrapper/NamedConcreteElement.h>
#include <xsdelements/elementswrapper/ReferenceBase.h>
#include <xsdelements/elementswrapper/UnsolvedReference.h>
#include <xsdelements/enums/BlockEnum.h>
#include <xsdelements/enums/FinalEnum.h>
#include <xsdelements/enums/FormEnum.h>
#include <xsdelements/visitors/XsdAbstractElementVisitor.h>

#include <xsdelements/XsdNamedElements.h>
#include <xsdelements/XsdBuiltInDataType.h>
#include <xsdelements/AttributeValidations.h>


/**
 * A class representing the xsd:element element. Extends {@link XsdNamedElements} because it's one of the
 * {@link XsdAbstractElement} concrete classes that can have a {@link XsdNamedElements#name} attribute.
 *
 * @see <a href="https://www.w3schools.com/xml/el_element.asp">xsd:element description and usage at w3c</a>
 */
class XsdElement : public XsdNamedElements
{
public:
  using XsdNamedElements::clone;
  constexpr static const std::string_view XSD_TAG = "xsd:element";
  constexpr static const std::string_view XS_TAG = "xs:element";
  constexpr static const std::string_view TAG = "element";

private:
    /**
     * The {@link XsdComplexType} instance wrapped in a {@link ReferenceBase} object.
     */
    std::shared_ptr<ReferenceBase> m_complexType;

    /**
     * The {@link XsdSimpleType} instance wrapped in a {@link ReferenceBase} object.
     */
    std::shared_ptr<ReferenceBase> m_simpleType;

    /**
     * The type of the current element.
     * Either specified a built in data type or is a reference to a existent {@link XsdComplexType} or a
     * {@link XsdSimpleType} instances.
     */
    std::shared_ptr<ReferenceBase> m_type;

    /**
     * Specifies the name of an element that can be substituted with this element. Only should be present if this
     * {@link XsdElement} is a top level element, i.e. his parent is a XsdSchema element.
     */
    std::shared_ptr<ReferenceBase> m_substitutionGroup;

    /**
     * Specifies a default value for the element. It's only available if the type contents are text only type defined by
     * a simpleType.
     */
    std::optional<std::string> m_defaultObj;

    /**
     * Specifies a fixed value for the element. It's only available if the type contents are text only type defined by
     * a simpleType.
     */
    std::optional<std::string> m_fixed;

    /**
     * Specifies if the current {@link XsdElement} attribute is "qualified" or "unqualified".
     */
    FormEnum m_form;

    /**
     * Specifies if the this {@link XsdElement} support a null value.
     */
    bool m_nillable;

    /**
     * Specifies whether the element can be used in an instance document.
     */
    bool m_abstractObj;

    /**
     * Prevents an element with a specified type of derivation from being used in place of this {@link XsdElement} element.
     * Possible values are:
        * extension - prevents elements derived by extension;
        * restriction - prevents elements derived by restriction;
        * substitution - prevents elements derived by substitution;
        * #all - all of the above.
     */
    BlockEnum m_block;

    /**
     * Prevents other elements to derive depending on its value. This attribute cannot be present unless this
     * {@link XsdElement} is a top level element, i.e. his parent is a XsdSchema element.
         * extension - prevents elements derived by extension;
         * restriction - prevents elements derived by restriction;
         * #all - all of the above.
     */
    FinalEnum m_finalObj;

    /**
     * Specifies the minimum number of times this element can occur in the parent element. The value can be any
     * number bigger or equal to 0. Default value is 1. This attribute cannot be used if the parent element is the
     * XsdSchema element.
     */
    int m_minOccurs;

    /**
     * Specifies the maximum number of times this element can occur in the parent element. The value can be any
     * number bigger or equal to 0, or if you want to set no limit on the maximum number, use the value "unbounded".
     * Default value is 1. This attribute cannot be used if the parent element is the XsdSchema element.
     */
    std::string m_maxOccurs;

public: // ctors
  XsdElement(std::shared_ptr<XsdParserCore> parser,
             StringMap attributesMap,
             VisitorFunctionReference visitorFunction,
             std::shared_ptr<XsdAbstractElement> parent);
  virtual void initialize(void) override;
private:
    /**
     * Runs verifications on each concrete element to ensure that the XSD schema rules are verified.
     */
  virtual void validateSchemaRules(void) override
    {
        XsdNamedElements::validateSchemaRules();
        rule2();
        rule3();
        rule4();
        rule5();
        rule6();
        rule7();
    }

private:
    void rule7(void);
    void rule6(void);
    void rule5(void);
    void rule4(void);
    void rule3(void);
    void rule2(void);
public:
  void accept(std::shared_ptr<XsdAbstractElementVisitor> visitorParam)
    {
        XsdNamedElements::accept(visitorParam);
        visitorParam->visit(std::static_pointer_cast<XsdElement>(shared_from_this()));
    }

  std::shared_ptr<XsdElement> clone(StringMap placeHolderAttributes);
  void replaceUnsolvedElements(std::shared_ptr<NamedConcreteElement> element);

  std::shared_ptr<XsdComplexType> getXsdComplexType(void);
  std::shared_ptr<XsdSimpleType> getXsdSimpleType(void);

private:
  std::shared_ptr<XsdComplexType> getXsdComplexTypeFromType(void);
  std::shared_ptr<XsdSimpleType> getXsdSimpleTypeFromType(void);
public:
  std::shared_ptr<XsdNamedElements> getTypeAsXsd(void);
  std::shared_ptr<XsdComplexType> getTypeAsComplexType(void);
  std::shared_ptr<XsdSimpleType> getTypeAsSimpleType(void);
  std::shared_ptr<XsdBuiltInDataType> getTypeAsBuiltInDataType(void);

  static std::shared_ptr<ReferenceBase> parse(ParseData parseData)
  {
    return xsdParseSkeleton(parseData.node,
                            std::static_pointer_cast<XsdAbstractElement>(
                              create<XsdElement>(parseData.parserInstance,
                                                 getAttributesMap(parseData.node),
                                                 parseData.visitorFunction,
                                                 nullptr)));
  }

  std::optional<std::string> getFinal(void)
  {
    return m_finalObj.getValue();
  }

  bool isNillable(void) {
    return m_nillable;
  }

  int getMinOccurs(void) {
    return m_minOccurs;
  }

  std::string getMaxOccurs(void) {
    return m_maxOccurs;
  }

  bool isAbstractObj(void) {
    return m_abstractObj;
  }

  void setComplexType(std::shared_ptr<ReferenceBase> complexType) {
    m_complexType = complexType;
  }

  void setSimpleType(std::shared_ptr<ReferenceBase> simpleType) {
    m_simpleType = simpleType;
  }

  std::optional<std::string> getBlock(void) {
    return m_block.getValue();
  }

  std::optional<std::string> getForm(void) {
    return m_form.getValue();
  }

  std::optional<std::string> getType(void);

  std::shared_ptr<ReferenceBase> getSubstitutionGroup(void)
  {
    return m_substitutionGroup;
  }

  std::shared_ptr<XsdElement> getXsdSubstitutionGroup(void);
};
