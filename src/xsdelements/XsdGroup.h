#pragma once




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

public: // ctors
  XsdGroup(std::shared_ptr<XsdParserCore> parser,
           StringMap attributesMap,
           VisitorFunctionType visitorFunction,
           std::shared_ptr<XsdAbstractElement> parent)
      : XsdNamedElements(parser, attributesMap, visitorFunction, parent),
        m_minOccurs(INT_MIN)
  {
  }

public:
  virtual void initialize(void) override
  {
    XsdNamedElements::initialize();
    m_minOccurs = 1;
    m_maxOccurs = "1";

    if(haveAttribute(MIN_OCCURS_TAG))
      m_minOccurs = AttributeValidations::validateNonNegativeInteger(*TAG<XsdGroup>::xsd, *MIN_OCCURS_TAG, getAttribute(MIN_OCCURS_TAG));

    if(haveAttribute(MAX_OCCURS_TAG))
      m_maxOccurs = AttributeValidations::maxOccursValidation(*TAG<XsdGroup>::xsd, getAttribute(MAX_OCCURS_TAG));
  }

    /**
     * Runs verifications on each concrete element to ensure that the XSD schema rules are verified.
     */
  virtual void validateSchemaRules(void) const override
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
    void rule2(void) const
    {
        if (std::dynamic_pointer_cast<XsdSchema>(getParent()) == nullptr && getRawName())
            throw ParsingException(TAG<XsdGroup>::xsd + " element: The " + NAME_TAG + " should only be used when the parent of the " + TAG<XsdGroup>::xsd + " is the " + TAG<XsdSchema>::xsd + " element.");
    }

    /**
     * Asserts if the current has no value for its name attribute while being a direct child of the top level XsdSchema element,
     * which is required. Throws an exception if no name is present.
     */
    void rule3(void) const
    {
        if (std::dynamic_pointer_cast<XsdSchema>(getParent()) && !getRawName())
            throw ParsingException(TAG<XsdGroup>::xsd + " element: The " + NAME_TAG + " should is required the parent of the " + TAG<XsdGroup>::xsd + " is the " + TAG<XsdSchema>::xsd + " element.");
    }
public:
  void accept(std::shared_ptr<XsdAbstractElementVisitor> visitorParam) override
    {
        XsdNamedElements::accept(visitorParam);
        visitorParam->visit(std::static_pointer_cast<XsdGroup>(shared_from_this()));
    }

    /**
     * @return A list with the child element of the {@link XsdGroup} instance.
     */
  virtual std::list<std::shared_ptr<ReferenceBase>> getElements(void) const override
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
  virtual std::shared_ptr<XsdAbstractElement> clone(StringMap placeHolderAttributes) override
    {
        placeHolderAttributes.merge(getAttributesMap());
        placeHolderAttributes.erase(*REF_TAG);

        auto elementCopy = create<XsdGroup>(getParser(),
                                            placeHolderAttributes,
                                            m_visitorFunction,
                                            getParent());

        if (m_childElement)
            elementCopy->m_childElement = std::dynamic_pointer_cast<XsdMultipleElements>(m_childElement->clone(m_childElement->getAttributesMap(), elementCopy));

        return elementCopy;
    }

  void setChildElement(std::shared_ptr<XsdMultipleElements> childElement)
  {
        m_childElement = childElement;
        for(auto& childElementObj : childElement->getElements())
          childElementObj->getElement()->setParent(childElement);
        m_childElement->setParent(shared_from_this());
    }

  std::shared_ptr<XsdMultipleElements> getChildElement(void) const {
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

  std::shared_ptr<XsdSequence> getChildAsSequence(void) {
        return XsdMultipleElements::getChildAsSequence(m_childElement);
    }

  int getMinOccurs(void) {
        return m_minOccurs;
    }

  std::string getMaxOccurs(void) {
        return m_maxOccurs;
    }
};
