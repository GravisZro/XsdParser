#include "XsdElement.h"

#include <core/XsdParserCore.h>
#include <xsdelements/elementswrapper/NamedConcreteElement.h>
#include <xsdelements/elementswrapper/UnsolvedReference.h>

#include <xsdelements/AttributeValidations.h>
#include <xsdelements/XsdElement.h>
#include <xsdelements/XsdSchema.h>

#include <xsdelements/XsdComplexType.h>
#include <xsdelements/XsdSimpleType.h>

#include <xsdelements/exceptions/ParsingException.h>

#define xsdElementIsXsdSchema TAG<XsdElement>::xsd + " is a " + TAG<XsdSchema>::xsd + " element."
XsdElement::XsdElement(StringMap attributesMap,
           VisitorFunctionType visitorFunction,
           XsdAbstractElement* parent)
  : XsdNamedElements(attributesMap, visitorFunction, parent),
    m_complexType(nullptr),
    m_simpleType(nullptr),
    m_type(nullptr),
    m_substitutionGroup(nullptr),
    m_nillable(false),
    m_abstractObj(false),
    m_minOccurs(1),
    m_maxOccurs("1")
{
  m_form = AttributeValidations::getFormDefaultValue(getParent());
  m_block = AttributeValidations::getBlockDefaultValue(getParent());
  m_finalObj = AttributeValidations::getFinalDefaultValue(getParent());

  if (haveAttribute(TYPE_TAG))
  {
    std::string typeString = getAttribute(TYPE_TAG);
    if (XsdParserCore::getXsdTypesToCpp().contains(typeString))
    {
      StringMap attributes;
      attributes.emplace(*NAME_TAG, typeString);
      m_type = ReferenceBase::createFromXsd(
                 new XsdBuiltInDataType(attributes,
                                            nullptr,
                                            this));
    }
    else
    {
      m_type = new UnsolvedReference(typeString,
                                         new XsdElement(StringMap{},
                                                            m_visitorFunction,
                                                            this));
      getParser()->addUnsolvedReference(static_cast<UnsolvedReference*>(m_type));
    }
  }

  std::optional<std::string> localSubstitutionGroup;
  if(haveAttribute(SUBSTITUTION_GROUP_TAG))
    localSubstitutionGroup = getAttribute(SUBSTITUTION_GROUP_TAG);

  if (localSubstitutionGroup)
  {
    m_substitutionGroup = new UnsolvedReference(
                            localSubstitutionGroup.value(),
                            static_cast<XsdNamedElements*>(
                              new XsdElement(StringMap{},
                                                 m_visitorFunction,
                                                 this)));
    getParser()->addUnsolvedReference(static_cast<UnsolvedReference*>(m_substitutionGroup));
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
    m_minOccurs = AttributeValidations::validateNonNegativeInteger(*TAG<XsdElement>::xsd, *MIN_OCCURS_TAG, getAttribute(MIN_OCCURS_TAG));

  if(haveAttribute(MAX_OCCURS_TAG))
    m_maxOccurs = AttributeValidations::maxOccursValidation(*TAG<XsdElement>::xsd, getAttribute(MAX_OCCURS_TAG));
}


/**
 * Performs a copy of the current object for replacing purposes. The cloned objects are used to replace
 * {@link UnsolvedReference} objects in the reference solving process.
 * @param placeHolderAttributes The additional attributes to add to the clone.
 * @return A copy of the object from which is called upon.
 */
XsdElement::XsdElement(const XsdElement& other)
  : XsdElement(other.getAttributesMap(), other.m_visitorFunction, other.getParent())
{
  removeAttribute(TYPE_TAG);
  removeAttribute(REF_TAG);

  if (other.m_simpleType != nullptr)
    m_simpleType = new ReferenceBase(other.m_simpleType, this);

  if (other.m_complexType != nullptr)
    m_complexType = new ReferenceBase(other.m_complexType, this);

  if (other.m_type != nullptr)
  {
    if (dynamic_cast<ConcreteElement*>(other.m_type) != nullptr)
      m_type = new ReferenceBase(other.m_type, this);
    else
    {
      m_type = new UnsolvedReference(
                              static_cast<UnsolvedReference*>(m_type)->getRef().value(),
                              new XsdElement(StringMap{},
                                                 m_visitorFunction,
                                                 nullptr));
      getParser()->addUnsolvedReference(static_cast<UnsolvedReference*>(m_type));
    }
  }

  setCloneOf(&other);
}

/**
 * Asserts if the current object has a form attribute while being a direct child of the top level XsdSchema element,
 * which isn't allowed, throwing an exception in that case.
 */
void XsdElement::rule7(void) const
{
  if (dynamic_cast<XsdSchema*>(getParent()) != nullptr && haveAttribute(FORM_TAG))
    throw ParsingException(*TAG<XsdElement>::xsd + " element: The " + FORM_TAG + " attribute can only be present when the parent of the " + xsdElementIsXsdSchema);
}

void XsdElement::rule6(void) const
{
  //fixed 	Optional. Specifies a fixed value for the element (can only be used if the element's content is a simple type or text only)
}

void XsdElement::rule5(void) const
{
  // default 	Optional. Specifies a default value for the element (can only be used if the element's content is a simple type or text only)
}

/**
 * Asserts if the current object isn't a direct child of the top level XsdSchema and has a value for the substitutionGroup,
 * which isn't allowed, throwing an exception in that case.
 */
void XsdElement::rule4(void) const
{
  if (dynamic_cast<XsdSchema*>(getParent()) == nullptr && m_substitutionGroup)
    throw ParsingException(*TAG<XsdElement>::xsd + " element: The " + SUBSTITUTION_GROUP_TAG + " attribute can only be present when the parent of the " + xsdElementIsXsdSchema);
}

/**
 * Asserts if the current object has a ref attribute while being a direct child of the top level XsdSchema element, which isn't allowed,
 * throwing an exception in that case.
 */
void XsdElement::rule3(void) const
{
  if (dynamic_cast<XsdSchema*>(getParent()) != nullptr && haveAttribute(REF_TAG))
    throw ParsingException(*TAG<XsdElement>::xsd + " element: The " + REF_TAG + " attribute cannot be present when the parent of the " + xsdElementIsXsdSchema);
}

/**
 * Asserts if the current object is a direct child of the top level XsdSchema element and doesn't have a name, which isn't allowed,
 * throwing an exception in that case.
 */
void XsdElement::rule2(void) const
{
  if (dynamic_cast<XsdSchema*>(getParent()) != nullptr && !getRawName())
    throw ParsingException(*TAG<XsdElement>::xsd + " element: The " + NAME_TAG + " attribute is required when the parent of the " + xsdElementIsXsdSchema);
}

/**
 * This method aims to replace the previously created {@link UnsolvedReference} in case that the type of the
 * current {@link XsdElement} instance is not a built-in type.
 * @param element A concrete element with a name that will replace the {@link UnsolvedReference} object created in the
 *                {@link XsdElement} constructor. The {@link UnsolvedReference} is only replaced if there
 *                is a match between the {@link UnsolvedReference#ref} and the {@link NamedConcreteElement#name}.
 */
void XsdElement::replaceUnsolvedElements(NamedConcreteElement* elementWrapper)
{
  XsdNamedElements::replaceUnsolvedElements(elementWrapper);

  XsdNamedElements* element = elementWrapper->getElement();

  bool isComplexOrSimpleType = dynamic_cast<XsdComplexType*>(element) != nullptr ||
                               dynamic_cast<XsdSimpleType*>(element) != nullptr;

  if(dynamic_cast<UnsolvedReference*>(m_type) != nullptr &&
     isComplexOrSimpleType &&
     compareReference(elementWrapper, static_cast<UnsolvedReference*>(m_type)))
    m_type = elementWrapper;

  if (dynamic_cast<UnsolvedReference*>(m_substitutionGroup) != nullptr &&
      dynamic_cast<XsdElement*>(element) != nullptr &&
      compareReference(elementWrapper, static_cast<UnsolvedReference*>(m_substitutionGroup)))
    m_substitutionGroup = elementWrapper;
}

XsdComplexType* XsdElement::getXsdComplexType(void) const
{
  if(m_complexType == nullptr || dynamic_cast<UnsolvedReference*>(m_complexType) != nullptr)
    return getXsdComplexTypeFromType();
  return static_cast<XsdComplexType*>(m_complexType->getElement());
}

XsdSimpleType* XsdElement::getXsdSimpleType(void) const
{
  if(m_simpleType == nullptr || dynamic_cast<UnsolvedReference*>(m_simpleType) != nullptr)
    return getXsdSimpleTypeFromType();
  return static_cast<XsdSimpleType*>(m_simpleType->getElement());
}

XsdComplexType* XsdElement::getXsdComplexTypeFromType(void) const
{
  if (dynamic_cast<ConcreteElement*>(m_type) != nullptr)
    if(auto x = dynamic_cast<XsdComplexType*>(m_type->getElement()); x != nullptr)
      return x;
  return nullptr;
}

XsdSimpleType* XsdElement::getXsdSimpleTypeFromType(void) const
{
  if (dynamic_cast<ConcreteElement*>(m_type) != nullptr)
    if(auto x = dynamic_cast<XsdSimpleType*>(m_type->getElement()); x != nullptr)
      return x;
  return nullptr;
}

XsdNamedElements* XsdElement::getTypeAsXsd(void) const
{
  if (auto x = dynamic_cast<NamedConcreteElement*>(m_type); x != nullptr)
    return x->getElement();
  return nullptr;
}

XsdComplexType* XsdElement::getTypeAsComplexType(void) const
{
  if (dynamic_cast<NamedConcreteElement*>(m_type) != nullptr)
    if(auto x = dynamic_cast<XsdComplexType*>(m_type->getElement()); x != nullptr)
      return x;
  return nullptr;
}

XsdSimpleType* XsdElement::getTypeAsSimpleType(void) const
{
  if (dynamic_cast<NamedConcreteElement*>(m_type) != nullptr)
    if(auto x = dynamic_cast<XsdSimpleType*>(m_type->getElement()); x != nullptr)
      return x;
  return nullptr;
}

XsdBuiltInDataType* XsdElement::getTypeAsBuiltInDataType(void) const
{
  if (dynamic_cast<NamedConcreteElement*>(m_type) != nullptr)
    if(auto x = dynamic_cast<XsdBuiltInDataType*>(m_type->getElement()); x != nullptr)
      return x;
  return nullptr;
}

std::optional<std::string> XsdElement::getType(void) const
{
  if (auto x = dynamic_cast<NamedConcreteElement*>(m_type); x != nullptr)
    return x->getName();
  if(haveAttribute(TYPE_TAG))
    return getAttribute(TYPE_TAG);
  return std::nullopt;
}

XsdElement* XsdElement::getXsdSubstitutionGroup(void) const
{
  if (dynamic_cast<ConcreteElement*>(m_substitutionGroup) != nullptr)
    if(auto x = dynamic_cast<XsdElement*>(m_substitutionGroup->getElement()); x != nullptr)
      return x;
  return nullptr;
}
