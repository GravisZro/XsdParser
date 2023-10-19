#include "XsdExtension.h"

#include <core/utils/CommonOperations.h>

#include <xsdelements/XsdBuiltInDataType.h>
#include <xsdelements/XsdElement.h>
#include <xsdelements/XsdComplexType.h>
#include <xsdelements/XsdSimpleType.h>

#include <xsdelements/visitors/XsdExtensionVisitor.h>

#include <xsdelements/elementswrapper/NamedConcreteElement.h>
#include <xsdelements/elementswrapper/UnsolvedReference.h>

#include <xsdelements/exceptions/ParsingException.h>
#include <xsdelements/XsdAll.h>

#include <core/XsdParserCore.h>


XsdExtension::XsdExtension(std::shared_ptr<XsdParserCore> parser, StringMap attributesMap, VisitorFunctionReference visitorFunction)
    : XsdAnnotatedElements(parser, attributesMap, visitorFunction)
{
    if (attributesMap.contains(*BASE_TAG))
    {
      std::string baseValue = attributesMap.at(*BASE_TAG);

        if (XsdParserCore::getXsdTypesToJava().contains(baseValue))
        {
            StringMap attributes;
            attributes.emplace(NAME_TAG, baseValue);
            m_base = ReferenceBase::createFromXsd(std::make_shared<XsdBuiltInDataType>(parser, attributes, std::shared_ptr<XsdExtension>(this)));
        }
        else
        {
            auto parseMappers = XsdParserCore::getParseMappers();
            ConfigEntryData config;

            if(parseMappers.contains(*XsdElement::XSD_TAG))
              config = parseMappers.at(*XsdElement::XSD_TAG);
            else if(parseMappers.contains(*XsdElement::XS_TAG))
              config = parseMappers.at(*XsdElement::XS_TAG);

            if (!config.parserFunction || !config.visitorFunction)
                throw new ParsingException("Invalid Parsing Configuration for XsdElement.");

            m_base = std::make_shared<UnsolvedReference>(baseValue, std::make_shared<XsdElement>(std::shared_ptr<XsdAbstractElement>(this), m_parser, StringMap{}, config.visitorFunction));
            m_parser->addUnsolvedReference(std::static_pointer_cast<UnsolvedReference>(m_base));
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

    std::static_pointer_cast<XsdExtensionVisitor>(m_visitor)->replaceUnsolvedAttributes(m_parser, element, std::shared_ptr<XsdExtension>(this));
}

/**
 * Performs a copy of the current object for replacing purposes. The cloned objects are used to replace
 * {@link UnsolvedReference} objects in the reference solving process.
 * @param placeHolderAttributes The additional attributes to add to the clone.
 * @return A copy of the object from which is called upon.
 */
std::shared_ptr<XsdExtension> XsdExtension::clone(StringMap placeHolderAttributes)
{
    placeHolderAttributes.merge(m_attributesMap);

    auto elementCopy = std::make_shared<XsdExtension>(m_parser, placeHolderAttributes, m_visitorFunction);

    for(auto& attribute : getXsdAttributes())
    {
        elementCopy->m_visitor->visit(std::static_pointer_cast<XsdAttribute>(attribute->clone(attribute->getAttributesMap(), elementCopy)));
    }

    for(auto& attributeGroup : getXsdAttributeGroup())
    {
        elementCopy->m_visitor->visit(std::static_pointer_cast<XsdAttributeGroup>(attributeGroup->clone(attributeGroup->getAttributesMap(), elementCopy)));
    }

    elementCopy->m_childElement = ReferenceBase::clone(m_parser, m_childElement, elementCopy);
    elementCopy->m_base = m_base;
    elementCopy->m_cloneOf = std::shared_ptr<XsdAbstractElement>(this);
    elementCopy->m_parent = nullptr;

    return elementCopy;
}

/**
 * @return Its children elements as his own.
 */
std::list<std::shared_ptr<ReferenceBase>> XsdExtension::getElements(void)
{
  if(m_childElement)
    return m_childElement->getElement()->getElements();
  return {};
}

/**
 * @return Either a {@link XsdComplexType} or a {@link XsdSimpleType} from which this extension extends or null if
 * the {@link XsdParserCore} wasn't able to replace the {@link UnsolvedReference} created by the base attribute value.
 */
std::shared_ptr<XsdNamedElements> XsdExtension::getBase(void)
{
  if(auto x = std::dynamic_pointer_cast<NamedConcreteElement>(m_base))
    return x->getElement();
  return nullptr;
}

/**
 * @return The {@link XsdComplexType} from which this extension extends or null if the {@link XsdParserCore} wasn't
 * able to replace the {@link UnsolvedReference} created by the base attribute value.
 */
std::shared_ptr<XsdComplexType> XsdExtension::getBaseAsComplexType(void)
{
if (std::dynamic_pointer_cast<NamedConcreteElement>(m_base))
  if(auto x = std::dynamic_pointer_cast<XsdComplexType>(m_base->getElement()); x)
    return x;
return nullptr;
}

/**
 * @return The {@link XsdSimpleType} from which this extension extends or null if the {@link XsdParserCore} wasn't
 * able to replace the {@link UnsolvedReference} created by the base attribute value.
 */
std::shared_ptr<XsdSimpleType> XsdExtension::getBaseAsSimpleType(void)
{
if (std::dynamic_pointer_cast<NamedConcreteElement>(m_base))
  if(auto x = std::dynamic_pointer_cast<XsdSimpleType>(m_base->getElement()); x)
    return x;
return nullptr;
}

/**
 * @return The {@link XsdBuiltInDataType} from which this extension extends.
 */
std::shared_ptr<XsdBuiltInDataType> XsdExtension::getBaseAsBuiltInDataType(void)
{
if (std::dynamic_pointer_cast<NamedConcreteElement>(m_base))
  if(auto x = std::dynamic_pointer_cast<XsdBuiltInDataType>(m_base->getElement()); x)
    return x;
return nullptr;
}

std::shared_ptr<ReferenceBase> XsdExtension::parse(ParseData parseData)
{
    return xsdParseSkeleton(parseData.node, std::static_pointer_cast<XsdAbstractElement>(std::make_shared<XsdExtension>(parseData.parserInstance, XsdAbstractElement::getAttributesMap(parseData.node), parseData.visitorFunction)));
}

std::list<std::shared_ptr<XsdAttribute>> XsdExtension::getXsdAttributes(void) {
    return std::static_pointer_cast<XsdExtensionVisitor>(m_visitor)->getXsdAttributes();
}

std::list<std::shared_ptr<XsdAttributeGroup>> XsdExtension::getXsdAttributeGroup(void) {
    return std::static_pointer_cast<XsdExtensionVisitor>(m_visitor)->getXsdAttributeGroups();
}

std::shared_ptr<XsdAbstractElement> XsdExtension::getXsdChildElement()
{
  if (m_childElement &&
      std::dynamic_pointer_cast<UnsolvedReference>(m_childElement) == nullptr)
    return m_childElement->getElement();
  return nullptr;
}

/**
 * @return The childElement as a {@link XsdGroup} object or null if childElement isn't a {@link XsdGroup} instance.
 */
std::shared_ptr<XsdGroup> XsdExtension::getChildAsGroup(void)
{
  return std::dynamic_pointer_cast<XsdGroup>(m_childElement->getElement());
}

/**
 * @return The childElement as a {@link XsdAll} object or null if childElement isn't a {@link XsdAll} instance.
 */
std::shared_ptr<XsdAll> XsdExtension::getChildAsAll(void)
{
  if(std::dynamic_pointer_cast<XsdMultipleElements>(m_childElement->getElement()))
    return XsdMultipleElements::getChildAsAll(std::static_pointer_cast<XsdMultipleElements>(m_childElement->getElement()));
  return nullptr;
}

/**
 * @return The childElement as a {@link XsdChoice} object or null if childElement isn't a {@link XsdChoice} instance.
 */
std::shared_ptr<XsdChoice> XsdExtension::getChildAsChoice(void)
{
  if(std::dynamic_pointer_cast<XsdMultipleElements>(m_childElement->getElement()))
    return XsdMultipleElements::getChildAsChoice(std::static_pointer_cast<XsdMultipleElements>(m_childElement->getElement()));
  return nullptr;
}

/**
 * @return The childElement as a {@link XsdSequence} object or null if childElement isn't a {@link XsdSequence} instance.
 */
std::shared_ptr<XsdSequence> XsdExtension::getChildAsSequence(void)
{
  if(std::dynamic_pointer_cast<XsdMultipleElements>(m_childElement->getElement()))
    return XsdMultipleElements::getChildAsSequence(std::static_pointer_cast<XsdMultipleElements>(m_childElement->getElement()));
  return nullptr;
}
