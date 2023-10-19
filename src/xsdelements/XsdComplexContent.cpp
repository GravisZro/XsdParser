#include "XsdComplexContent.h"

#include <xsdelements/XsdExtension.h>
#include <xsdelements/XsdRestriction.h>
#include <xsdelements/AttributeValidations.h>

XsdComplexContent::XsdComplexContent(std::shared_ptr<XsdParserCore> parser, StringMap attributesMap, VisitorFunctionReference visitorFunction)
  : XsdAnnotatedElements(parser, attributesMap, visitorFunction),
    m_mixed(false)
{
  if(attributesMap.contains(*MIXED_TAG))
    m_mixed = AttributeValidations::validateBoolean(attributesMap.at(*MIXED_TAG));
}


/**
 * Performs a copy of the current object for replacing purposes. The cloned objects are used to replace
 * {@link UnsolvedReference} objects in the reference solving process.
 * @param placeHolderAttributes The additional attributes to add to the clone.
 * @return A copy of the object from which is called upon.
 */
std::shared_ptr<XsdComplexContent> XsdComplexContent::clone(StringMap placeHolderAttributes)
{
    placeHolderAttributes.merge(m_attributesMap);

    auto elementCopy = std::make_shared<XsdComplexContent>(m_parser, placeHolderAttributes, m_visitorFunction);

    elementCopy->m_restriction = ReferenceBase::clone(m_parser, m_restriction, elementCopy);
    elementCopy->m_extension = ReferenceBase::clone(m_parser, m_extension, elementCopy);
    elementCopy->m_cloneOf = std::shared_ptr<XsdAbstractElement>(this);
    elementCopy->m_parent = nullptr;

    return elementCopy;
}

std::shared_ptr<XsdExtension> XsdComplexContent::getXsdExtension(void)
{
if(auto e = std::dynamic_pointer_cast<ConcreteElement>(m_extension))
  return std::static_pointer_cast<XsdExtension>(e->getElement());
return nullptr;
}

std::shared_ptr<XsdRestriction> XsdComplexContent::getXsdRestriction(void)
{
if(auto r = std::dynamic_pointer_cast<ConcreteElement>(m_restriction))
  return std::static_pointer_cast<XsdRestriction>(r->getElement());
return nullptr;
}
