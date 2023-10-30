#pragma once

#include <xsdelements/XsdAbstractElement.h>
#include <xsdelements/visitors/XsdAbstractElementVisitor.h>

#include <xsdelements/xsdrestrictions/XsdStringRestrictions.h>


/**
 * States a pattern that a given attribute must match in order to be considered valid. The value is defined as a
 * {@link std::string}. This value is usually defined as a regular expression.
 */
class XsdPattern : public XsdStringRestrictions
{
public: // ctors
  XsdPattern(StringMap attributesMap,
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
  XsdPattern(const XsdPattern& other, XsdAbstractElement* parent = nullptr)
    : XsdPattern(other.getAttributesMap(), other.m_visitorFunction, parent)
  {
  }
public:
  void accept(XsdAbstractElementVisitor* xsdAbstractElementVisitor) override
  {
    XsdStringRestrictions::accept(xsdAbstractElementVisitor);
    xsdAbstractElementVisitor->visit(static_cast<XsdPattern*>(this));
  }
};
