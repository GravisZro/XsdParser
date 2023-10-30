#include "XsdAttributeGroup.h"

#include <xsdelements/elementswrapper/UnsolvedReference.h>
#include <xsdelements/elementswrapper/NamedConcreteElement.h>

#include <xsdelements/XsdAttribute.h>
#include <xsdelements/XsdAttributeGroup.h>

#include <algorithm>

/**
 * Performs a copy of the current object for replacing purposes. The cloned objects are used to replace
 * {@link UnsolvedReference} objects in the reference solving process.
 * @param placeHolderAttributes The additional attributes to add to the clone.
 * @return A copy of the object from which is called upon.
 */

XsdAttributeGroup::XsdAttributeGroup(const XsdAttributeGroup& other, XsdAbstractElement* parent)
  : XsdAttributeGroup(other.getAttributesMap(), other.m_visitorFunction, parent)
{
  removeAttribute(REF_TAG);

  for(const auto& attribute : other.m_attributes)
    m_attributes.push_back(new ReferenceBase(attribute, this));

  for(const auto& attributeGroup : other.m_attributeGroups)
    m_attributeGroups.push_back(new ReferenceBase(attributeGroup, this));

  setCloneOf(&other);
}

/**
 * @return A list of all {@link XsdAttribute} objects contained in the current {@link XsdAttributeGroup} instance,
 * either directly or present in its children {@link XsdAttributeGroup} in the
 * {@link XsdAttributeGroup#attributeGroups} field.
 */
std::list<ReferenceBase*> XsdAttributeGroup::getElements(void) const
{
  std::list<ReferenceBase*> allAttributes = m_attributes;
  for(auto& attributeGroup : getXsdAttributeGroups())
    allAttributes.merge(attributeGroup->getElements());
  return allAttributes;
}

void XsdAttributeGroup::replaceUnsolvedElements(NamedConcreteElement* elementWrapper)
{
  if (dynamic_cast<XsdAttributeGroup*>(elementWrapper->getElement()) != nullptr)
  {
    ReferenceBase* attributeGroupUnsolvedReference = nullptr;
    for(auto& attributeGroup : m_attributeGroups)
      if(auto x = dynamic_cast<UnsolvedReference*>(attributeGroup);
         x != nullptr && x->getRef() && x->getRef() == elementWrapper->getName())
      {
        attributeGroupUnsolvedReference = attributeGroup;
        break;
      }

    if (attributeGroupUnsolvedReference != nullptr)
    {
      m_attributeGroups.remove(attributeGroupUnsolvedReference);
      m_attributeGroups.push_back(elementWrapper);
    }
  }
}

std::list<XsdAttributeGroup*> XsdAttributeGroup::getXsdAttributeGroups(void) const
{
  std::list<XsdAttributeGroup*> rvals;
  for(auto& element : m_attributeGroups)
    if(auto x = dynamic_cast<XsdAttributeGroup*>(element->getElement()); x != nullptr)
      rvals.push_back(x);
  return rvals;
}

std::list<XsdAttributeGroup*> XsdAttributeGroup::getAllXsdAttributeGroups(void) const
{
  std::list<XsdAttributeGroup*> rvals;
  for(auto& attributeGroup : getXsdAttributeGroups())
  {
    rvals.push_back(attributeGroup);
    rvals.merge(attributeGroup->getAllXsdAttributeGroups());
  }
  return rvals;
}

/**
 * @return All the attributes of this attributeGroup and other attributeGroups contained within.
 */
std::list<XsdAttribute*> XsdAttributeGroup::getXsdAttributes(void) const
{
  std::list<XsdAttribute*> rvals;
  for(auto& element : m_attributes)
    if(auto x = dynamic_cast<XsdAttribute*>(element->getElement()); x != nullptr)
      rvals.push_back(x);
  return rvals;
}
