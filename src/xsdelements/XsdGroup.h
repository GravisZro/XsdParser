#pragma once



#include <core/utils/ParseData.h>
#include <xsdelements/elementswrapper/ReferenceBase.h>
#include <xsdelements/elementswrapper/UnsolvedReference.h>
#include <xsdelements/exceptions/ParsingException.h>
#include <xsdelements/visitors/XsdAbstractElementVisitor.h>

#include <xsdelements/XsdNamedElements.h>
#include <xsdelements/XsdMultipleElements.h>
#include <xsdelements/XsdSchema.h>
#include <xsdelements/AttributeValidations.h>

/**
 * A class representing the xsd:complexType element. Extends {@link XsdNamedElements} because it's one of the
 * {@link XsdAbstractElement} concrete classes that can have a {@link XsdNamedElements#name} attribute.
 *
 * @see <a href="https://www.w3schools.com/xml/el_group.asp">xsd:group description and usage at w3c</a>
 */
class XsdGroup : public XsdNamedElements
{
public:
  using XsdNamedElements::clone;
  constexpr static const std::string_view XSD_TAG = "xsd:group";
  constexpr static const std::string_view XS_TAG = "xs:group";
  constexpr static const std::string_view TAG = "group";

private:
    /**
     * The child element of the {@link XsdGroup} instance. It can be a {@link XsdAll}, {@link XsdChoice} or a
     * {@link XsdSequence} instance.
     */
    std::shared_ptr<XsdMultipleElements> m_childElement;

    /**
     * Specifies the minimum number of times this element can occur in the parent element. The value can be any
     * number bigger or equal to 0. Default value is 1. This attribute cannot be used if the parent element is the
     * XsdSchema element.
     */
    int m_minOccurs;

    /**
     * Specifies the maximum number of times this element can occur in the parent element. The value can be any
     * number bigger or equal to 0, or if you want to set no limit on the maximum number, use the value "unbounded".
     * Default value is 1. This attribute cannot be used if the parent element is the XsdSchema element.
     */
    std::string m_maxOccurs;

public:
    XsdGroup(std::shared_ptr<XsdParserCore> parser, StringMap attributesMap, VisitorFunctionReference visitorFunction)
        : XsdNamedElements(parser, attributesMap, visitorFunction),
          m_minOccurs(1),
          m_maxOccurs("1")
    {
      if(attributesMap.contains(*MIN_OCCURS_TAG))
        m_minOccurs = AttributeValidations::validateNonNegativeInteger(*XSD_TAG, *MIN_OCCURS_TAG, attributesMap.at(*MIN_OCCURS_TAG));

      if(attributesMap.contains(*MAX_OCCURS_TAG))
        m_maxOccurs = AttributeValidations::maxOccursValidation(*XSD_TAG, attributesMap.at(*MAX_OCCURS_TAG));
    }

    XsdGroup(std::shared_ptr<XsdAbstractElement> parent, std::shared_ptr<XsdParserCore> parser, StringMap attributesMap, VisitorFunctionReference visitorFunction)
        : XsdGroup(parser, attributesMap, visitorFunction)
    {
        setParent(parent);
    }
public:
    /**
     * Runs verifications on each concrete element to ensure that the XSD schema rules are verified.
     */
  void validateSchemaRules(void)
    {
        XsdNamedElements::validateSchemaRules();

        rule2();
        rule3();
    }

private:
    /**
     * Asserts if the current object has the name attribute when not being a direct child of the XsdSchema element, which is
     * not allowed, throwing an exception in that case.
     */
    void rule2(void)
    {
        if (std::dynamic_pointer_cast<XsdSchema>(m_parent) == nullptr && m_name)
            throw ParsingException(XSD_TAG + " element: The " + NAME_TAG + " should only be used when the parent of the " + XSD_TAG + " is the " + XsdSchema::XSD_TAG + " element.");
    }

    /**
     * Asserts if the current has no value for its name attribute while being a direct child of the top level XsdSchema element,
     * which is required. Throws an exception if no name is present.
     */
    void rule3(void)
    {
        if (std::dynamic_pointer_cast<XsdSchema>(m_parent) && !m_name)
            throw ParsingException(XSD_TAG + " element: The " + NAME_TAG + " should is required the parent of the " + XSD_TAG + " is the " + XsdSchema::XSD_TAG + " element.");
    }
public:
  void accept(std::shared_ptr<XsdAbstractElementVisitor> visitorParam)
    {
        XsdNamedElements::accept(visitorParam);
        visitorParam->visit(nondeleted_ptr<XsdGroup>(this));
    }

    /**
     * @return A list with the child element of the {@link XsdGroup} instance.
     */
  std::list<std::shared_ptr<ReferenceBase>> getElements(void)
  {
    std::list<std::shared_ptr<ReferenceBase>> list;
    if (m_childElement)
      list.push_back(ReferenceBase::createFromXsd(m_childElement));
    return list;
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

        auto elementCopy = std::make_shared<XsdGroup>(m_parent, getParser(), placeHolderAttributes, m_visitorFunction);

        if (m_childElement)
            elementCopy->m_childElement = std::dynamic_pointer_cast<XsdMultipleElements>(m_childElement->clone(m_childElement->getAttributesMap(), elementCopy));

        return elementCopy;
    }

  void setChildElement(std::shared_ptr<XsdMultipleElements> childElement)
  {
        m_childElement = childElement;
        for(auto& childElementObj : childElement->getElements())
          childElementObj->getElement()->setParent(childElement);
        m_childElement->setParent(nondeleted_ptr<XsdGroup>(this));
    }

  std::shared_ptr<XsdMultipleElements> getChildElement(void) {
        return m_childElement;
    }

    /**
     * @return The childElement as a {@link XsdAll} object or null if childElement isn't a {@link XsdAll} instance.
     */
  std::shared_ptr<XsdAll> getChildAsAll(void) {
        return XsdMultipleElements::getChildAsAll(m_childElement);
    }

    /**
     * @return The childElement as a {@link XsdChoice} object or null if childElement isn't a {@link XsdChoice} instance.
     */
  std::shared_ptr<XsdChoice> getChildAsChoice(void) {
        return XsdMultipleElements::getChildAsChoice(m_childElement);
    }

    /**
     * @return The childElement as a {@link XsdSequence} object or null if childElement isn't a {@link XsdSequence} instance.
     */
    // @SuppressWarnings("unused")
  std::shared_ptr<XsdSequence> getChildAsSequence(void) {
        return XsdMultipleElements::getChildAsSequence(m_childElement);
    }

  static std::shared_ptr<ReferenceBase> parse(ParseData parseData)
  {
    return xsdParseSkeleton(parseData.node, std::static_pointer_cast<XsdAbstractElement>(std::make_shared<XsdGroup>(parseData.parserInstance, XsdAbstractElement::getAttributesMap(parseData.node), parseData.visitorFunction)));
  }

  int getMinOccurs(void) {
        return m_minOccurs;
    }

  std::string getMaxOccurs(void) {
        return m_maxOccurs;
    }
};
