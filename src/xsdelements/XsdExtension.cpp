#include "XsdExtension.h"

#include <core/utils/StringOperations.h>

#include <xsdelements/XsdBuiltInDataType.h>
#include <xsdelements/XsdElement.h>
#include <xsdelements/XsdComplexType.h>
#include <xsdelements/XsdSimpleType.h>

#include <xsdelements/visitors/XsdExtensionVisitor.h>

#include <xsdelements/elementswrapper/NamedConcreteElement.h>
#include <xsdelements/elementswrapper/UnsolvedReference.h>

#include <xsdelements/exceptions/ParsingException.h>

#include <xsdelements/XsdMultipleElements.h>
#include <xsdelements/XsdAll.h>
#include <xsdelements/XsdGroup.h>
#include <xsdelements/XsdChoice.h>
#include <xsdelements/XsdSequence.h>

#include <core/XsdParserCore.h>

void XsdExtension::initialize(void)
{
  XsdAnnotatedElements::initialize();
  m_childElement.reset();
  m_base.reset();

  if (haveAttribute(BASE_TAG))
  {
    std::string baseValue = getAttribute(BASE_TAG);

    if (XsdParserCore::getXsdTypesToCpp().contains(baseValue))
    {
      StringMap attributes;
      attributes.emplace(NAME_TAG, baseValue);
      m_base = ReferenceBase::createFromXsd(
                 create<XsdBuiltInDataType>(getParser(),
                                            attributes,
                                            nullptr,
                                            shared_from_this()));
    }
    else
    {
      auto parseMappers = XsdParserCore::getParseMappers();
      ConfigEntryData config;

      if(parseMappers.contains(TAG<XsdElement>::xsd))
        config = parseMappers.at(TAG<XsdElement>::xsd);
      else if(parseMappers.contains(TAG<XsdElement>::xs))
        config = parseMappers.at(TAG<XsdElement>::xs);

      if (config.parserFunction == nullptr || config.visitorFunction == nullptr)
        throw ParsingException("Invalid Parsing Configuration for XsdElement.");

      m_base = create<UnsolvedReference>(baseValue,
                                         create<XsdElement>(getParser(),
                                                            StringMap{},
                                                            config.visitorFunction,
                                                            shared_from_this()));
      getParser()->addUnsolvedReference(std::static_pointer_cast<UnsolvedReference>(m_base));
    }
  }
}

/**
 * This method should always receive two elements, one to replace the {@link UnsolvedReference} created due to
 * the value present in the base attribute and another if it has an {@link UnsolvedReference} as a child element.
 * @param element A concrete element with a name that will replace the {@link UnsolvedReference} object created in the
 *                {@link XsdExtension} constructor. The {@link UnsolvedReference} is only replaced if there
 *                is a match between the {@link UnsolvedReference#ref} and the {@link NamedConcreteElement#name}.
 */
void XsdExtension::replaceUnsolvedElements(std::shared_ptr<NamedConcreteElement> element)
{
  XsdAnnotatedElements::replaceUnsolvedElements(element);

  auto elem = element->getElement();

  bool isComplexOrSimpleType = std::dynamic_pointer_cast<XsdComplexType>(elem) ||
                               std::dynamic_pointer_cast<XsdSimpleType>(elem);

  if (auto x = std::dynamic_pointer_cast<UnsolvedReference>(m_base);
      x && isComplexOrSimpleType &&
      compareReference(element, x))
    m_base = element;


  if (auto x = std::dynamic_pointer_cast<UnsolvedReference>(m_base);
      x && std::dynamic_pointer_cast<XsdGroup>(m_base) &&
      compareReference(element, x))
    m_childElement = element;

  std::static_pointer_cast<XsdExtensionVisitor>(getVisitor())->replaceUnsolvedAttributes(
        getParser(),
        element,
        shared_from_this());
}

/**
 * Performs a copy of the current object for replacing purposes. The cloned objects are used to replace
 * {@link UnsolvedReference} objects in the reference solving process.
 * @param placeHolderAttributes The additional attributes to add to the clone.
 * @return A copy of the object from which is called upon.
 */
std::shared_ptr<XsdAbstractElement> XsdExtension::clone(StringMap placeHolderAttributes)
{
  placeHolderAttributes.merge(getAttributesMap());

  auto elementCopy = create<XsdExtension>(getParser(),
                                          placeHolderAttributes,
                                          m_visitorFunction,
                                          nullptr);

  for(auto& attribute : getXsdAttributes())
  {
    elementCopy->getVisitor()->visit(
          std::static_pointer_cast<XsdAttribute>(
            attribute->XsdAbstractElement::clone(
              attribute->getAttributesMap(),
              elementCopy)));
  }

  for(auto& attributeGroup : getXsdAttributeGroup())
  {
    elementCopy->getVisitor()->visit(
          std::static_pointer_cast<XsdAttributeGroup>(
            attributeGroup->XsdAbstractElement::clone(
              attributeGroup->getAttributesMap(),
              elementCopy)));
  }

  elementCopy->m_childElement = ReferenceBase::clone(getParser(), m_childElement, elementCopy);
  elementCopy->m_base = m_base;
  elementCopy->setCloneOf(shared_from_this());

  return elementCopy;
}

/**
 * @return Its children elements as his own.
 */
std::list<std::shared_ptr<ReferenceBase>> XsdExtension::getElements(void) const
{
  if(m_childElement)
    return m_childElement->getElement()->getElements();
  return {};
}

std::list<std::shared_ptr<XsdAttribute>> XsdExtension::getXsdAttributes(void) const
{
  return std::static_pointer_cast<XsdExtensionVisitor>(getVisitor())->getXsdAttributes();
}

std::list<std::shared_ptr<XsdAttributeGroup>> XsdExtension::getXsdAttributeGroup(void) const
{
  return std::static_pointer_cast<XsdExtensionVisitor>(getVisitor())->getXsdAttributeGroups();
}

std::shared_ptr<XsdAbstractElement> XsdExtension::getXsdChildElement(void) const
{
  if (m_childElement &&
      std::dynamic_pointer_cast<UnsolvedReference>(m_childElement) == nullptr)
    return m_childElement->getElement();
  return nullptr;
}
