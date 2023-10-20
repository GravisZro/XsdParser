#include "XsdSimpleType.h"

#include <xsdelements/xsdrestrictions/XsdEnumeration.h>
#include <xsdelements/xsdrestrictions/XsdFractionDigits.h>
#include <xsdelements/xsdrestrictions/XsdIntegerRestrictions.h>
#include <xsdelements/xsdrestrictions/XsdLength.h>
#include <xsdelements/xsdrestrictions/XsdMaxExclusive.h>
#include <xsdelements/xsdrestrictions/XsdMaxInclusive.h>
#include <xsdelements/xsdrestrictions/XsdMaxLength.h>
#include <xsdelements/xsdrestrictions/XsdMinExclusive.h>
#include <xsdelements/xsdrestrictions/XsdMinInclusive.h>
#include <xsdelements/xsdrestrictions/XsdMinLength.h>
#include <xsdelements/xsdrestrictions/XsdPattern.h>
#include <xsdelements/xsdrestrictions/XsdStringRestrictions.h>
#include <xsdelements/xsdrestrictions/XsdTotalDigits.h>
#include <xsdelements/xsdrestrictions/XsdWhiteSpace.h>

#include <xsdelements/XsdAnnotatedElements.h>
#include <xsdelements/XsdSchema.h>
#include <xsdelements/XsdUnion.h>
#include <xsdelements/XsdList.h>
#include <xsdelements/XsdRestriction.h>

#include <core/XsdParserCore.h>


XsdSimpleType::XsdSimpleType(std::shared_ptr<XsdParserCore> parser,
              StringMap attributesMap,
              VisitorFunctionReference visitorFunction)
  : XsdNamedElements(parser, attributesMap, visitorFunction)
{
    std::string finalDefault = AttributeValidations::getFinalDefaultValue(m_parent);

    m_finalObj = AttributeValidations::belongsToEnum<SimpleTypeFinalEnum>(attributesMap.contains(*FINAL_TAG) ? attributesMap.at(*FINAL_TAG) : finalDefault);
}

XsdSimpleType::XsdSimpleType(std::shared_ptr<XsdAbstractElement> parent,
                             std::shared_ptr<XsdParserCore> parser,
                             StringMap elementFieldsMapParam,
                             VisitorFunctionReference visitorFunction)
  : XsdSimpleType(parser, elementFieldsMapParam, visitorFunction)
{
    setParent(parent);
}

/**
 * Runs verifications on each concrete element to ensure that the XSD schema rules are verified.
 */
void XsdSimpleType::validateSchemaRules(void)
{
    XsdNamedElements::validateSchemaRules();

    rule2();
    rule3();
}

/**
 * Asserts that the current object has the required name attribute when not being a direct child of the XsdSchema element.
 * Throws an exception if the required attribute is not present.
 */
void XsdSimpleType::rule2(void)
{
    if (std::dynamic_pointer_cast<XsdSchema>(m_parent) == nullptr && m_name)
        throw ParsingException(XSD_TAG + " element: The " + NAME_TAG + " should only be used when the parent of the " + XSD_TAG + " is the " + XsdSchema::XSD_TAG + " element.");
}

/**
 * Asserts if the current has no value for its name attribute while being a direct child of the top level XsdSchema element,
 * which is required. Throws an exception if no name is present.
 */
void XsdSimpleType::rule3(void)
{
    if (std::dynamic_pointer_cast<XsdSchema>(m_parent) && !m_name)
        throw ParsingException(XSD_TAG + " element: The " + NAME_TAG + " should is required the parent of the " + XSD_TAG + " is the " + XsdSchema::XSD_TAG + " element.");
}

void XsdSimpleType::accept(std::shared_ptr<XsdAbstractElementVisitor> visitorParam)
{
    XsdNamedElements::accept(visitorParam);
    visitorParam->visit(nondeleted_ptr<XsdSimpleType>(this));
}

/**
 * Performs a copy of the current object for replacing purposes. The cloned objects are used to replace
 * {@link UnsolvedReference} objects in the reference solving process.
 * @param placeHolderAttributes The additional attributes to add to the clone.
 * @return A copy of the object from which is called upon.
 */
std::shared_ptr<XsdSimpleType> XsdSimpleType::clone(StringMap placeHolderAttributes)
{
    placeHolderAttributes.merge(m_attributesMap);
    placeHolderAttributes.erase(*REF_TAG);

    auto elementCopy = std::make_shared<XsdSimpleType>(m_parent, getParser(), placeHolderAttributes, m_visitorFunction);

    if (m_xsd_union)
        elementCopy->m_xsd_union = std::static_pointer_cast<XsdUnion>(m_xsd_union->clone(m_xsd_union->getAttributesMap(), elementCopy));

    if (m_xsd_list)
        elementCopy->m_xsd_list = std::static_pointer_cast<XsdList>(m_xsd_list->clone(m_xsd_list->getAttributesMap(), elementCopy));

    if (m_restriction)
        elementCopy->m_restriction = std::static_pointer_cast<XsdRestriction>(m_restriction->clone(m_restriction->getAttributesMap(), elementCopy));

    return elementCopy;
}

std::shared_ptr<ReferenceBase> XsdSimpleType::parse(ParseData parseData)
{
    return xsdParseSkeleton(parseData.node, std::static_pointer_cast<XsdAbstractElement>(std::make_shared<XsdSimpleType>(parseData.parserInstance, XsdAbstractElement::getAttributesMap(parseData.node), parseData.visitorFunction)));
}


std::shared_ptr<XsdList> XsdSimpleType::getList(void)
{
    if (!m_xsd_list && m_xsd_union)
      for(auto& xsdSimpleType : m_xsd_union->getUnionElements())
        if(xsdSimpleType->m_xsd_list)
          return xsdSimpleType->m_xsd_list;
    return m_xsd_list;
}

/**
 * This method obtains all the restrictions for the current {@link XsdSimpleType} element. It also joins multiple
 * restrictions with the same base attribute in the same {@link XsdRestriction} object, if a overlap doesn't occur.
 * In case of restriction overlap an exception is thrown because the information on the xsd file is contradictory.
 * @return A xsd_list of restrictions.
 */
std::list<std::shared_ptr<XsdRestriction>> XsdSimpleType::getAllRestrictions(void)
{
    std::map<std::string, std::shared_ptr<XsdRestriction>> restrictions;
    StringMap xsdBuiltinTypes = XsdParserCore::getXsdTypesToJava();

    if (m_restriction && m_restriction->getBase())
    {
        restrictions.emplace(xsdBuiltinTypes.at(m_restriction->getBase().value()), m_restriction);
    }

    if (m_xsd_union)
    {
      for(auto& unionMember :  m_xsd_union->getUnionElements())
      {
        auto unionMemberRestriction = unionMember->getRestriction();
        if (unionMemberRestriction)
        {
          assert(unionMemberRestriction->getBase());
          assert(xsdBuiltinTypes.contains(unionMemberRestriction->getBase().value()));


          std::shared_ptr<XsdRestriction> existingRestriction;
          if(restrictions.contains(xsdBuiltinTypes.at(unionMemberRestriction->getBase().value())))
             existingRestriction = restrictions.at(xsdBuiltinTypes.at(unionMemberRestriction->getBase().value()));

          if(existingRestriction)
          {
            if (existsRestrictionOverlap(existingRestriction, unionMemberRestriction))
              throw std::runtime_error("The xsd file is invalid because has contradictory restrictions.");
            updateExistingRestriction(existingRestriction, unionMemberRestriction);
          }
          else
            restrictions.emplace(xsdBuiltinTypes.at(unionMemberRestriction->getBase().value()), unionMemberRestriction);
        }
      }
    }

    std::list<std::shared_ptr<XsdRestriction>> rvals;
    for(auto& pair : restrictions)
      rvals.push_back(pair.second);
    return rvals;
}

/**
 * Joins two distinct {@link XsdRestriction} instances. This method assumes that the information of both
 * {@link XsdRestriction} objects don't have overlapping or contradictory information.
 * @param existing The existing restriction.
 * @param newRestriction The new restriction.
 */
void XsdSimpleType::updateExistingRestriction(std::shared_ptr<XsdRestriction> existing,
                                              std::shared_ptr<XsdRestriction> newRestriction)
{
    std::shared_ptr<XsdPattern> pattern = newRestriction->getPattern();
    std::shared_ptr<XsdMaxExclusive> maxExclusive = newRestriction->getMaxExclusive();
    std::shared_ptr<XsdMaxInclusive> maxInclusive = newRestriction->getMaxInclusive();
    std::shared_ptr<XsdMaxLength> maxLength = newRestriction->getMaxLength();
    std::shared_ptr<XsdMinExclusive> minExclusive = newRestriction->getMinExclusive();
    std::shared_ptr<XsdMinInclusive> minInclusive = newRestriction->getMinInclusive();
    std::shared_ptr<XsdMinLength> minLength = newRestriction->getMinLength();
    std::shared_ptr<XsdLength> length = newRestriction->getLength();
    std::shared_ptr<XsdFractionDigits> fractionDigits = newRestriction->getFractionDigits();
    std::shared_ptr<XsdTotalDigits> totalDigits = newRestriction->getTotalDigits();
    std::shared_ptr<XsdWhiteSpace> whiteSpace = newRestriction->getWhiteSpace();

    if (pattern)
        existing->setPattern(pattern);

    if (maxExclusive)
        existing->setMaxExclusive(maxExclusive);

    if (maxInclusive)
        existing->setMaxInclusive(maxInclusive);

    if (maxLength)
        existing->setMaxLength(maxLength);

    if (minExclusive)
        existing->setMinExclusive(minExclusive);

    if (minInclusive)
        existing->setMinInclusive(minInclusive);

    if (minLength)
        existing->setMinLength(minLength);

    if (length)
        existing->setLength(length);

    if (fractionDigits)
        existing->setFractionDigits(fractionDigits);

    if (totalDigits)
        existing->setTotalDigits(totalDigits);

    if (whiteSpace)
        existing->setWhiteSpace(whiteSpace);

    updateExistingRestrictionEnumerations(existing, newRestriction);
}

/**
 * Updates the existing {@link XsdRestriction} with the restrictions of the new {@link XsdRestriction} instance.
 * @param existing The existing {@link XsdRestriction} instance.
 * @param newRestriction The new {@link XsdRestriction} instance.
 */
void XsdSimpleType::updateExistingRestrictionEnumerations(std::shared_ptr<XsdRestriction> existing, std::shared_ptr<XsdRestriction> newRestriction)
{
  std::list<std::shared_ptr<XsdEnumeration>> existingEnumeration = existing->getEnumeration();
  std::list<std::shared_ptr<XsdEnumeration>> newRestrictionEnumeration = newRestriction->getEnumeration();

  if(!existingEnumeration.empty())
    existing->setEnumeration(newRestrictionEnumeration);
  else
    for (auto& enumerationElem : newRestrictionEnumeration)
    {
      bool found = false;
      for (auto& existingEnumerationElem : existingEnumeration)
        if(existingEnumerationElem->getValue() == enumerationElem->getValue())
        {
          found = true;
          break;
        }
      if(!found)
        existingEnumeration.push_back(enumerationElem);
    }
}

template<typename T, std::enable_if_t<std::is_base_of_v<XsdIntegerRestrictions, T>, bool> = true>
constexpr bool hasDifferentValue(std::shared_ptr<T> existing, std::shared_ptr<T> newRestriction)
{
  return XsdIntegerRestrictions::hasDifferentValue(std::static_pointer_cast<XsdIntegerRestrictions>(existing),
                                                   std::static_pointer_cast<XsdIntegerRestrictions>(newRestriction));
}

template<typename T, std::enable_if_t<std::is_base_of_v<XsdStringRestrictions, T>, bool> = true>
constexpr bool hasDifferentValue(std::shared_ptr<T> existing, std::shared_ptr<T> newRestriction)
{
  return XsdStringRestrictions::hasDifferentValue(std::static_pointer_cast<XsdStringRestrictions>(existing),
                                                   std::static_pointer_cast<XsdStringRestrictions>(newRestriction));
}

template<typename T, std::enable_if_t<std::is_base_of_v<XsdWhiteSpace, T>, bool> = true>
constexpr bool hasDifferentValue(std::shared_ptr<T> existing, std::shared_ptr<T> newRestriction)
{
  return XsdWhiteSpace::hasDifferentValue(std::static_pointer_cast<XsdWhiteSpace>(existing),
                                          std::static_pointer_cast<XsdWhiteSpace>(newRestriction));
}

/**
 * Checks for any restriction overlap between two different {@link XsdRestriction} instances.
 * @param existing The existing restriction.
 * @param newRestriction The second restriction found.
 * @return True if an overlap between the restrictions occur, false if it doesn't occur.
 */
bool XsdSimpleType::existsRestrictionOverlap(std::shared_ptr<XsdRestriction> existing, std::shared_ptr<XsdRestriction> newRestriction)
{
    return hasDifferentValue(existing->getPattern(), newRestriction->getPattern()) ||
           hasDifferentValue(existing->getWhiteSpace(), newRestriction->getWhiteSpace()) ||
           hasDifferentValue(existing->getTotalDigits(), newRestriction->getTotalDigits()) ||
           hasDifferentValue(existing->getFractionDigits(), newRestriction->getFractionDigits()) ||
           hasDifferentValue(existing->getMaxExclusive(), newRestriction->getMaxExclusive()) ||
           hasDifferentValue(existing->getMaxInclusive(), newRestriction->getMaxInclusive()) ||
           hasDifferentValue(existing->getMaxLength(), newRestriction->getMaxLength()) ||
           hasDifferentValue(existing->getMinExclusive(), newRestriction->getMinExclusive()) ||
           hasDifferentValue(existing->getMinInclusive(), newRestriction->getMinInclusive()) ||
           hasDifferentValue(existing->getMinLength(), newRestriction->getMinLength()) ||
           hasDifferentValue(existing->getLength(), newRestriction->getLength());
}
