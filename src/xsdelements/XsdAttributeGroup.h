#pragma once


//#include <core/XsdParserCore.h>
#include <core/utils/ParseData.h>
#include <xsdelements/elementswrapper/NamedConcreteElement.h>
#include <xsdelements/elementswrapper/ReferenceBase.h>
#include <xsdelements/elementswrapper/UnsolvedReference.h>
#include <xsdelements/XsdAbstractElement.h>

#include <xsdelements/XsdNamedElements.h>

#include <list>
#include <map>
// import java.util.Optional;
#include <functional>
// import java.util.stream.Collectors;
// import java.util.stream.Stream;

/**
 * A class is representing xsd:attributeGroup elements. It can have a ref attribute and therefore extends from
 * {@link XsdNamedElements}, which serves as a base to every element type that can have a ref attribute. For more
 * information check {@link XsdNamedElements}.
 *
 * @see <a href="https://www.w3schools.com/xml/el_attributegroup.asp">xsd:attributeGroup element description and usage at w3c</a>
 */
class XsdAttributeGroup : public XsdNamedElements
{
public:
  using XsdNamedElements::clone;
  constexpr static const std::string_view XSD_TAG = "xsd:attributeGroup";
  constexpr static const std::string_view XS_TAG = "xs:attributeGroup";
  constexpr static const std::string_view TAG = "attributeGroup";

private:
    /**
     * A list of {@link XsdAttributeGroup} children instances.
     */
    //This list is populated by the replaceUnsolvedElements and never directly (such as a Visitor method like all else).
    //The UnsolvedReference is placed in the XsdParser queue by the default implementation of the Visitor#visit(std::make_shared<XsdAttributeGroup> element)
    //The reference solving process then sends the XsdAttributeGroup to this class.
    std::list<std::shared_ptr<ReferenceBase>> m_attributeGroups;

    /**
     * A list of {@link XsdAttribute} children instances.
     */
    std::list<std::shared_ptr<ReferenceBase>> m_attributes;
public:
    XsdAttributeGroup(std::shared_ptr<XsdParserCore> parser, StringMap attributesMap, VisitorFunctionReference visitorFunction)
      : XsdNamedElements(parser, attributesMap, visitorFunction) { }

    XsdAttributeGroup(std::shared_ptr<XsdAbstractElement> parent, std::shared_ptr<XsdParserCore> parser, StringMap attributesMap, VisitorFunctionReference visitorFunction)
      : XsdNamedElements(parser, attributesMap, visitorFunction)
    {
        setParent(parent);
    }
public:
  void accept(std::shared_ptr<XsdAbstractElementVisitor> visitorParam)
    {
        XsdNamedElements::accept(visitorParam);
        visitorParam->visit(std::shared_ptr<XsdAttributeGroup>(this));
    }

    /**
     * @return A list of all {@link XsdAttribute} objects contained in the current {@link XsdAttributeGroup} instance,
     * either directly or present in its children {@link XsdAttributeGroup} in the
     * {@link XsdAttributeGroup#attributeGroups} field.
     */
  std::list<std::shared_ptr<ReferenceBase>> getElements(void)
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
  std::shared_ptr<XsdNamedElements> clone(StringMap placeHolderAttributes)
    {
        placeHolderAttributes.merge(m_attributesMap);
        placeHolderAttributes.erase(*REF_TAG);

        auto elementCopy = std::make_shared<XsdAttributeGroup>(m_parent, m_parser, placeHolderAttributes, m_visitorFunction);

        std::transform(std::begin(m_attributes), std::end(m_attributes),
                       std::end(elementCopy->m_attributes),
                       [this, elementCopy](std::shared_ptr<ReferenceBase> attributeReference)
          { return ReferenceBase::clone(m_parser, attributeReference, elementCopy); });

        std::transform(std::begin(m_attributeGroups), std::end(m_attributeGroups),
                       std::end(elementCopy->m_attributeGroups),
                       [this, elementCopy](std::shared_ptr<ReferenceBase> attributeGroupReference)
          { return ReferenceBase::clone(m_parser, attributeGroupReference, elementCopy); });

        elementCopy->m_cloneOf = std::shared_ptr<XsdAbstractElement>(this);
        elementCopy->m_parent = nullptr;

        return elementCopy;
    }

  void replaceUnsolvedElements(std::shared_ptr<NamedConcreteElement> element)
    {
        if (std::dynamic_pointer_cast<XsdAttributeGroup>(element->getElement()))
        { // TODO
          /*
            Optional<ReferenceBase> attributeGroupUnsolvedReference = attributeGroups.stream().filter(attributeGroup -> attributeGroup instanceof UnsolvedReference && ((UnsolvedReference) attributeGroup).getRef().equals(element.getName())).findFirst();
            if (attributeGroupUnsolvedReference.isPresent())
            {
                m_attributeGroups.remove(attributeGroupUnsolvedReference.get());
                m_attributeGroups.add(element);
            }
*/
        }
    }

  std::list<std::shared_ptr<XsdAttributeGroup>> getXsdAttributeGroups(void)
  {
    return {}; // TODO
    /*
        return attributeGroups
                .stream()
                .filter(element -> element.getElement() instanceof XsdAttributeGroup)
                .map(element -> (XsdAttributeGroup) element.getElement());
                */
    }

  std::list<std::shared_ptr<XsdAttributeGroup>> getAllXsdAttributeGroups(void)
  {
    return {}; // TODO
    /*
        std::list<std::shared_ptr<XsdAttributeGroup>> a;

        for(XsdAttributeGroup attributeGroup: attributeGroups
                .stream()
                .filter(element -> element.getElement() instanceof XsdAttributeGroup)
                .map(element -> (XsdAttributeGroup) element.getElement())
                ){

            a.add(attributeGroup);

            a.addAll(attributeGroup.getAllXsdAttributeGroups());
        }

        return a.stream();
        */
    }

    /**
     * @return All the attributes of this attributeGroup and other attributeGroups contained within.
     */
  std::list<std::shared_ptr<XsdAttribute>> getXsdAttributes(void)
  {
    return {}; // TODO
    /*
        return m_attributes
                .stream()
                .filter(element -> element.getElement() instanceof XsdAttribute)
                .map(element -> (XsdAttribute) element.getElement());
                */
  }

    /**
     * @return The attributes directly defined in this attributeGroup.
     */
  std::list<std::shared_ptr<XsdAttribute>> getDirectAttributes(void)
  {
    return {}; // TODO
    /*
        return attributes
                    .stream()
                    .filter(element -> element.getElement() instanceof XsdAttribute)
                    .map(element -> (XsdAttribute) element.getElement());
                    */
    }

  static std::shared_ptr<ReferenceBase> parse(ParseData parseData)
  {
        return xsdParseSkeleton(parseData.node, std::static_pointer_cast<XsdAbstractElement>(std::make_shared<XsdAttributeGroup>(parseData.parserInstance, XsdAbstractElement::getAttributesMap(parseData.node), parseData.visitorFunction)));
    }

  void addAttribute(std::shared_ptr<ReferenceBase> attribute)
  {
    m_attributes.push_back(attribute);
  }

  void addAttributeGroup(std::shared_ptr<ReferenceBase> attributeGroup) {
        m_attributeGroups.push_back(attributeGroup);
    }
};
