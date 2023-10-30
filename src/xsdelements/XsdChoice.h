#pragma once

#include <xsdelements/visitors/XsdAbstractElementVisitor.h>

#include <xsdelements/XsdMultipleElements.h>
#include <xsdelements/AttributeValidations.h>
#include <xsdelements/elementswrapper/ReferenceBase.h>

class XsdSequence;
class XsdGroup;

/**
 * A class representing the xsd:choice element. Since it shares the same attributes as {@link XsdChoice} or
 * {@link XsdSequence} it extends {@link XsdMultipleElements}. For more information check {@link XsdMultipleElements}.
 *
 * @see <a href="https://www.w3schools.com/xml/el_choice.asp">xsd:choice element description and usage at w3c</a>
 */
class XsdChoice : public XsdMultipleElements
{
public: // ctors
  XsdChoice(StringMap attributesMap,
            VisitorFunctionType visitorFunction,
            XsdAbstractElement* parent)
    : XsdMultipleElements(attributesMap, visitorFunction, parent),
      m_minOccurs(1),
      m_maxOccurs("1")
  {
    if(haveAttribute(MIN_OCCURS_TAG))
      m_minOccurs = AttributeValidations::validateNonNegativeInteger(*TAG<XsdChoice>::xsd, *MIN_OCCURS_TAG, getAttribute(MIN_OCCURS_TAG));

    if(haveAttribute(MAX_OCCURS_TAG))
      m_maxOccurs = AttributeValidations::maxOccursValidation(*TAG<XsdChoice>::xsd, getAttribute(MAX_OCCURS_TAG));
  }

  /**
   * Performs a copy of the current object for replacing purposes. The cloned objects are used to replace
   * {@link UnsolvedReference} objects in the reference solving process.
   * @param placeHolderAttributes The additional attributes to add to the clone.
   * @return A copy of the object from which is called upon.
   */

  XsdChoice(const XsdChoice& other, XsdAbstractElement* parent = nullptr)
    : XsdChoice(other.getAttributesMap(), other.m_visitorFunction, parent)
  {
    for(auto& element : other.getElements())
      m_elements.push_back(new ReferenceBase(element, this));
  }

public:
  void accept(XsdAbstractElementVisitor* visitorParam) override
  {
    XsdMultipleElements::accept(visitorParam);
    visitorParam->visit(static_cast<XsdChoice*>(this));
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
     * XsdSchema* element.
     */
  int m_minOccurs;

  /**
     * Specifies the maximum number of times this element can occur in the parent element. The value can be any
     * number bigger or equal to 0, or if you want to set no limit on the maximum number, use the value "unbounded".
     * Default value is 1. This attribute cannot be used if the parent element is the XsdSchema* element.
     */
  std::string m_maxOccurs;
};
