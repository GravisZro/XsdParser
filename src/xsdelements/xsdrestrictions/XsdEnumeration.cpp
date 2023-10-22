#include "XsdEnumeration.h"

#include <xsdelements/visitors/XsdAbstractElementVisitor.h>

void XsdEnumeration::accept(std::shared_ptr<XsdAbstractElementVisitor> xsdAbstractElementVisitor)
{
  XsdStringRestrictions::accept(xsdAbstractElementVisitor);
  xsdAbstractElementVisitor->visit(std::static_pointer_cast<XsdEnumeration>(shared_from_this()));
}

/**
 * Performs a copy of the current object for replacing purposes. The cloned objects are used to replace
 * {@link UnsolvedReference} objects in the reference solving process.
 * @param placeHolderAttributes The additional attributes to add to the clone.
 * @return A copy of the object from which is called upon.
 */
std::shared_ptr<XsdEnumeration> XsdEnumeration::clone(StringMap placeHolderAttributes)
{
  placeHolderAttributes.merge(getAttributesMap());
  return create<XsdEnumeration>(getParser(),
                                placeHolderAttributes,
                                m_visitorFunction,
                                nullptr);
}
