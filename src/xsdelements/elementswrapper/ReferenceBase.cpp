#include "ReferenceBase.h"

#include <core/XsdParserCore.h>
#include <xsdelements/XsdNamedElements.h>
#include <xsdelements/elementswrapper/ConcreteElement.h>
#include <xsdelements/elementswrapper/NamedConcreteElement.h>
#include <xsdelements/elementswrapper/UnsolvedReference.h>
#include <xsdelements/XsdAbstractElement.h>


ReferenceBase::ReferenceBase(std::shared_ptr<XsdAbstractElement> element)
{
    m_element = element;
}

std::shared_ptr<XsdAbstractElement> ReferenceBase::getElement(void)
{ return m_element; }

/**
 * This method creates a ReferenceBase object that serves as a wrapper to {@link XsdAbstractElement} objects.
 * If a {@link XsdAbstractElement} has a ref attribute it results in a {@link UnsolvedReference} object. If it
 * doesn't have a ref attribute and has a name attribute it's a {@link NamedConcreteElement}. If it isn't a
 * {@link UnsolvedReference} or a {@link NamedConcreteElement} then it's a {@link ConcreteElement}.
 * @param element The element which will be "wrapped".
 * @return A wrapper object for the element received.
 */
std::shared_ptr<ReferenceBase> ReferenceBase::createFromXsd(std::shared_ptr<XsdAbstractElement> element)
{
  auto ref = getRef(element);
  auto name = getName(element);

  if(std::dynamic_pointer_cast<XsdNamedElements>(element) == nullptr)
    return std::make_shared<ConcreteElement>(element);

  if(!ref)
  {
    if (!name)
      return std::make_shared<ConcreteElement>(element);
    else
      return std::make_shared<NamedConcreteElement>(std::static_pointer_cast<XsdNamedElements>(element), name.value());
  }
  else
    return std::make_shared<UnsolvedReference>(std::static_pointer_cast<XsdNamedElements>(element));
}

std::shared_ptr<ReferenceBase> ReferenceBase::clone(std::shared_ptr<XsdParserCore> parser,
                                                    std::shared_ptr<ReferenceBase> originalReference,
                                                    std::shared_ptr<XsdAbstractElement> parent)
{
    if (!originalReference)
      return nullptr;

    std::shared_ptr<XsdAbstractElement> originalElement = originalReference->getElement();

    if (auto original = std::dynamic_pointer_cast<UnsolvedReference>(originalReference); original)
    {
      assert(original->getRef());
        StringMap originalElementAttributesMap = originalElement->getAttributesMap();
        StringMap clonedOriginalElementAttributesMap = originalElementAttributesMap;
        clonedOriginalElementAttributesMap.emplace(XsdAbstractElement::REF_TAG, original->getRef().value());

        std::shared_ptr<XsdNamedElements> clonedElement = std::static_pointer_cast<XsdNamedElements>(originalElement->clone(clonedOriginalElementAttributesMap));
        clonedElement->getAttributesMap().emplace(XsdAbstractElement::REF_TAG, original->getRef().value());
        clonedElement->setCloneOf(originalElement);
        clonedElement->setParent(parent);

        auto unsolvedClonedElement = std::make_shared<UnsolvedReference>(clonedElement);

        parser->addUnsolvedReference(unsolvedClonedElement);

        return unsolvedClonedElement;
    }
    else {
        originalReference->getElement()->setParentAvailable(false);

        return originalReference;

//            XsdAbstractElement cloneElement = originalElement->clone(originalElement->getAttributesMap());
//            cloneElement.setParent(parent);
//
//            return createFromXsd(cloneElement);
    }
}

std::optional<std::string> ReferenceBase::getName(std::shared_ptr<XsdAbstractElement> element)
{
    return getNodeValue(element, *XsdNamedElements::NAME_TAG);
}

std::optional<std::string> ReferenceBase::getRef(std::shared_ptr<XsdAbstractElement> element)
{
    return getNodeValue(element, *XsdAbstractElement::REF_TAG);
}

/**
 * @param element The element that contains the attributes.
 * @param nodeName The attribute name that will be searched.
 * @return The value of the attribute contained in element with the name nodeName.
 */
std::optional<std::string> ReferenceBase::getNodeValue(std::shared_ptr<XsdAbstractElement> element, std::string nodeName)
{
  if(element->getAttributesMap().contains(nodeName))
    return element->getAttributesMap().at(nodeName);
  return std::nullopt;
}
