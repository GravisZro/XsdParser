#pragma once

#include <core/utils/CommonTypes.h>
#include <core/utils/StringOperations.h>


#include <xsdelements/elementswrapper/NamedConcreteElement.h>
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

/**
 * A class representing the xsd:complexType element. Extends {@link XsdNamedElements} because it's one of the
 * {@link XsdAbstractElement} concrete classes that can have a name attribute.
 *
 * @see <a href="https://www.w3schools.com/xml/el_complextype.asp">xsd:complexType element description and usage at w3c</a>
 */
class XsdComplexType : public XsdNamedElements
{
public:
  using XsdNamedElements::clone;

private:
    /**
     * The child element of {@link XsdComplexType}. Can be either a {@link XsdGroup} or a {@link XsdMultipleElements}
     * instance wrapped in a {@link ReferenceBase} object.
     */
    std::shared_ptr<ReferenceBase> m_childElement;

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
    std::shared_ptr<XsdComplexContent> m_complexContent;

    /**
     * A {@link XsdSimpleContent} child. This element is exclusive with the {@link XsdComplexType#mixed} field, only one
     * of them should be present in any {@link XsdComplexType} element.
     */
    std::shared_ptr<XsdSimpleContent> m_simpleContent;

public: // ctors
  XsdComplexType(std::shared_ptr<XsdParserCore> parser,
                 StringMap attributesMap,
                 VisitorFunctionType visitorFunction,
                 std::shared_ptr<XsdAbstractElement> parent)
    : XsdNamedElements(parser, attributesMap, visitorFunction, parent),
      m_elementAbstract(false),
      m_mixed(false)
  {
  }

public:
  virtual void initialize(void) override
  {
    XsdNamedElements::initialize();
    m_childElement.reset();
    m_elementAbstract = false;
    m_mixed = false;
    m_block.reset();
    m_elementFinal.reset();
    m_complexContent.reset();
    m_simpleContent.reset();

    m_block = AttributeValidations::getBlockDefaultValue(getParent());
    m_elementFinal = AttributeValidations::getFinalDefaultValue(getParent());

    if(haveAttribute(ABSTRACT_TAG))
      m_elementAbstract = AttributeValidations::validateBoolean(getAttribute(ABSTRACT_TAG));

    if(haveAttribute(MIXED_TAG))
      m_mixed = AttributeValidations::validateBoolean(getAttribute(MIXED_TAG));

    if(haveAttribute(BLOCK_TAG))
      m_block = AttributeValidations::belongsToEnum<ComplexTypeBlockEnum>(getAttribute(BLOCK_TAG));

    if(haveAttribute(FINAL_TAG))
      m_elementFinal = AttributeValidations::belongsToEnum<FinalEnum>(getAttribute(FINAL_TAG));
  }

    /**
     * Runs verifications on each concrete element to ensure that the XSD schema rules are verified.
     */
  virtual void validateSchemaRules(void) override
    {
        XsdNamedElements::validateSchemaRules();
        rule2();
    }

private:
    /**
     * Asserts if the current object has a simpleContent as children and contains a value for the mixed attribute, which isn't allowed throwing
     * an exception in that case.
     */
  void rule2(void)
  {
        if (m_simpleContent && haveAttribute(MIXED_TAG)){
            throw ParsingException(TAG<XsdComplexType>::xsd + " element: The simpleContent element and the " + MIXED_TAG + " attribute are not allowed at the same time.");
        }
    }

public:
  void accept(std::shared_ptr<XsdAbstractElementVisitor> visitorParam) override
    {
        XsdNamedElements::accept(visitorParam);
        visitorParam->visit(std::static_pointer_cast<XsdComplexType>(shared_from_this()));
    }

    /**
     * @return The elements of his child as if they belong to the {@link XsdComplexType} instance.
     */
  virtual std::list<std::shared_ptr<ReferenceBase>> getElements(void) override
  {
    if(m_childElement)
      return m_childElement->getElement()->getElements();
    return {};
  }

  std::shared_ptr<XsdComplexType> clone(StringMap placeHolderAttributes);
  void replaceUnsolvedElements(std::shared_ptr<NamedConcreteElement> element);
  std::shared_ptr<XsdAbstractElement> getXsdChildElement(void);

  std::optional<std::string> getFinal(void);

  std::list<std::shared_ptr<ReferenceBase>> getAttributes(void);
  std::list<std::shared_ptr<XsdAttribute>> getXsdAttributes(void);
  std::list<std::shared_ptr<XsdAttributeGroup>> getXsdAttributeGroup(void);
  std::list<std::shared_ptr<XsdAttributeGroup>> getAllXsdAttributeGroups(void);
  std::list<std::shared_ptr<XsdAttribute>> getAllXsdAttributes(void);

  std::shared_ptr<XsdSimpleContent> getSimpleContent(void) {
        return m_simpleContent;
    }

  std::shared_ptr<XsdComplexContent> getComplexContent(void) {
        return m_complexContent;
    }

  bool isMixed(void) {
        return m_mixed;
    }

  bool isElementAbstract(void) {
        return m_elementAbstract;
    }

  void setChildElement(std::shared_ptr<ReferenceBase> childElement) {
        m_childElement = childElement;
    }

  void setComplexContent(std::shared_ptr<XsdComplexContent> complexContent) {
        m_complexContent = complexContent;
    }

  void setSimpleContent(std::shared_ptr<XsdSimpleContent> simpleContent) {
        m_simpleContent = simpleContent;
    }

  std::optional<std::string> getBlock(void) {
        return m_block.getValue();
    }

  std::shared_ptr<XsdGroup> getChildAsGroup(void);
  std::shared_ptr<XsdAll> getChildAsAll(void);
  std::shared_ptr<XsdChoice> getChildAsChoice(void);
  std::shared_ptr<XsdSequence> getChildAsSequence(void);
};
