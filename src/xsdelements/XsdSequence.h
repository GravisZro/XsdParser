#pragma once

#include <xsdelements/visitors/XsdAbstractElementVisitor.h>
#include <xsdelements/elementswrapper/ReferenceBase.h>
#include <xsdelements/XsdMultipleElements.h>
#include <xsdelements/AttributeValidations.h>

/**
 * A class representing the xsd:sequence element. Since it shares the same attributes as {@link XsdAll} or
 * {@link XsdChoice} it extends {@link XsdMultipleElements}. For more information check {@link XsdMultipleElements}.
 *
 * @see <a href="https://www.w3schools.com/xml/el_sequence.asp">xsd:sequence description and usage at w3c</a>
 */
class XsdSequence : public XsdMultipleElements
{
public: // ctors
  XsdSequence(StringMap attributesMap,
              VisitorFunctionType visitorFunction,
              XsdAbstractElement* parent)
    : XsdMultipleElements(attributesMap, visitorFunction, parent),
      m_minOccurs(1),
      m_maxOccurs("1")
  {
    if(haveAttribute(MIN_OCCURS_TAG))
      m_minOccurs = AttributeValidations::validateNonNegativeInteger(*TAG<XsdSequence>::xsd, *MIN_OCCURS_TAG, getAttribute(MIN_OCCURS_TAG));

    if(haveAttribute(MAX_OCCURS_TAG))
      m_maxOccurs = AttributeValidations::maxOccursValidation(*TAG<XsdSequence>::xsd, getAttribute(MAX_OCCURS_TAG));
  }

  /**
   * Performs a copy of the current object for replacing purposes. The cloned objects are used to replace
   * {@link UnsolvedReference} objects in the reference solving process.
   * @param placeHolderAttributes The additional attributes to add to the clone.
   * @return A copy of the object from which is called upon.
   */
  XsdSequence(const XsdSequence& other, XsdAbstractElement* parent = nullptr)
   : XsdSequence(other.getAttributesMap(), other.m_visitorFunction, parent)
  {
    for(auto& element : other.getElements())
      m_elements.push_back(new ReferenceBase(element, this));

    setCloneOf(&other);
  }

public:
  void accept(XsdAbstractElementVisitor* visitorParam) override
  {
    XsdMultipleElements::accept(visitorParam);
    visitorParam->visit(static_cast<XsdSequence*>(this));
  }

  int getMinOccurs(void) const
  {
    return m_minOccurs;
  }

  std::string getMaxOccurs(void) const
  {
    return m_maxOccurs;
  }

private:
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
