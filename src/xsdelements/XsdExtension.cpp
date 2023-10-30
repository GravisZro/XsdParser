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

XsdExtension::XsdExtension(StringMap attributesMap,
                           VisitorFunctionType visitorFunction,
                           XsdAbstractElement* parent)
  : XsdAnnotatedElements(attributesMap, visitorFunction, parent),
    m_childElement(nullptr),
    m_base(nullptr)
{
  if (hasAttribute(BASE_TAG))
  {
    std::string baseValue = getAttribute(BASE_TAG);
    const auto& typeMap = XsdParserCore::getXsdTypesToCpp();

    if (typeMap.contains(baseValue))
    {
      StringMap attributes;
      attributes.emplace(NAME_TAG, baseValue);
      m_base = ReferenceBase::createFromXsd(
                 new XsdBuiltInDataType(attributes,
                                            nullptr,
                                            this));
    }
    else
    {
      const auto& parseMappers = XsdParserCore::getParseMappers();
      ConfigEntryData configEntryData;

      if(parseMappers.contains(TAG<XsdElement>::xsd))
        configEntryData = parseMappers.at(TAG<XsdElement>::xsd);
      else if(parseMappers.contains(TAG<XsdElement>::xs))
        configEntryData = parseMappers.at(TAG<XsdElement>::xs);

      if (configEntryData.parserFunction == nullptr || configEntryData.visitorFunction == nullptr)
        throw ParsingException("Invalid Parsing Configuration for XsdElement.");

      m_base = new UnsolvedReference(baseValue,
                                     new XsdElement(StringMap{},
                                                    configEntryData.visitorFunction,
                                                    this));
      getParser()->addUnsolvedReference(static_cast<UnsolvedReference*>(m_base));
    }
  }
}

XsdExtension::~XsdExtension(void)
{
  if(m_childElement != nullptr)
    delete m_childElement, m_childElement = nullptr;

  if(m_base != nullptr)
    delete m_base, m_base = nullptr;
}

/**
 * This method should always receive two elements, one to replace the {@link UnsolvedReference} created due to
 * the value present in the base attribute and another if it has an {@link UnsolvedReference} as a child element.
 * @param element A concrete element with a name that will replace the {@link UnsolvedReference} object created in the
 *                {@link XsdExtension} constructor. The {@link UnsolvedReference} is only replaced if there
 *                is a match between the {@link UnsolvedReference#ref} and the {@link NamedConcreteElement#name}.
 */
void XsdExtension::replaceUnsolvedElements(NamedConcreteElement* elementWrapper)
{
  XsdAnnotatedElements::replaceUnsolvedElements(elementWrapper);

  auto element = elementWrapper->getElement();

  bool isComplexOrSimpleType = dynamic_cast<XsdComplexType*>(element) != nullptr ||
                               dynamic_cast<XsdSimpleType*>(element) != nullptr;

  if (auto x = dynamic_cast<UnsolvedReference*>(m_base);
      x != nullptr &&
      isComplexOrSimpleType &&
      compareReference(elementWrapper, x))
    m_base = elementWrapper;


  if (auto x = dynamic_cast<UnsolvedReference*>(m_base);
      x != nullptr &&
      dynamic_cast<XsdGroup*>(m_base) != nullptr &&
      compareReference(elementWrapper, x))
    m_childElement = elementWrapper;

  static_cast<XsdExtensionVisitor*>(getVisitor())->replaceUnsolvedAttributes(elementWrapper, this);
}

/**
 * Performs a copy of the current object for replacing purposes. The cloned objects are used to replace
 * {@link UnsolvedReference} objects in the reference solving process.
 * @param placeHolderAttributes The additional attributes to add to the clone.
 * @return A copy of the object from which is called upon.
 */
XsdExtension::XsdExtension(const XsdExtension& other)
 : XsdExtension(other.getAttributesMap(), other.m_visitorFunction, nullptr)
{
  for(auto& attribute : other.getXsdAttributes())
    getVisitor()->visit(new XsdAttribute(attribute->getAttributesMap(), nullptr, this));

  for(auto& attributeGroup : other.getXsdAttributeGroup())
    getVisitor()->visit(new XsdAttributeGroup(attributeGroup->getAttributesMap(), nullptr, this));

  m_childElement = new ReferenceBase(m_childElement, this);
  m_base = other.m_base;
  setCloneOf(&other);
}

/**
 * @return Its children elements as his own.
 */
std::list<ReferenceBase*> XsdExtension::getElements(void) const
{
  if(m_childElement)
    return m_childElement->getElement()->getElements();
  return {};
}

std::list<XsdAttribute*> XsdExtension::getXsdAttributes(void) const
{
  return static_cast<XsdExtensionVisitor*>(getVisitor())->getXsdAttributes();
}

std::list<XsdAttributeGroup*> XsdExtension::getXsdAttributeGroup(void) const
{
  return static_cast<XsdExtensionVisitor*>(getVisitor())->getXsdAttributeGroups();
}

XsdAbstractElement* XsdExtension::getXsdChildElement(void) const
{
  if (m_childElement != nullptr &&
      dynamic_cast<UnsolvedReference*>(m_childElement) == nullptr)
    return m_childElement->getElement();
  return nullptr;
}
