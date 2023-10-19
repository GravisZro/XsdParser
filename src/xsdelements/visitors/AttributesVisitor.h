#pragma once


#include <xsdelements/XsdAbstractElement.h>
#include <xsdelements/XsdAnnotatedElements.h>
#include <xsdelements/XsdAttribute.h>
#include <xsdelements/XsdAttributeGroup.h>
#include <xsdelements/elementswrapper/ConcreteElement.h>
#include <xsdelements/elementswrapper/NamedConcreteElement.h>
#include <xsdelements/elementswrapper/ReferenceBase.h>
#include <xsdelements/elementswrapper/UnsolvedReference.h>
#include <xsdelements/visitors/XsdAnnotatedElementsVisitor.h>

// import java.util.ArrayList;
#include <list>
// import java.util.stream.Collectors;
// import java.util.stream.Stream;

/**
 * Represents the restrictions of the all elements that can contain {@link XsdAttribute} and {@link XsdAttributeGroup}.
 * This visitor contains the {@link AttributesVisitor#attributes} and {@link AttributesVisitor#attributeGroups} that
 * belong to the owner and apart from receiving the attributes in the visit method this visitor also performs the
 * {@link AttributesVisitor#replaceUnsolvedAttributes} method, which is a method that was shared by all the types that
 * contained a list of {@link XsdAttribute} and {@link XsdAttributeGroup} objects.
 * Can also have xsd:annotation children as per inheritance of {@link XsdAnnotatedElementsVisitor}.
 */
class AttributesVisitor : public XsdAnnotatedElementsVisitor
{
private:
    /**
     * The list of {@link XsdAttributeGroup} instances received by this visitor, wrapped in a {@link ReferenceBase} object.
     */
    std::list<std::shared_ptr<ReferenceBase>> m_attributeGroups;

    /**
     * The list of {@link XsdAttribute} instances received by this visitor, wrapped in a {@link ReferenceBase} object.
     */
    std::list<std::shared_ptr<ReferenceBase>> m_attributes;
public:
    using XsdAnnotatedElementsVisitor::visit;

    AttributesVisitor(std::shared_ptr<XsdAnnotatedElements> owner)
      : XsdAnnotatedElementsVisitor(owner) { }

  void visit(std::shared_ptr<XsdAttribute> attribute)
    {
        XsdAbstractElementVisitor::visit(attribute);
        m_attributes.push_back(ReferenceBase::createFromXsd(attribute));
    }

  void visit(std::shared_ptr<XsdAttributeGroup> attributeGroup)
    {
        XsdAbstractElementVisitor::visit(attributeGroup);
        m_attributeGroups.push_back(ReferenceBase::createFromXsd(attributeGroup));
    }

  void setAttributes(std::list<std::shared_ptr<ReferenceBase>> attributes) {
        m_attributes = attributes;
    }

  void setAttributeGroups(std::list<std::shared_ptr<ReferenceBase>> attributeGroups) {
        m_attributeGroups = attributeGroups;
    }

    /**
     * @return All the wrapped {@link XsdAttribute} objects received by this visitor.
     */
  std::list<std::shared_ptr<ReferenceBase>> getAttributes(void) {
        return m_attributes;
    }

    /**
     * @return All the wrapped {@link XsdAttributeGroup} objects received by this visitor.
     */
  std::list<std::shared_ptr<ReferenceBase>> getAttributeGroups(void) {
        return m_attributeGroups;
    }

    /**
     * @return All the {@link XsdAttribute} objects that are fully resolved by this visitor. The {@link XsdAttribute}
     * objects wrapped in {@link UnsolvedReference} objects are not returned.
     */
  std::list<std::shared_ptr<XsdAttribute>> getXsdAttributes(void)
  {
    std::list<std::shared_ptr<XsdAttribute>> xsd_attrs;
    for(auto& attribute : m_attributes)
      if(auto x = std::dynamic_pointer_cast<XsdAttribute>(attribute->getElement()); x)
        xsd_attrs.push_back(x);
    return xsd_attrs;
  }

    /**
     * @return All the {@link XsdAttributeGroup} objects that are fully resolved by this visitor. The
     * {@link XsdAttributeGroup} objects wrapped in {@link UnsolvedReference} objects are not returned.
     */
  std::list<std::shared_ptr<XsdAttributeGroup>> getXsdAttributeGroups(void)
  {
    std::list<std::shared_ptr<XsdAttributeGroup>> xsd_attrgrps;
    for(auto& attributeGroup : m_attributeGroups)
      if(std::dynamic_pointer_cast<XsdAttribute>(attributeGroup))
        xsd_attrgrps.push_back(std::static_pointer_cast<XsdAttributeGroup>(attributeGroup->getElement()));
    return xsd_attrgrps;
  }

  std::list<std::shared_ptr<XsdAttributeGroup>> getAllXsdAttributeGroups(void)
  {
    std::list<std::shared_ptr<XsdAttributeGroup>> allXsdAttributeGroups;
    for(auto& element : m_attributeGroups)
      if(auto x = std::dynamic_pointer_cast<XsdAttributeGroup>(element->getElement()); x)
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
  void replaceUnsolvedAttributes(std::shared_ptr<XsdParserCore> parser,
                                 std::shared_ptr<NamedConcreteElement> element,
                                 std::shared_ptr<XsdAbstractElement> parent)
  {
    std::shared_ptr<ReferenceBase> firstRef;
    if(std::dynamic_pointer_cast<XsdAttributeGroup>(element->getElement()))
      for(auto& attributeGroup : m_attributeGroups)
        if(auto x = std::dynamic_pointer_cast<UnsolvedReference>(attributeGroup);
           x && XsdAbstractElement::compareReference(element, x))
        {
          firstRef = attributeGroup;
          break;
        }

    if(firstRef)
    {
      m_attributeGroups.remove(firstRef);
      m_attributeGroups.push_back(ReferenceBase::clone(parser, element, parent));
      firstRef.reset();
    }

    if(std::dynamic_pointer_cast<XsdAttribute>(element->getElement()))
      for(auto& attribute : m_attributes)
        if(auto x = std::dynamic_pointer_cast<UnsolvedReference>(attribute);
           x && XsdAbstractElement::compareReference(element, x))
        {
          firstRef = attribute;
          break;
        }

    if(firstRef)
    {
      m_attributes.remove(firstRef);
      m_attributes.push_back(ReferenceBase::clone(parser, element, parent));
    }
  }

  std::list<std::shared_ptr<XsdAttribute>> getAllAttributes(void)
  {
    std::list<std::shared_ptr<XsdAttribute>> allAttributes = getXsdAttributes();
    for(auto& attributeGroup : getXsdAttributeGroups())
      for(auto& attributeReference : attributeGroup->getElements())
        if(std::dynamic_pointer_cast<ConcreteElement>(attributeReference))
          allAttributes.push_back(std::static_pointer_cast<XsdAttribute>(attributeReference->getElement()));
    return allAttributes;
  }
};
