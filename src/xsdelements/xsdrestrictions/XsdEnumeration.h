#pragma once

#include <xsdelements/xsdrestrictions/XsdStringRestrictions.h>

struct XsdAbstractElementVisitor;

/**
 * Represents a value that a given XSD type is allowed to take. The value is defined as a {@link std::string}.
 */
class XsdEnumeration : public XsdStringRestrictions
{
public: // ctors
  XsdEnumeration(StringMap attributesMap,
                 VisitorFunctionType visitorFunction,
                 XsdAbstractElement* parent)
    : XsdStringRestrictions(attributesMap, visitorFunction, parent)
  {
  }

  /**
   * Performs a copy of the current object for replacing purposes. The cloned objects are used to replace
   * {@link UnsolvedReference} objects in the reference solving process.
   * @param placeHolderAttributes The additional attributes to add to the clone.
   * @return A copy of the object from which is called upon.
   */
  XsdEnumeration(const XsdEnumeration& other, XsdAbstractElement* parent = nullptr)
    : XsdEnumeration(other.getAttributesMap(), other.m_visitorFunction, parent)
  {
  }

public:
  void accept(XsdAbstractElementVisitor* xsdAbstractElementVisitor) override;
    /**
     * Performs a copy of the current object for replacing purposes. The cloned objects are used to replace
     * {@link UnsolvedReference} objects in the reference solving process.
     * @param placeHolderAttributes The additional attributes to add to the clone.
     * @return A copy of the object from which is called upon.
     */
};
