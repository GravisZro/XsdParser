#pragma once

#include <xsdelements/XsdMultipleElements.h>
#include <xsdelements/AttributeValidations.h>

struct XsdAbstractElementVisitor;

/**
 * A class representing the xsd:all element. Since it shares the same attributes as {@link XsdChoice} or {@link XsdSequence}
 * it extends {@link XsdMultipleElements}. For more information check {@link XsdMultipleElements}.
 *
 * @see <a href="https://www.w3schools.com/xml/el_all.asp">xsd:all element definition and usage</a>
 */
class XsdAll : public XsdMultipleElements
{
public: // ctors
  XsdAll(StringMap attributesMap,
         VisitorFunctionType visitorFunction,
         XsdAbstractElement* parent)
    : XsdMultipleElements(attributesMap, visitorFunction, parent),
      m_minOccurs(1),
      m_maxOccurs(1)
  {
    if(haveAttribute(MIN_OCCURS_TAG))
      m_minOccurs = AttributeValidations::validateNonNegativeInteger(*TAG<XsdAll>::xsd, *MIN_OCCURS_TAG, getAttribute(MIN_OCCURS_TAG));
    if(haveAttribute(MAX_OCCURS_TAG))
      m_maxOccurs = AttributeValidations::validateNonNegativeInteger(*TAG<XsdAll>::xsd, *MAX_OCCURS_TAG, getAttribute(MAX_OCCURS_TAG));
  }

  XsdAll(const XsdAll& other, XsdAbstractElement* parent = nullptr);

public:
  void accept(XsdAbstractElementVisitor* visitorParam) override;

  /**
   * Performs a copy of the current object for replacing purposes. The cloned objects are used to replace
   * {@link UnsolvedReference} objects in the reference solving process.
   * @param placeHolderAttributes The additional attributes to add to the clone.
   * @return A copy of the object from which is called upon.
   */

  int getMinOccurs(void) const
  {
    return m_minOccurs;
  }

  int getMaxOccurs(void) const
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
   * number bigger or equal to 0. Default value is 1. This attribute cannot be used if the parent element is the
   * XsdSchema element.
   */
  int m_maxOccurs;
};
