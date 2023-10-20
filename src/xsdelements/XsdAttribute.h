#pragma once



/*
#include <xsdelements/elementswrapper/ConcreteElement.h>
#include <xsdelements/elementswrapper/NamedConcreteElement.h>
#include <xsdelements/elementswrapper/UnsolvedReference.h>
#include <xsdelements/exceptions/ParsingException.h>
#include <xsdelements/visitors/XsdAbstractElementVisitor.h>
#include <xsdelements/visitors/XsdSimpleTypeVisitor.h>
*/

#include <xsdelements/enums/FormEnum.h>
#include <xsdelements/enums/UsageEnum.h>
#include <xsdelements/XsdNamedElements.h>
#include <xsdelements/elementswrapper/ReferenceBase.h>
#include <xsdelements/elementswrapper/NamedConcreteElement.h>

#include <xsdelements/XsdSimpleType.h>

#include <list>
#include <map>
#include <functional>
#include <string_view>
#include <string>

/**
 * A class representing the xsd:attribute element. It can have a ref attribute and therefore extends from
 * {@link XsdNamedElements}, which serves as a base to every element type that can have a ref attribute.
 * For more information check {@link XsdNamedElements}.
 *
 * @see <a href="https://www.w3schools.com/xml/el_attribute.asp">xsd:attribute element description and usage at w3c</a>
 */
class XsdAttribute : public XsdNamedElements
{
public:
  using XsdNamedElements::clone;
  constexpr static const std::string_view XSD_TAG = "xsd:attribute";
  constexpr static const std::string_view XS_TAG = "xs:attribute";
  constexpr static const std::string_view TAG = "attribute";

private:
    /**
     * A {@link XsdSimpleType} instance wrapped in a {@link ReferenceBase} object which indicate any restrictions
     * that may be present in the current {@link XsdAttribute} instance.
     */
    std::shared_ptr<ReferenceBase> m_simpleType;

    /**
     * A default value for the current {@link XsdAttribute} instance. This value and {@link XsdAttribute#fixed}
     * shouldn't be present at the same time.
     */
    std::optional<std::string> m_defaultElement;

    /**
     * Specifies a fixed value for the current {@link XsdAttribute} instance. This value and
     * {@link XsdAttribute#defaultElement} shouldn't be present at the same time.
     */
    std::optional<std::string> m_fixed;

    /**
     * Specifies either a built-in data type for the current {@link XsdAttribute} instance or serves as a reference to a
     * {@link XsdSimpleType} instance. In the case of being used as a reference to a {@link XsdSimpleType} instance
     * its value is used to create an {@link UnsolvedReference} using its value as ref to be resolved later in the
     * parsing process.
     */
    std::optional<std::string> m_type;

    /**
     * Specifies if the current {@link XsdAttribute} attribute is "qualified" or "unqualified".
     */
    FormEnum m_form;

    /**
     * Specifies how this {@link XsdAttribute} should be used. The possible values are: required, prohibited, optional.
     */
    UsageEnum m_use;
public:
    XsdAttribute(std::shared_ptr<XsdParserCore> parser,
                 StringMap attributesMap,
                 VisitorFunctionReference visitorFunction);

    XsdAttribute(std::shared_ptr<XsdAbstractElement> parent,
                 std::shared_ptr<XsdParserCore> parser,
                 StringMap attributesMap,
                 VisitorFunctionReference visitorFunction)
      : XsdAttribute(parser, attributesMap, visitorFunction)
    {
        setParent(parent);
    }

public:
    /**
     * Runs verifications on each concrete element to ensure that the XSD schema rules are verified.
     */
  void validateSchemaRules(void)
    {
        XsdNamedElements::validateSchemaRules();
        rule2();
        rule3();
    }
private:
  static std::optional<std::string> getFormDefaultValue(std::shared_ptr<XsdAbstractElement> parent);
    /**
     * Asserts if the current object has a ref attribute at the same time as either a simpleType as children, a form attribute or a type attribute.
     * Throws an exception in that case.
     */
    void rule3(void)
    {
        if (m_attributesMap.contains(*REF_TAG) && (m_simpleType || m_form || m_type)){
            throw ParsingException(XSD_TAG + " element: If " + REF_TAG + " attribute is present, simpleType element, form attribute and type attribute cannot be present at the same time.");
        }
    }

    /**
     * Asserts if the current object has the fixed and default attributes at the same time, which isn't allowed, throwing
     * an exception in that case.
     */
    void rule2(void)
    {
        if (m_fixed && m_defaultElement){
            throw ParsingException(XSD_TAG + " element: " + FIXED_TAG + " and " + DEFAULT_ELEMENT_TAG + " attributes are not allowed at the same time.");
        }
    }
public:
  void accept(std::shared_ptr<XsdAbstractElementVisitor> visitorParam);
  std::shared_ptr<XsdAttribute> clone(StringMap placeHolderAttributes);
  void replaceUnsolvedElements(std::shared_ptr<NamedConcreteElement> elementWrapper);

  void setSimpleType(std::shared_ptr<ReferenceBase> simpleType) {
        m_simpleType = simpleType;
    }

  std::shared_ptr<XsdSimpleType> getXsdSimpleType(void);

  std::optional<std::string> getType(void) {
        return m_type;
    }

  std::optional<std::string> getUse(void) {
        return m_use.getValue();
    }

  std::optional<std::string> getForm(void) {
        return m_form.getValue();
    }

  std::optional<std::string> getFixed(void) {
        return m_fixed;
    }

  std::list<std::shared_ptr<XsdRestriction>> getAllRestrictions(void);

  static std::shared_ptr<ReferenceBase> parse(ParseData parseData);
};
