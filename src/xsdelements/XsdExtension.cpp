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


XsdExtension::XsdExtension(std::shared_ptr<XsdParserCore> parser,
                           StringMap attributesMap,
                           VisitorFunctionReference visitorFunction,
                           std::shared_ptr<XsdAbstractElement> parent)
    : XsdAnnotatedElements(parser, attributesMap, visitorFunction, parent)
{ }

void XsdExtension::initialize(void)
{
  XsdAnnotatedElements::initialize();
    if (haveAttribute(BASE_TAG))
    {
      std::string baseValue = getAttribute(BASE_TAG);

        if (XsdParserCore::getXsdTypesToJava().contains(baseValue))
        {
            StringMap attributes;
            attributes.emplace(NAME_TAG, baseValue);
            m_base = ReferenceBase::createFromXsd(
                       create<XsdBuiltInDataType>(getParser(),
                         attributes,
                         shared_from_this()));
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
std::shared_ptr<XsdExtension> XsdExtension::clone(StringMap placeHolderAttributes)
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
                attribute->clone(
                  attribute->getAttributesMap(),
                  elementCopy)));
    }

    for(auto& attributeGroup : getXsdAttributeGroup())
    {
        elementCopy->getVisitor()->visit(
              std::static_pointer_cast<XsdAttributeGroup>(
                attributeGroup->clone(
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
    return xsdParseSkeleton(parseData.node,
                            std::static_pointer_cast<XsdAbstractElement>(
                              create<XsdExtension>(parseData.parserInstance,
                                                   getAttributesMap(parseData.node),
                                                   parseData.visitorFunction,
                                                   nullptr)));
}

std::list<std::shared_ptr<XsdAttribute>> XsdExtension::getXsdAttributes(void) {
    return std::static_pointer_cast<XsdExtensionVisitor>(getVisitor())->getXsdAttributes();
}

std::list<std::shared_ptr<XsdAttributeGroup>> XsdExtension::getXsdAttributeGroup(void) {
    return std::static_pointer_cast<XsdExtensionVisitor>(getVisitor())->getXsdAttributeGroups();
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
