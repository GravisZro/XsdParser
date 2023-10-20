#include "XsdComplexType.h"

#include <xsdelements/XsdMultipleElements.h>
#include <xsdelements/XsdComplexContent.h>
#include <xsdelements/XsdSimpleContent.h>
#include <xsdelements/XsdGroup.h>
#include <xsdelements/XsdAll.h>
#include <xsdelements/XsdChoice.h>
#include <xsdelements/XsdSequence.h>

XsdComplexType::XsdComplexType(std::shared_ptr<XsdParserCore> parser, StringMap attributesMap, VisitorFunctionReference visitorFunction)
  : XsdNamedElements(parser, attributesMap, visitorFunction),
    m_elementAbstract(false),
    m_mixed(false)
{
    m_block = AttributeValidations::getBlockDefaultValue(m_parent);
    m_elementFinal = AttributeValidations::getFinalDefaultValue(m_parent);

    if(attributesMap.contains(*ABSTRACT_TAG))
      m_elementAbstract = AttributeValidations::validateBoolean(attributesMap.at(*ABSTRACT_TAG));

    if(attributesMap.contains(*MIXED_TAG))
      m_mixed = AttributeValidations::validateBoolean(attributesMap.at(*MIXED_TAG));

    if(attributesMap.contains(*BLOCK_TAG))
      m_block = AttributeValidations::belongsToEnum<ComplexTypeBlockEnum>(attributesMap.at(*BLOCK_TAG));

    if(attributesMap.contains(*FINAL_TAG))
      m_elementFinal = AttributeValidations::belongsToEnum<FinalEnum>(attributesMap.at(*FINAL_TAG));
}

/**
 * Performs a copy of the current object for replacing purposes. The cloned objects are used to replace
 * {@link UnsolvedReference} objects in the reference solving process.
 * @param placeHolderAttributes The additional attributes to add to the clone.
 * @return A copy of the object from which is called upon.
 */
std::shared_ptr<XsdComplexType> XsdComplexType::clone(StringMap placeHolderAttributes)
{
    placeHolderAttributes.merge(m_attributesMap);
    placeHolderAttributes.erase(*REF_TAG);

    auto elementCopy = std::make_shared<XsdComplexType>(m_parent, getParser(), placeHolderAttributes, m_visitorFunction);

    elementCopy->m_childElement = ReferenceBase::clone(getParser(), m_childElement, elementCopy);

    if (m_complexContent)
        elementCopy->m_complexContent = std::static_pointer_cast<XsdComplexContent>(m_complexContent->clone(m_complexContent->getAttributesMap(), elementCopy));

    if (m_simpleContent)
        elementCopy->m_simpleContent = std::static_pointer_cast<XsdSimpleContent>(m_simpleContent->clone(m_simpleContent->getAttributesMap(), elementCopy));

    std::list<std::shared_ptr<ReferenceBase>> clonedAttributes;
    std::list<std::shared_ptr<ReferenceBase>> clonedAttributeGroups;

    for(auto& attribute : std::static_pointer_cast<XsdComplexTypeVisitor>(m_visitor)->getAttributes())
      clonedAttributes.push_back(ReferenceBase::clone(getParser(), attribute, elementCopy));

    for(auto& attributeGroup: std::static_pointer_cast<XsdComplexTypeVisitor>(m_visitor)->getAttributeGroups())
      clonedAttributeGroups.push_back(ReferenceBase::clone(getParser(), attributeGroup, elementCopy));

    std::static_pointer_cast<XsdComplexTypeVisitor>(elementCopy->m_visitor)->setAttributes(clonedAttributes);
    std::static_pointer_cast<XsdComplexTypeVisitor>(elementCopy->m_visitor)->setAttributeGroups(clonedAttributeGroups);

    elementCopy->m_cloneOf = nondeleted_ptr<XsdAbstractElement>(this);
    elementCopy->m_parent = nullptr;

    return elementCopy;
}

void XsdComplexType::replaceUnsolvedElements(std::shared_ptr<NamedConcreteElement> element)
{
    XsdNamedElements::replaceUnsolvedElements(element);
    std::static_pointer_cast<XsdComplexTypeVisitor>(m_visitor)->replaceUnsolvedAttributes(getParser(), element, nondeleted_ptr<XsdComplexType>(this));

    if (auto x = std::dynamic_pointer_cast<UnsolvedReference>(m_childElement);
        x &&
        std::dynamic_pointer_cast<XsdGroup>(m_childElement->getElement()) &&
        std::dynamic_pointer_cast<XsdGroup>(element->getElement()) &&
        compareReference(element, x))
        m_childElement = element;
}

std::shared_ptr<XsdAbstractElement> XsdComplexType::getXsdChildElement(void)
{
if(m_childElement)
  return m_childElement->getElement();
return nullptr;
}

std::optional<std::string> XsdComplexType::getFinal(void) {
    return m_elementFinal.getValue();
}

std::list<std::shared_ptr<ReferenceBase>> XsdComplexType::getAttributes(void) {
    return std::static_pointer_cast<XsdComplexTypeVisitor>(m_visitor)->getAttributes();
}

std::list<std::shared_ptr<XsdAttribute>> XsdComplexType::getXsdAttributes(void) {
    return std::static_pointer_cast<XsdComplexTypeVisitor>(m_visitor)->getXsdAttributes();
}

std::list<std::shared_ptr<XsdAttributeGroup>> XsdComplexType::getXsdAttributeGroup(void) {
    return std::static_pointer_cast<XsdComplexTypeVisitor>(m_visitor)->getXsdAttributeGroups();
}

std::list<std::shared_ptr<XsdAttributeGroup>> XsdComplexType::getAllXsdAttributeGroups(void) {
    return std::static_pointer_cast<XsdComplexTypeVisitor>(m_visitor)->getAllXsdAttributeGroups();
}

std::list<std::shared_ptr<XsdAttribute>> XsdComplexType::getAllXsdAttributes(void) {
    return std::static_pointer_cast<XsdComplexTypeVisitor>(m_visitor)->getAllAttributes();
}


/**
 * @return The childElement as a {@link XsdGroup} object or null if childElement isn't a {@link XsdGroup} instance.
 */
std::shared_ptr<XsdGroup> XsdComplexType::getChildAsGroup(void)
{
  return std::dynamic_pointer_cast<XsdGroup>(m_childElement->getElement());
}

/**
 * @return The childElement as a {@link XsdAll} object or null if childElement isn't a {@link XsdAll} instance.
 */
std::shared_ptr<XsdAll> XsdComplexType::getChildAsAll(void)
{
  if(std::dynamic_pointer_cast<XsdMultipleElements>(m_childElement))
    return XsdMultipleElements::getChildAsAll(std::static_pointer_cast<XsdMultipleElements>(m_childElement->getElement()));
  return nullptr;
}

/**
 * @return The childElement as a {@link XsdChoice} object or null if childElement isn't a {@link XsdChoice} instance.
 */
std::shared_ptr<XsdChoice> XsdComplexType::getChildAsChoice(void)
{
  if(std::dynamic_pointer_cast<XsdMultipleElements>(m_childElement))
    return XsdMultipleElements::getChildAsChoice(std::static_pointer_cast<XsdMultipleElements>(m_childElement->getElement()));
  return nullptr;
}

/**
 * @return The childElement as a {@link XsdSequence} object or null if childElement isn't a {@link XsdSequence} instance.
 */
std::shared_ptr<XsdSequence> XsdComplexType::getChildAsSequence(void)
{
  if(std::dynamic_pointer_cast<XsdMultipleElements>(m_childElement))
    return XsdMultipleElements::getChildAsSequence(std::static_pointer_cast<XsdMultipleElements>(m_childElement->getElement()));
  return nullptr;
}
