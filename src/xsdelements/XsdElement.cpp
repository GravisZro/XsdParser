#include "XsdElement.h"

#include <core/XsdParserCore.h>
#include <xsdelements/elementswrapper/ReferenceBase.h>
#include <xsdelements/elementswrapper/UnsolvedReference.h>
#include <xsdelements/XsdElement.h>
#include <xsdelements/XsdSchema.h>

#include <xsdelements/XsdComplexType.h>
#include <xsdelements/XsdSimpleType.h>

#include <xsdelements/exceptions/ParsingException.h>

#define xsdElementIsXsdSchema XsdElement::XSD_TAG + " is a " + XsdSchema::XSD_TAG + " element."


XsdElement::XsdElement(std::shared_ptr<XsdParserCore> parser,
                       StringMap attributesMap,
                       VisitorFunctionReference visitorFunction,
                       std::shared_ptr<XsdAbstractElement> parent)
  : XsdNamedElements(parser, attributesMap, visitorFunction, parent),
    m_minOccurs(1),
    m_maxOccurs("1")
{ }

void XsdElement::initialize(void)
{
  XsdNamedElements::initialize();

  if (haveAttribute(TYPE_TAG))
  {
    std::string typeString = getAttribute(TYPE_TAG);
    if (XsdParserCore::getXsdTypesToJava().contains(typeString))
    {
      StringMap attributes;
      attributes.emplace(*NAME_TAG, typeString);
      m_type = ReferenceBase::createFromXsd(
                 create<XsdBuiltInDataType>(getParser(),
                                            attributes,
                                            shared_from_this()));
    }
    else
    {
      m_type = create<UnsolvedReference>(typeString,
                                         create<XsdElement>(getParser(),
                                                            StringMap{},
                                                            m_visitorFunction,
                                                            shared_from_this()));
      getParser()->addUnsolvedReference(std::static_pointer_cast<UnsolvedReference>(m_type));
    }
  }

  m_form = AttributeValidations::getFormDefaultValue(getParent());
  m_block = AttributeValidations::getBlockDefaultValue(getParent());
  m_finalObj = AttributeValidations::getFinalDefaultValue(getParent());
  m_nillable = false;
  m_abstractObj = false;

  std::optional<std::string> localSubstitutionGroup;
  if(haveAttribute(SUBSTITUTION_GROUP_TAG))
    localSubstitutionGroup = getAttribute(SUBSTITUTION_GROUP_TAG);

  if (localSubstitutionGroup)
  {
    m_substitutionGroup = create<UnsolvedReference>(
                            localSubstitutionGroup.value(),
                            std::static_pointer_cast<XsdNamedElements>(
                              create<XsdElement>(getParser(),
                                                 StringMap{},
                                                 m_visitorFunction,
                                                 shared_from_this())));
    getParser()->addUnsolvedReference(std::static_pointer_cast<UnsolvedReference>(m_substitutionGroup));
  }

  if(haveAttribute(DEFAULT_TAG))
    m_defaultObj = getAttribute(DEFAULT_TAG);


  if(haveAttribute(FIXED_TAG))
    m_fixed = getAttribute(FIXED_TAG);

  if(haveAttribute(FORM_TAG))
    m_form = AttributeValidations::belongsToEnum<FormEnum>(getAttribute(FORM_TAG));

  if(haveAttribute(NILLABLE_TAG))
    m_nillable = AttributeValidations::validateBoolean(getAttribute(NILLABLE_TAG));

  if(haveAttribute(ABSTRACT_TAG))
    m_abstractObj = AttributeValidations::validateBoolean(getAttribute(ABSTRACT_TAG));

  if(haveAttribute(BLOCK_TAG))
    m_block = AttributeValidations::belongsToEnum<BlockEnum>(getAttribute(BLOCK_TAG));

  if(haveAttribute(FINAL_TAG))
    m_finalObj = AttributeValidations::belongsToEnum<FinalEnum>(getAttribute(FINAL_TAG));

  if(haveAttribute(MIN_OCCURS_TAG))
    m_minOccurs = AttributeValidations::validateNonNegativeInteger(*XSD_TAG, *MIN_OCCURS_TAG, getAttribute(MIN_OCCURS_TAG));

  if(haveAttribute(MAX_OCCURS_TAG))
    m_maxOccurs = AttributeValidations::maxOccursValidation(*XSD_TAG, getAttribute(MAX_OCCURS_TAG));
}



/**
 * Asserts if the current object has a form attribute while being a direct child of the top level XsdSchema element,
 * which isn't allowed, throwing an exception in that case.
 */
void XsdElement::rule7(void)
{
  if (std::dynamic_pointer_cast<XsdSchema>(getParent()) && haveAttribute(FORM_TAG))
    throw ParsingException(*XSD_TAG + " element: The " + FORM_TAG + " attribute can only be present when the parent of the " + xsdElementIsXsdSchema);
}

void XsdElement::rule6(void)
{
    //fixed 	Optional. Specifies a fixed value for the element (can only be used if the element's content is a simple type or text only)
}

void XsdElement::rule5(void)
{
    // default 	Optional. Specifies a default value for the element (can only be used if the element's content is a simple type or text only)
}

/**
 * Asserts if the current object isn't a direct child of the top level XsdSchema and has a value for the substitutionGroup,
 * which isn't allowed, throwing an exception in that case.
 */
void XsdElement::rule4(void)
{
  if (std::dynamic_pointer_cast<XsdSchema>(getParent()) == nullptr && m_substitutionGroup)
    throw ParsingException(*XSD_TAG + " element: The " + SUBSTITUTION_GROUP_TAG + " attribute can only be present when the parent of the " + xsdElementIsXsdSchema);
}

/**
 * Asserts if the current object has a ref attribute while being a direct child of the top level XsdSchema element, which isn't allowed,
 * throwing an exception in that case.
 */
void XsdElement::rule3(void)
{
  if (std::dynamic_pointer_cast<XsdSchema>(getParent()) && haveAttribute(REF_TAG))
    throw ParsingException(*XSD_TAG + " element: The " + REF_TAG + " attribute cannot be present when the parent of the " + xsdElementIsXsdSchema);
}

/**
 * Asserts if the current object is a direct child of the top level XsdSchema element and doesn't have a name, which isn't allowed,
 * throwing an exception in that case.
 */
void XsdElement::rule2(void)
{
  if (std::dynamic_pointer_cast<XsdSchema>(getParent()) && !getRawName())
    throw ParsingException(*XSD_TAG + " element: The " + NAME_TAG + " attribute is required when the parent of the " + xsdElementIsXsdSchema);
}


/**
 * Performs a copy of the current object for replacing purposes. The cloned objects are used to replace
 * {@link UnsolvedReference} objects in the reference solving process.
 * @param placeHolderAttributes The additional attributes to add to the clone.
 * @return A copy of the object from which is called upon.
 */
std::shared_ptr<XsdElement> XsdElement::clone(StringMap placeHolderAttributes)
{
    placeHolderAttributes.merge(getAttributesMap());
    placeHolderAttributes.erase(*TYPE_TAG);
    placeHolderAttributes.erase(*REF_TAG);

    auto elementCopy = create<XsdElement>(getParser(),
                                          placeHolderAttributes,
                                          m_visitorFunction,
                                          getParent());

    if (m_simpleType){
        elementCopy->m_simpleType = ReferenceBase::clone(getParser(), m_simpleType, elementCopy);
    }

    if (m_complexType){
        elementCopy->m_complexType = ReferenceBase::clone(getParser(), m_complexType, elementCopy);
    }

    if (m_type)
    {
        if (std::dynamic_pointer_cast<ConcreteElement>(m_type))
        {
            elementCopy->m_type = ReferenceBase::clone(getParser(), m_type, elementCopy);
        }
        else
        {
          elementCopy->m_type = create<UnsolvedReference>(
                                  std::static_pointer_cast<UnsolvedReference>(m_type)->getRef().value(),
                                  create<XsdElement>(getParser(),
                                                     StringMap{},
                                                     m_visitorFunction,
                                                     elementCopy));
          getParser()->addUnsolvedReference(std::static_pointer_cast<UnsolvedReference>(elementCopy->m_type));
        }
    }

    elementCopy->setCloneOf(shared_from_this());
    elementCopy->setParent(nullptr);

    return elementCopy;
}



/**
 * This method aims to replace the previously created {@link UnsolvedReference} in case that the type of the
 * current {@link XsdElement} instance is not a built-in type.
 * @param element A concrete element with a name that will replace the {@link UnsolvedReference} object created in the
 *                {@link XsdElement} constructor. The {@link UnsolvedReference} is only replaced if there
 *                is a match between the {@link UnsolvedReference#ref} and the {@link NamedConcreteElement#name}.
 */
void XsdElement::replaceUnsolvedElements(std::shared_ptr<NamedConcreteElement> element)
{
    XsdNamedElements::replaceUnsolvedElements(element);

    std::shared_ptr<XsdNamedElements> elem = element->getElement();

    bool isComplexOrSimpleType = std::dynamic_pointer_cast<XsdComplexType>(elem) ||
                                 std::dynamic_pointer_cast<XsdSimpleType>(elem);

    if(std::dynamic_pointer_cast<UnsolvedReference>(m_type) &&
        isComplexOrSimpleType &&
       compareReference(element, std::static_pointer_cast<UnsolvedReference>(m_type)))
    {
        m_type = element;
    }

    if (std::dynamic_pointer_cast<UnsolvedReference>(m_substitutionGroup) &&
        std::dynamic_pointer_cast<XsdElement>(elem) &&
        compareReference(element, std::static_pointer_cast<UnsolvedReference>(m_substitutionGroup)))
    {
        m_substitutionGroup = element;
    }
}

std::shared_ptr<XsdComplexType> XsdElement::getXsdComplexType(void)
{
  if(!m_complexType || std::dynamic_pointer_cast<UnsolvedReference>(m_complexType))
    return getXsdComplexTypeFromType();
  return std::static_pointer_cast<XsdComplexType>(m_complexType->getElement());
}

std::shared_ptr<XsdSimpleType> XsdElement::getXsdSimpleType(void)
{
  if(!m_simpleType || std::dynamic_pointer_cast<UnsolvedReference>(m_simpleType))
    return getXsdSimpleTypeFromType();
  return std::static_pointer_cast<XsdSimpleType>(m_simpleType->getElement());
}



std::shared_ptr<XsdComplexType> XsdElement::getXsdComplexTypeFromType(void)
{
  if (std::dynamic_pointer_cast<ConcreteElement>(m_type))
    if(auto x = std::dynamic_pointer_cast<XsdComplexType>(m_type->getElement()); x)
      return x;
  return nullptr;
}

std::shared_ptr<XsdSimpleType> XsdElement::getXsdSimpleTypeFromType(void)
{
  if (std::dynamic_pointer_cast<ConcreteElement>(m_type))
    if(auto x = std::dynamic_pointer_cast<XsdSimpleType>(m_type->getElement()); x)
      return x;
  return nullptr;
}

std::shared_ptr<XsdNamedElements> XsdElement::getTypeAsXsd(void)
{
  if (auto x = std::dynamic_pointer_cast<NamedConcreteElement>(m_type); x)
    return x->getElement();
  return nullptr;
}

std::shared_ptr<XsdComplexType> XsdElement::getTypeAsComplexType(void)
{
  if (std::dynamic_pointer_cast<NamedConcreteElement>(m_type))
    if(auto x = std::dynamic_pointer_cast<XsdComplexType>(m_type->getElement()); x)
      return x;
  return nullptr;
}

std::shared_ptr<XsdSimpleType> XsdElement::getTypeAsSimpleType(void)
{
  if (std::dynamic_pointer_cast<NamedConcreteElement>(m_type))
    if(auto x = std::dynamic_pointer_cast<XsdSimpleType>(m_type->getElement()); x)
      return x;
  return nullptr;
}

std::shared_ptr<XsdBuiltInDataType> XsdElement::getTypeAsBuiltInDataType(void)
{
  if (std::dynamic_pointer_cast<NamedConcreteElement>(m_type))
    if(auto x = std::dynamic_pointer_cast<XsdBuiltInDataType>(m_type->getElement()); x)
      return x;
  return nullptr;
}



std::optional<std::string> XsdElement::getType(void)
{
  if (auto x = std::dynamic_pointer_cast<NamedConcreteElement>(m_type); x)
    return x->getName();
  if(haveAttribute(TYPE_TAG))
    return getAttribute(TYPE_TAG);
  return std::nullopt;
}

std::shared_ptr<XsdElement> XsdElement::getXsdSubstitutionGroup(void)
{
  if (std::dynamic_pointer_cast<ConcreteElement>(m_substitutionGroup))
    if(auto x = std::dynamic_pointer_cast<XsdElement>(m_substitutionGroup->getElement()); x)
      return x;
  return nullptr;
}
