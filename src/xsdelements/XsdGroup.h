#pragma once

#include <type_traits>

#include <xsdelements/elementswrapper/ReferenceBase.h>
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
public: // ctors
  XsdGroup(StringMap attributesMap,
           VisitorFunctionType visitorFunction,
           XsdAbstractElement* parent)
    : XsdNamedElements(attributesMap, visitorFunction, parent),
      m_childElement(nullptr),
      m_minOccurs(1),
      m_maxOccurs("1")
  {
    if(haveAttribute(MIN_OCCURS_TAG))
      m_minOccurs = AttributeValidations::validateNonNegativeInteger(*TAG<XsdGroup>::xsd, *MIN_OCCURS_TAG, getAttribute(MIN_OCCURS_TAG));

    if(haveAttribute(MAX_OCCURS_TAG))
      m_maxOccurs = AttributeValidations::maxOccursValidation(*TAG<XsdGroup>::xsd, getAttribute(MAX_OCCURS_TAG));
  }

  /**
     * Performs a copy of the current object for replacing purposes. The cloned objects are used to replace
     * {@link UnsolvedReference} objects in the reference solving process.
     * @param placeHolderAttributes The additional attributes to add to the clone.
     * @return A copy of the object from which is called upon.
     */
  XsdGroup(XsdGroup* other)
    : XsdGroup(other->getAttributesMap(), other->m_visitorFunction, other->getParent())
  {
    removeAttribute(REF_TAG);

    if (other->m_childElement != nullptr)
      m_childElement = new XsdMultipleElements(other->m_childElement->getAttributesMap(), nullptr, this);
  }

public:
  /**
     * Runs verifications on each concrete element to ensure that the XSD schema rules are verified.
     */
  virtual void validateSchemaRules(void) const override
  {
    XsdNamedElements::validateSchemaRules();

    rule2();
    rule3();
  }

  void accept(XsdAbstractElementVisitor* visitorParam) override
  {
    XsdNamedElements::accept(visitorParam);
    visitorParam->visit(static_cast<XsdGroup*>(this));
  }

  /**
   * @return A list with the child element of the {@link XsdGroup} instance.
   */
  virtual std::list<ReferenceBase*> getElements(void) const override
  {
    std::list<ReferenceBase*> list;
    if (m_childElement != nullptr)
      list.push_back(ReferenceBase::createFromXsd(m_childElement));
    return list;
  }


  void setChildElement(XsdMultipleElements* childElement)
  {
    m_childElement = childElement;
    for(auto& childElementObj : childElement->getElements())
      childElementObj->getElement()->setParent(childElement);
    m_childElement->setParent(this);
  }

  int getMinOccurs(void) const
  {
    return m_minOccurs;
  }

  std::string getMaxOccurs(void) const
  {
    return m_maxOccurs;
  }

  XsdMultipleElements* getChildElement(void) const
  {
    return m_childElement;
  }

  /**
   * @return The childElement as the templated type object or null if childElement isn't of the templated type's instance.
   */
  template<typename T, std::enable_if_t<std::is_base_of_v<XsdMultipleElements, T>, bool> = true>
  T* getChildAs(void) const
    { return dynamic_cast<T*>(getChildElement()); }

private:
  /**
   * Asserts if the current object has the name attribute when not being a direct child of the XsdSchema element, which is
   * not allowed, throwing an exception in that case.
   */
  void rule2(void) const
  {
    if (dynamic_cast<XsdSchema*>(getParent()) == nullptr && getRawName())
      throw ParsingException(TAG<XsdGroup>::xsd + " element: The " + NAME_TAG + " should only be used when the parent of the " + TAG<XsdGroup>::xsd + " is the " + TAG<XsdSchema>::xsd + " element.");
  }

  /**
   * Asserts if the current has no value for its name attribute while being a direct child of the top level XsdSchema element,
   * which is required. Throws an exception if no name is present.
   */
  void rule3(void) const
  {
    if (dynamic_cast<XsdSchema*>(getParent()) != nullptr && !getRawName())
      throw ParsingException(TAG<XsdGroup>::xsd + " element: The " + NAME_TAG + " should is required the parent of the " + TAG<XsdGroup>::xsd + " is the " + TAG<XsdSchema>::xsd + " element.");
  }

private:
  /**
   * The child element of the {@link XsdGroup} instance. It can be a {@link XsdAll}, {@link XsdChoice} or a
   * {@link XsdSequence} instance.
   */
  XsdMultipleElements* m_childElement;

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
};
