#include "ReferenceBase.h"

#include <core/XsdParserCore.h>
#include <xsdelements/XsdNamedElements.h>
#include <xsdelements/elementswrapper/ConcreteElement.h>
#include <xsdelements/elementswrapper/NamedConcreteElement.h>
#include <xsdelements/elementswrapper/UnsolvedReference.h>
#include <xsdelements/XsdAbstractElement.h>

/**
 * This method creates a ReferenceBase object that serves as a wrapper to {@link XsdAbstractElement} objects.
 * If a {@link XsdAbstractElement} has a ref attribute it results in a {@link UnsolvedReference} object. If it
 * doesn't have a ref attribute and has a name attribute it's a {@link NamedConcreteElement}. If it isn't a
 * {@link UnsolvedReference} or a {@link NamedConcreteElement} then it's a {@link ConcreteElement}.
 * @param element The element which will be "wrapped".
 * @return A wrapper object for the element received.
 */
ReferenceBase* ReferenceBase::createFromXsd(XsdAbstractElement* element)
{
  auto ref = getRef(element);
  auto name = getName(element);

  if(dynamic_cast<XsdNamedElements*>(element) == nullptr)
    return new ConcreteElement(element);

  if(!ref)
  {
    if (!name)
      return new ConcreteElement(element);
    else
      return new NamedConcreteElement(static_cast<XsdNamedElements*>(element), name.value());
  }
  else
    return new UnsolvedReference(static_cast<XsdNamedElements*>(element));
}

ReferenceBase::ReferenceBase(ReferenceBase* other, XsdAbstractElement* parent)
{
  if (other != nullptr)
  {
    XsdAbstractElement* originalElement = other->getElement();
    if (auto original = dynamic_cast<UnsolvedReference*>(other); original != nullptr)
    {
      assert(original->getRef());
      StringMap clonedAttributesMap = originalElement->getAttributesMap();
      clonedAttributesMap.emplace(XsdAbstractElement::REF_TAG, original->getRef().value());

      auto clonedElement = new XsdNamedElements(clonedAttributesMap, nullptr, parent);
      clonedElement->setCloneOf(originalElement);

      auto unsolvedClonedElement = new UnsolvedReference(clonedElement);
      getParser()->addUnsolvedReference(unsolvedClonedElement);
    }
    else
    {
      other->getElement()->setParentAvailable(false);

//            XsdAbstractElement cloneElement = originalElement->clone(originalElement->getAttributesMap());
//            cloneElement.setParent(parent);
//
//            return createFromXsd(cloneElement);
    }
  }
}

std::optional<std::string> ReferenceBase::getName(XsdAbstractElement* element)
{
    return getNodeValue(element, *XsdNamedElements::NAME_TAG);
}

std::optional<std::string> ReferenceBase::getRef(XsdAbstractElement* element)
{
    return getNodeValue(element, *XsdAbstractElement::REF_TAG);
}

/**
 * @param element The element that contains the attributes.
 * @param nodeName The attribute name that will be searched.
 * @return The value of the attribute contained in element with the name nodeName.
 */
std::optional<std::string> ReferenceBase::getNodeValue(XsdAbstractElement* element, std::string nodeName)
{
  if(element->getAttributesMap().contains(nodeName))
    return element->getAttributesMap().at(nodeName);
  return std::nullopt;
}
