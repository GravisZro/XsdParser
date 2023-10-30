#pragma once

#include <core/utils/CommonTypes.h>
#include <core/utils/StringOperations.h>


#include <xsdelements/elementswrapper/ReferenceBase.h>
#include <xsdelements/enums/ComplexTypeBlockEnum.h>
#include <xsdelements/enums/FinalEnum.h>
#include <xsdelements/exceptions/ParsingException.h>
#include <xsdelements/visitors/XsdAbstractElementVisitor.h>

#include <xsdelements/XsdNamedElements.h>
#include <xsdelements/AttributeValidations.h>

class XsdComplexContent;
class XsdSimpleContent;
class XsdAttribute;
class XsdAttributeGroup;
class XsdGroup;
class XsdAll;
class XsdChoice;
class XsdSequence;
class XsdMultipleElements;
class NamedConcreteElement;

/**
 * A class representing the xsd:complexType element. Extends {@link XsdNamedElements} because it's one of the
 * {@link XsdAbstractElement} concrete classes that can have a name attribute.
 *
 * @see <a href="https://www.w3schools.com/xml/el_complextype.asp">xsd:complexType element description and usage at w3c</a>
 */
class XsdComplexType : public XsdNamedElements
{
public: // ctors
  XsdComplexType(StringMap attributesMap,
                 VisitorFunctionType visitorFunction,
                 XsdAbstractElement* parent)
    : XsdNamedElements(attributesMap, visitorFunction, parent),
      m_childElement(nullptr),
      m_elementAbstract(false),
      m_mixed(false),
      m_complexContent(nullptr),
      m_simpleContent(nullptr)
  {
    m_block = AttributeValidations::getBlockDefaultValue(getParent());
    m_elementFinal = AttributeValidations::getFinalDefaultValue(getParent());

    if(hasAttribute(ABSTRACT_TAG))
      m_elementAbstract = AttributeValidations::validateBoolean(getAttribute(ABSTRACT_TAG));

    if(hasAttribute(MIXED_TAG))
      m_mixed = AttributeValidations::validateBoolean(getAttribute(MIXED_TAG));

    if(hasAttribute(BLOCK_TAG))
      m_block = AttributeValidations::belongsToEnum<ComplexTypeBlockEnum>(getAttribute(BLOCK_TAG));

    if(hasAttribute(FINAL_TAG))
      m_elementFinal = AttributeValidations::belongsToEnum<FinalEnum>(getAttribute(FINAL_TAG));
  }

  XsdComplexType(const XsdComplexType& other, XsdAbstractElement* parent = nullptr);

  ~XsdComplexType(void);
public:
  /**
   * Runs verifications on each concrete element to ensure that the XSD schema rules are verified.
   */
  virtual void validateSchemaRules(void) const override
  {
    XsdNamedElements::validateSchemaRules();
    rule2();
  }

  void accept(XsdAbstractElementVisitor* visitorParam) override
  {
    XsdNamedElements::accept(visitorParam);
    visitorParam->visit(static_cast<XsdComplexType*>(this));
  }

  /**
    * @return The elements of his child as if they belong to the {@link XsdComplexType} instance.
    */
  virtual std::list<ReferenceBase*> getElements(void) const override
  {
    if(m_childElement != nullptr)
      return m_childElement->getElement()->getElements();
    return {};
  }

  virtual void replaceUnsolvedElements(NamedConcreteElement* elementWrapper) override;

  std::optional<std::string> getFinal(void) const;

  std::list<ReferenceBase*> getAttributes(void) const;
  std::list<XsdAttribute*> getXsdAttributes(void) const;
  std::list<XsdAttributeGroup*> getXsdAttributeGroup(void) const;
  std::list<XsdAttributeGroup*> getAllXsdAttributeGroups(void) const;
  std::list<XsdAttribute*> getAllXsdAttributes(void) const;

  XsdSimpleContent* getSimpleContent(void) const
  {
    return m_simpleContent;
  }

  XsdComplexContent* getComplexContent(void) const
  {
    return m_complexContent;
  }

  bool isMixed(void) const
  {
    return m_mixed;
  }

  bool isElementAbstract(void) const
  {
    return m_elementAbstract;
  }

  void setChildElement(ReferenceBase* childElement)
  {
    m_childElement = childElement;
  }

  void setComplexContent(XsdComplexContent* complexContent)
  {
    m_complexContent = complexContent;
  }

  void setSimpleContent(XsdSimpleContent* simpleContent)
  {
    m_simpleContent = simpleContent;
  }

  std::optional<std::string> getBlock(void) const
  {
    return m_block;
  }

  template<typename T, std::enable_if_t<std::is_same_v<XsdAbstractElement , T> ||
                                        std::is_same_v<XsdMultipleElements, T> ||
                                        std::is_same_v<XsdGroup           , T> ||
                                        std::is_same_v<XsdAll             , T> ||
                                        std::is_same_v<XsdChoice          , T> ||
                                        std::is_same_v<XsdSequence        , T> ||
                                        std::is_same_v<XsdElement         , T>, bool> = true>
  T* getChildAs(void) const
  {
    if (m_childElement != nullptr)
      return dynamic_cast<T*>(m_childElement->getElement());
    return nullptr;
  }

private:
  /**
   * Asserts if the current object has a simpleContent as children and contains a value for the mixed attribute, which isn't allowed throwing
   * an exception in that case.
   */
  void rule2(void) const
  {
    if (m_simpleContent != nullptr && hasAttribute(MIXED_TAG))
      throw ParsingException(TAG<XsdComplexType>::xsd + " element: The simpleContent element and the " + MIXED_TAG + " attribute are not allowed at the same time.");
  }

private:
  /**
   * The child element of {@link XsdComplexType}. Can be either a {@link XsdGroup} or a {@link XsdMultipleElements}
   * instance wrapped in a {@link ReferenceBase} object.
   */
  ReferenceBase* m_childElement;

  /**
   * Specifies whether the complex type can be used in an instance document. True indicates that an element cannot
   * use this complex type directly but must use a complex type derived from this complex type.
   */
  bool m_elementAbstract;

  /**
   * Specifies whether character data is allowed to appear between the child elements of this complexType element.
   * This attribute is exclusive with {@link XsdComplexType#simpleContent}, only one can be present at any given time.
   */
  bool m_mixed;

  /**
   * Prevents a complex type that has a specified type of derivation from being used in place of this complex type.
   * Possible values are extension, restriction or #all.
   */
  ComplexTypeBlockEnum m_block;

  /**
   * Prevents a specified type of derivation of this complex type element.
   * Possible values are extension, restriction or #all.
   */
  FinalEnum m_elementFinal;

  /**
   * A {@link XsdComplexContent} child.
   */
  XsdComplexContent* m_complexContent;

  /**
   * A {@link XsdSimpleContent} child. This element is exclusive with the {@link XsdComplexType#mixed} field, only one
   * of them should be present in any {@link XsdComplexType} element.
   */
  XsdSimpleContent* m_simpleContent;
};
