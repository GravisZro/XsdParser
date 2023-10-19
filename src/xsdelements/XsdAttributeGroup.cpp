#include "XsdAttributeGroup.h"

#include <xsdelements/XsdAttribute.h>
#include <xsdelements/XsdAttributeGroup.h>

#include <algorithm>

/**
 * @return A list of all {@link XsdAttribute} objects contained in the current {@link XsdAttributeGroup} instance,
 * either directly or present in its children {@link XsdAttributeGroup} in the
 * {@link XsdAttributeGroup#attributeGroups} field.
 */
std::list<std::shared_ptr<ReferenceBase>> XsdAttributeGroup::getElements(void)
{
  std::list<std::shared_ptr<ReferenceBase>> allAttributes = m_attributes;
  for(auto& attributeGroup : getXsdAttributeGroups())
    for(auto& element : attributeGroup->getElements())
      allAttributes.push_back(element);
  return allAttributes;
}

/**
 * Performs a copy of the current object for replacing purposes. The cloned objects are used to replace
 * {@link UnsolvedReference} objects in the reference solving process.
 * @param placeHolderAttributes The additional attributes to add to the clone.
 * @return A copy of the object from which is called upon.
 */
std::shared_ptr<XsdNamedElements> XsdAttributeGroup::clone(StringMap placeHolderAttributes)
{
  placeHolderAttributes.merge(m_attributesMap);
  placeHolderAttributes.erase(*REF_TAG);

  auto elementCopy = std::make_shared<XsdAttributeGroup>(m_parent, getParser(), placeHolderAttributes, m_visitorFunction);

  std::transform(std::begin(m_attributes), std::end(m_attributes),
                 std::end(elementCopy->m_attributes),
                 [this, elementCopy](std::shared_ptr<ReferenceBase> attributeReference)
  { return ReferenceBase::clone(getParser(), attributeReference, elementCopy); });

  std::transform(std::begin(m_attributeGroups), std::end(m_attributeGroups),
                 std::end(elementCopy->m_attributeGroups),
                 [this, elementCopy](std::shared_ptr<ReferenceBase> attributeGroupReference)
  { return ReferenceBase::clone(getParser(), attributeGroupReference, elementCopy); });

  elementCopy->m_cloneOf = std::shared_ptr<XsdAbstractElement>(this);
  elementCopy->m_parent = nullptr;

  return elementCopy;
}

void XsdAttributeGroup::replaceUnsolvedElements(std::shared_ptr<NamedConcreteElement> element)
{
  if (std::dynamic_pointer_cast<XsdAttributeGroup>(element->getElement()))
  {
    std::shared_ptr<ReferenceBase> attributeGroupUnsolvedReference;
    for(auto& attributeGroup : m_attributeGroups)
      if(auto x = std::dynamic_pointer_cast<UnsolvedReference>(attributeGroup);
         x && x->getRef() && x->getRef() == element->getName())
      {
        attributeGroupUnsolvedReference = attributeGroup;
        break;
      }

    if (attributeGroupUnsolvedReference)
    {
      m_attributeGroups.remove(attributeGroupUnsolvedReference);
      m_attributeGroups.push_back(element);
    }
  }
}

std::list<std::shared_ptr<XsdAttributeGroup>> XsdAttributeGroup::getXsdAttributeGroups(void)
{
  std::list<std::shared_ptr<XsdAttributeGroup>> rvals;
  for(auto& element : m_attributeGroups)
    if(auto x = std::dynamic_pointer_cast<XsdAttributeGroup>(element->getElement()); x)
      rvals.push_back(x);
  return rvals;
}

std::list<std::shared_ptr<XsdAttributeGroup>> XsdAttributeGroup::getAllXsdAttributeGroups(void)
{
  std::list<std::shared_ptr<XsdAttributeGroup>> rvals;
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
std::list<std::shared_ptr<XsdAttribute>> XsdAttributeGroup::getXsdAttributes(void)
{
  std::list<std::shared_ptr<XsdAttribute>> rvals;
  for(auto& element : m_attributes)
    if(auto x = std::dynamic_pointer_cast<XsdAttribute>(element->getElement()); x)
      rvals.push_back(x);
  return rvals;
}
