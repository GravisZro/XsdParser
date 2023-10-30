#pragma once

#include <xsdelements/enums/FormEnum.h>
#include <xsdelements/enums/UsageEnum.h>
#include <xsdelements/XsdNamedElements.h>
#include <xsdelements/elementswrapper/ReferenceBase.h>

#include <xsdelements/XsdSimpleType.h>

class NamedConcreteElement;

/**
 * A class representing the xsd:attribute element. It can have a ref attribute and therefore extends from
 * {@link XsdNamedElements}, which serves as a base to every element type that can have a ref attribute.
 * For more information check {@link XsdNamedElements}.
 *
 * @see <a href="https://www.w3schools.com/xml/el_attribute.asp">xsd:attribute element description and usage at w3c</a>
 */
class XsdAttribute : public XsdNamedElements
{
public: // ctors
  XsdAttribute(StringMap attributesMap,
               VisitorFunctionType visitorFunction,
               XsdAbstractElement* parent);

  XsdAttribute(const XsdAttribute& other);

  ~XsdAttribute(void);
public:
  /**
     * Runs verifications on each concrete element to ensure that the XSD schema rules are verified.
     */
  virtual void validateSchemaRules(void) const override
  {
    XsdNamedElements::validateSchemaRules();
    rule2();
    rule3();
  }

  void accept(XsdAbstractElementVisitor* visitorParam) override;
  virtual void replaceUnsolvedElements(NamedConcreteElement* elementWrapper) override;

  void setSimpleType(ReferenceBase* simpleType)
  {
    m_simpleType = simpleType;
  }

  XsdSimpleType* getXsdSimpleType(void) const;

  std::optional<std::string> getType(void) const
  {
    return m_type;
  }

  std::optional<std::string> getUse(void) const
  {
    return m_use;
  }

  std::optional<std::string> getForm(void) const
  {
    return m_form;
  }

  std::optional<std::string> getFixed(void) const
  {
    return m_fixed;
  }

  std::list<XsdRestriction*> getAllRestrictions(void) const;


private:
  static std::optional<std::string> getFormDefaultValue(XsdAbstractElement* parent);
  /**
     * Asserts if the current object has a ref attribute at the same time as either a simpleType as children, a form attribute or a type attribute.
     * Throws an exception in that case.
     */
  void rule3(void) const
  {
    if (hasAttribute(REF_TAG) && (m_simpleType != nullptr || m_form || m_type))
      throw ParsingException(TAG<XsdAttribute>::xsd + " element: If " + REF_TAG + " attribute is present, simpleType element, form attribute and type attribute cannot be present at the same time.");
  }

  /**
     * Asserts if the current object has the fixed and default attributes at the same time, which isn't allowed, throwing
     * an exception in that case.
     */
  void rule2(void) const
  {
    if (m_fixed && m_defaultElement)
      throw ParsingException(TAG<XsdAttribute>::xsd  + " element: " + FIXED_TAG + " and " + DEFAULT_ELEMENT_TAG + " attributes are not allowed at the same time.");
  }

private:
  /**
   * A {@link XsdSimpleType} instance wrapped in a {@link ReferenceBase} object which indicate any restrictions
   * that may be present in the current {@link XsdAttribute} instance.
   */
  ReferenceBase* m_simpleType;

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
};
