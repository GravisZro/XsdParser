#include "XsdGroup.h"

#include <xsdelements/XsdMultipleElements.h>
#include <xsdelements/XsdAll.h>
#include <xsdelements/XsdChoice.h>
#include <xsdelements/XsdSequence.h>


std::shared_ptr<XsdMultipleElements> XsdGroup::getChildElement(void) const
{
  return m_childElement;
}

/**
 * @return The childElement as a {@link XsdAll} object or null if childElement isn't a {@link XsdAll} instance.
 */
std::shared_ptr<XsdAll> XsdGroup::getChildAsAll(void) const
{
  return std::dynamic_pointer_cast<XsdAll>(getChildElement());
}

/**
 * @return The childElement as a {@link XsdChoice} object or null if childElement isn't a {@link XsdChoice} instance.
 */
std::shared_ptr<XsdChoice> XsdGroup::getChildAsChoice(void) const
{
  return std::dynamic_pointer_cast<XsdChoice>(getChildElement());
}

/**
 * @return The childElement as a {@link XsdSequence} object or null if childElement isn't a {@link XsdSequence} instance.
 */
std::shared_ptr<XsdSequence> XsdGroup::getChildAsSequence(void) const
{
  return std::dynamic_pointer_cast<XsdSequence>(getChildElement());
}
