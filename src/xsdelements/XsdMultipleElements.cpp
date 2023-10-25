#include "XsdMultipleElements.h"

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
void XsdMultipleElements::replaceUnsolvedElements(std::shared_ptr<NamedConcreteElement> elementWrapper)
{
    if (std::dynamic_pointer_cast<XsdElement>(elementWrapper->getElement()))
        XsdAnnotatedElements::replaceUnsolvedElements(elementWrapper);

    if (std::dynamic_pointer_cast<XsdGroup>(elementWrapper->getElement()))
    {
        m_elements.push_back(elementWrapper);
        m_elements.remove_if([elementWrapper](std::shared_ptr<ReferenceBase> e)
        {
          auto x = std::dynamic_pointer_cast<UnsolvedReference>(e);
          return x && compareReference(elementWrapper, x);
        });
    }
}

/**
 * @return All the elements received in the parsing process.
 */
std::list<std::shared_ptr<ReferenceBase>> XsdMultipleElements::getElements(void) const
{
    return m_elements;
}

/**
 * @return The elements that are fully resolved. The {@link UnsolvedReference} objects aren't returned.
 */
std::list<std::shared_ptr<XsdAbstractElement>> XsdMultipleElements::getXsdElements(void) const
{
  std::list<std::shared_ptr<XsdAbstractElement>> rval;
  for(auto& element : m_elements)
    if(std::dynamic_pointer_cast<ConcreteElement>(element))
      rval.push_back(element->getElement());
  return rval;
}

/**
 * @return The children elements that are of the type {@link XsdElement}.
 */
std::list<std::shared_ptr<XsdElement>> XsdMultipleElements::getChildrenElements(void) const
{
  std::list<std::shared_ptr<XsdElement>> rval;
  for(auto& element : getXsdElements())
    if(auto x = std::dynamic_pointer_cast<XsdElement>(element); x)
      rval.push_back(x);
  return rval;
}

void XsdMultipleElements::addElement(std::shared_ptr<XsdAbstractElement> element){
    m_elements.push_back(ReferenceBase::createFromXsd(element));
}
