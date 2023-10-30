#pragma once


#include <xsdelements/XsdAbstractElement.h>
#include <xsdelements/XsdAnnotatedElements.h>
#include <xsdelements/XsdAttribute.h>
#include <xsdelements/XsdAttributeGroup.h>
#include <xsdelements/elementswrapper/ConcreteElement.h>
#include <xsdelements/elementswrapper/NamedConcreteElement.h>
#include <xsdelements/elementswrapper/ReferenceBase.h>
#include <xsdelements/elementswrapper/UnsolvedReference.h>
#include <xsdelements/visitors/XsdNamedElementsVisitor.h>

/**
 * Represents the restrictions of the all elements that can contain {@link XsdAttribute} and {@link XsdAttributeGroup}.
 * This visitor contains the {@link AttributesVisitor#attributes} and {@link AttributesVisitor#attributeGroups} that
 * belong to the owner and apart from receiving the attributes in the visit method this visitor also performs the
 * {@link AttributesVisitor#replaceUnsolvedAttributes} method, which is a method that was shared by all the types that
 * contained a list of {@link XsdAttribute} and {@link XsdAttributeGroup} objects.
 * Can also have xsd:annotation children as per inheritance of {@link XsdAnnotatedElementsVisitor}.
 */
class AttributesVisitor : public XsdNamedElementsVisitor
{
public:
  AttributesVisitor(void) = default;


  virtual void visit(XsdAbstractElement* attribute) override
  {
    XsdNamedElementsVisitor::visit(attribute); // won't impact non-named elements
    if(dynamic_cast<XsdAttribute*>(attribute) != nullptr)
      m_attributes.push_back(ReferenceBase::createFromXsd(attribute));
    else if(dynamic_cast<XsdAttributeGroup*>(attribute) != nullptr)
      m_attributeGroups.push_back(ReferenceBase::createFromXsd(attribute));
  }

  void setAttributes(std::list<ReferenceBase*> attributes)
  {
    m_attributes = attributes;
  }

  void setAttributeGroups(std::list<ReferenceBase*> attributeGroups)
  {
    m_attributeGroups = attributeGroups;
  }

    /**
     * @return All the wrapped {@link XsdAttribute} objects received by this visitor.
     */
  std::list<ReferenceBase*> getAttributes(void) const
  {
    return m_attributes;
  }

    /**
     * @return All the wrapped {@link XsdAttributeGroup} objects received by this visitor.
     */
  std::list<ReferenceBase*> getAttributeGroups(void) const
  {
    return m_attributeGroups;
  }

    /**
     * @return All the {@link XsdAttribute} objects that are fully resolved by this visitor. The {@link XsdAttribute}
     * objects wrapped in {@link UnsolvedReference} objects are not returned.
     */
  std::list<XsdAttribute*> getXsdAttributes(void) const
  {
    std::list<XsdAttribute*> xsd_attrs;
    for(auto& attribute : m_attributes)
      if(auto x = dynamic_cast<XsdAttribute*>(attribute->getElement()); x != nullptr)
        xsd_attrs.push_back(x);
    return xsd_attrs;
  }

    /**
     * @return All the {@link XsdAttributeGroup} objects that are fully resolved by this visitor. The
     * {@link XsdAttributeGroup} objects wrapped in {@link UnsolvedReference} objects are not returned.
     */
  std::list<XsdAttributeGroup*> getXsdAttributeGroups(void) const
  {
    std::list<XsdAttributeGroup*> xsd_attrgrps;
    for(auto& attributeGroup : m_attributeGroups)
      if(dynamic_cast<XsdAttribute*>(attributeGroup) != nullptr)
        xsd_attrgrps.push_back(static_cast<XsdAttributeGroup*>(attributeGroup->getElement()));
    return xsd_attrgrps;
  }

  std::list<XsdAttributeGroup*> getAllXsdAttributeGroups(void) const
  {
    std::list<XsdAttributeGroup*> allXsdAttributeGroups;
    for(auto& element : m_attributeGroups)
      if(auto x = dynamic_cast<XsdAttributeGroup*>(element->getElement()); x != nullptr)
      {
        allXsdAttributeGroups.push_back(x);
        allXsdAttributeGroups.merge(x->getAllXsdAttributeGroups());
      }
    return allXsdAttributeGroups;
  }

    /**
     * Tries to match the received {@link NamedConcreteElement} object, with any of the elements present either in
     * {@link AttributesVisitor#attributeGroups} or {@link AttributesVisitor#attributes}. If a match occurs this method
     * performs all the required actions to fully exchange the {@link UnsolvedReference} object with the element parameter.
     * @param element The resolved element that will be match with the contents of this visitor in order to assert if
     *                there is anything to replace.
     */
  void replaceUnsolvedAttributes(NamedConcreteElement* element,
                                 XsdAbstractElement* parent)
  {
    ReferenceBase* firstRef = nullptr;
    if(dynamic_cast<XsdAttributeGroup*>(element->getElement()) != nullptr)
      for(auto& attributeGroup : m_attributeGroups)
        if(auto x = dynamic_cast<UnsolvedReference*>(attributeGroup);
           x != nullptr &&
           XsdAbstractElement::compareReference(element, x))
        {
          firstRef = attributeGroup;
          break;
        }

    if(firstRef != nullptr)
    {
      m_attributeGroups.remove(firstRef);
      m_attributeGroups.push_back(new ReferenceBase(element, parent));
      firstRef = nullptr;
    }

    if(dynamic_cast<XsdAttribute*>(element->getElement()) != nullptr)
      for(auto& attribute : m_attributes)
        if(auto x = dynamic_cast<UnsolvedReference*>(attribute);
           x != nullptr &&
           XsdAbstractElement::compareReference(element, x))
        {
          firstRef = attribute;
          break;
        }

    if(firstRef != nullptr)
    {
      m_attributes.remove(firstRef);
      m_attributes.push_back(new ReferenceBase(element, parent));
    }
  }

  std::list<XsdAttribute*> getAllAttributes(void) const
  {
    std::list<XsdAttribute*> allAttributes = getXsdAttributes();
    for(auto& attributeGroup : getXsdAttributeGroups())
      for(auto& attributeReference : attributeGroup->getElements())
        if(dynamic_cast<ConcreteElement*>(attributeReference) != nullptr)
          allAttributes.push_back(static_cast<XsdAttribute*>(attributeReference->getElement()));
    return allAttributes;
  }

private:
  /**
   * The list of {@link XsdAttributeGroup} instances received by this visitor, wrapped in a {@link ReferenceBase} object.
   */
  std::list<ReferenceBase*> m_attributeGroups;

  /**
   * The list of {@link XsdAttribute} instances received by this visitor, wrapped in a {@link ReferenceBase} object.
   */
  std::list<ReferenceBase*> m_attributes;
};
