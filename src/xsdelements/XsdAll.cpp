#include "XsdAll.h"

#include <core/XsdParserCore.h>

#include <xsdelements/elementswrapper/ReferenceBase.h>
#include <xsdelements/visitors/XsdAbstractElementVisitor.h>

/**
 * Performs a copy of the current object for replacing purposes. The cloned objects are used to replace
 * {@link UnsolvedReference} objects in the reference solving process.
 * @param placeHolderAttributes The additional attributes to add to the clone.
 * @return A copy of the object from which is called upon.
 */
XsdAll::XsdAll(const XsdAll& other, XsdAbstractElement* parent)
  : XsdAll(other.getAttributesMap(), other.m_visitorFunction, parent)
{
  for(auto& element : other.getElements())
    m_elements.push_back(new ReferenceBase(element, this));

  setCloneOf(&other);
}

void XsdAll::accept(XsdAbstractElementVisitor* visitorParam)
{
  XsdMultipleElements::accept(visitorParam);
  visitorParam->visit(static_cast<XsdAll*>(this));
}
