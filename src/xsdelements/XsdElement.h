#pragma once

#include <xsdelements/elementswrapper/ConcreteElement.h>
#include <xsdelements/elementswrapper/ReferenceBase.h>
#include <xsdelements/enums/BlockEnum.h>
#include <xsdelements/enums/FinalEnum.h>
#include <xsdelements/enums/FormEnum.h>
#include <xsdelements/visitors/XsdAbstractElementVisitor.h>

#include <xsdelements/XsdNamedElements.h>
#include <xsdelements/XsdBuiltInDataType.h>

class XsdComplexType;
class XsdSimpleType;
class NamedConcreteElement;

/**
 * A class representing the xsd:element element. Extends {@link XsdNamedElements} because it's one of the
 * {@link XsdAbstractElement} concrete classes that can have a {@link XsdNamedElements#name} attribute.
 *
 * @see <a href="https://www.w3schools.com/xml/el_element.asp">xsd:element description and usage at w3c</a>
 */
class XsdElement : public XsdNamedElements
{
public: // ctors
  XsdElement(StringMap attributesMap,
             VisitorFunctionType visitorFunction,
             XsdAbstractElement* parent);

  XsdElement(const XsdElement& other);
  ~XsdElement(void);
public:
  /**
     * Runs verifications on each concrete element to ensure that the XSD schema rules are verified.
     */
  virtual void validateSchemaRules(void) const override
  {
    XsdNamedElements::validateSchemaRules();
    rule2();
    rule3();
    rule4();
    rule5();
    rule6();
    rule7();
  }

public:
  void accept(XsdAbstractElementVisitor* visitorParam) override
  {
    XsdNamedElements::accept(visitorParam);
    visitorParam->visit(static_cast<XsdElement*>(this));
  }

  virtual void replaceUnsolvedElements(NamedConcreteElement* elementWrapper) override;

  XsdComplexType* getXsdComplexType(void) const;
  XsdSimpleType* getXsdSimpleType(void) const;

  XsdNamedElements* getTypeAsXsd(void) const;
  XsdComplexType* getTypeAsComplexType(void) const;
  XsdSimpleType* getTypeAsSimpleType(void) const;
  XsdBuiltInDataType* getTypeAsBuiltInDataType(void) const;

  std::optional<std::string> getFinal(void) const
  {
    return m_finalObj;
  }

  bool isNillable(void) const
  {
    return m_nillable;
  }

  int getMinOccurs(void) const
  {
    return m_minOccurs;
  }

  std::string getMaxOccurs(void) const
  {
    return m_maxOccurs;
  }

  bool isAbstractObj(void) const
  {
    return m_abstractObj;
  }

  void setComplexType(ReferenceBase* complexType)
  {
    m_complexType = complexType;
  }

  void setSimpleType(ReferenceBase* simpleType)
  {
    m_simpleType = simpleType;
  }

  std::optional<std::string> getBlock(void) const
  {
    return m_block;
  }

  std::optional<std::string> getForm(void) const
  {
    return m_form;
  }

  std::optional<std::string> getType(void) const;

  ReferenceBase* getSubstitutionGroup(void) const
  {
    return m_substitutionGroup;
  }

  XsdElement* getXsdSubstitutionGroup(void) const;  


private:
  XsdComplexType* getXsdComplexTypeFromType(void) const;
  XsdSimpleType* getXsdSimpleTypeFromType(void) const;

  void rule7(void) const;
  void rule6(void) const;
  void rule5(void) const;
  void rule4(void) const;
  void rule3(void) const;
  void rule2(void) const;

private:
  /**
   * The {@link XsdComplexType} instance wrapped in a {@link ReferenceBase} object.
   */
  ReferenceBase* m_complexType;

  /**
   * The {@link XsdSimpleType} instance wrapped in a {@link ReferenceBase} object.
   */
  ReferenceBase* m_simpleType;

  /**
   * The type of the current element.
   * Either specified a built in data type or is a reference to a existent {@link XsdComplexType} or a
   * {@link XsdSimpleType} instances.
   */
  ReferenceBase* m_type;

  /**
   * Specifies the name of an element that can be substituted with this element. Only should be present if this
   * {@link XsdElement} is a top level element, i.e. his parent is a XsdSchema element.
   */
  ReferenceBase* m_substitutionGroup;

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
};
