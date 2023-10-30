#include "XsdComplexType.h"

#include <xsdelements/XsdComplexContent.h>
#include <xsdelements/XsdSimpleContent.h>

#include <xsdelements/XsdMultipleElements.h>
#include <xsdelements/XsdAll.h>
#include <xsdelements/XsdGroup.h>
#include <xsdelements/XsdChoice.h>
#include <xsdelements/XsdSequence.h>

#include <xsdelements/elementswrapper/NamedConcreteElement.h>
#include <xsdelements/visitors/XsdComplexTypeVisitor.h>

/**
 * Performs a copy of the current object for replacing purposes. The cloned objects are used to replace
 * {@link UnsolvedReference} objects in the reference solving process.
 * @param placeHolderAttributes The additional attributes to add to the clone.
 * @return A copy of the object from which is called upon.
 */
XsdComplexType::XsdComplexType(const XsdComplexType& other, XsdAbstractElement* parent)
  : XsdComplexType(other.getAttributesMap(), other.m_visitorFunction, parent)
{
  removeAttribute(REF_TAG);

  m_childElement = new ReferenceBase(other.m_childElement, this);

  if (other.m_complexContent != nullptr)
    m_complexContent = new XsdComplexContent(*other.m_complexContent, this);

  if (other.m_simpleContent != nullptr)
    m_simpleContent = new XsdSimpleContent(*other.m_simpleContent, this);

  std::list<ReferenceBase*> clonedAttributes;
  std::list<ReferenceBase*> clonedAttributeGroups;

  for(auto& attribute : static_cast<XsdComplexTypeVisitor*>(other.getVisitor())->getAttributes())
    clonedAttributes.push_back(new ReferenceBase(attribute, this));

  for(auto& attributeGroup : static_cast<XsdComplexTypeVisitor*>(other.getVisitor())->getAttributeGroups())
    clonedAttributeGroups.push_back(new ReferenceBase(attributeGroup, this));

  static_cast<XsdComplexTypeVisitor*>(getVisitor())->setAttributes(clonedAttributes);
  static_cast<XsdComplexTypeVisitor*>(getVisitor())->setAttributeGroups(clonedAttributeGroups);

  setCloneOf(&other);

}

XsdComplexType::~XsdComplexType(void)
{
  if(m_childElement != nullptr)
    delete m_childElement, m_childElement = nullptr;

  if(m_complexContent != nullptr)
    delete m_complexContent, m_complexContent = nullptr;

  if(m_simpleContent != nullptr)
    delete m_simpleContent, m_simpleContent = nullptr;
}

void XsdComplexType::replaceUnsolvedElements(NamedConcreteElement* elementWrapper)
{
  XsdNamedElements::replaceUnsolvedElements(elementWrapper);
  static_cast<XsdComplexTypeVisitor*>(getVisitor())->replaceUnsolvedAttributes(elementWrapper, this);

  if (auto x = dynamic_cast<UnsolvedReference*>(m_childElement);
      x != nullptr &&
      dynamic_cast<XsdGroup*>(m_childElement->getElement()) != nullptr &&
      dynamic_cast<XsdGroup*>(elementWrapper->getElement()) != nullptr &&
      compareReference(elementWrapper, x))
    m_childElement = elementWrapper;
}

std::optional<std::string> XsdComplexType::getFinal(void) const
{
  return m_elementFinal;
}

std::list<ReferenceBase*> XsdComplexType::getAttributes(void) const
{
  return static_cast<XsdComplexTypeVisitor*>(getVisitor())->getAttributes();
}

std::list<XsdAttribute*> XsdComplexType::getXsdAttributes(void) const
{
  return static_cast<XsdComplexTypeVisitor*>(getVisitor())->getXsdAttributes();
}

std::list<XsdAttributeGroup*> XsdComplexType::getXsdAttributeGroup(void) const
{
  return static_cast<XsdComplexTypeVisitor*>(getVisitor())->getXsdAttributeGroups();
}

std::list<XsdAttributeGroup*> XsdComplexType::getAllXsdAttributeGroups(void) const
{
  return static_cast<XsdComplexTypeVisitor*>(getVisitor())->getAllXsdAttributeGroups();
}

std::list<XsdAttribute*> XsdComplexType::getAllXsdAttributes(void) const
{
  return static_cast<XsdComplexTypeVisitor*>(getVisitor())->getAllAttributes();
}

