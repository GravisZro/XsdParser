#include "XsdMultipleElements.h"

#include <xsdelements/elementswrapper/NamedConcreteElement.h>
#include <xsdelements/elementswrapper/ReferenceBase.h>
#include <xsdelements/elementswrapper/UnsolvedReference.h>
#include <xsdelements/XsdAbstractElement.h>
#include <xsdelements/XsdElement.h>
#include <xsdelements/XsdGroup.h>
#include <xsdelements/XsdAll.h>
#include <xsdelements/XsdChoice.h>
#include <xsdelements/XsdSequence.h>

/**
 * Replaces possible {@link UnsolvedReference} objects in the {@link XsdMultipleElements#elements} if any of their
 * {@link UnsolvedReference#ref} field matches the {@link NamedConcreteElement#name} field.
 * @param elementWrapper A {@link NamedConcreteElement} with a name that will replace an {@link UnsolvedReference}
 *                       object, if a match between the {@link NamedConcreteElement#name} attribute and the
 *                       {@link UnsolvedReference#ref} attribute.
 */
void XsdMultipleElements::replaceUnsolvedElements(NamedConcreteElement* elementWrapper)
{
  if (dynamic_cast<XsdElement*>(elementWrapper->getElement()) != nullptr)
    XsdAnnotatedElements::replaceUnsolvedElements(elementWrapper);

  if (dynamic_cast<XsdGroup*>(elementWrapper->getElement()) != nullptr)
  {
    m_elements.push_back(elementWrapper);
    m_elements.remove_if([elementWrapper](ReferenceBase* ref)
    {
      auto x = dynamic_cast<UnsolvedReference*>(ref);
      return x != nullptr &&
                  compareReference(elementWrapper, x);
    });
  }
}

/**
 * @return The elements that are fully resolved. The {@link UnsolvedReference} objects aren't returned.
 */
std::list<XsdAbstractElement*> XsdMultipleElements::getXsdElements(void) const
{
  std::list<XsdAbstractElement*> rval;
  for(auto& element : m_elements)
    if(dynamic_cast<ConcreteElement*>(element) != nullptr)
      rval.push_back(element->getElement());
  return rval;
}

void XsdMultipleElements::addElement(XsdAbstractElement* element)
{
  m_elements.push_back(ReferenceBase::createFromXsd(element));
}
