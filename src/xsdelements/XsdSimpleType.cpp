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



/**
 * Updates the existing {@link XsdRestriction} with the restrictions of the new {@link XsdRestriction} instance.
 * @param existing The existing {@link XsdRestriction} instance.
 * @param newRestriction The new {@link XsdRestriction} instance.
 */
static void updateExistingRestrictionEnumerations(
    XsdRestriction* existing,
    XsdRestriction* newRestriction)
{
  std::list<XsdEnumeration*> existingEnumeration = existing->getEnumeration();
  std::list<XsdEnumeration*> newRestrictionEnumeration = newRestriction->getEnumeration();

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

/**
 * Joins two distinct {@link XsdRestriction} instances. This method assumes that the information of both
 * {@link XsdRestriction} objects don't have overlapping or contradictory information.
 * @param existing The existing restriction.
 * @param newRestriction The new restriction.
 */
static void updateExistingRestriction(
    XsdRestriction* existing,
    XsdRestriction* newRestriction)
{
  XsdPattern*         pattern         = newRestriction->getPattern();
  XsdMaxExclusive*    maxExclusive    = newRestriction->getMaxExclusive();
  XsdMaxInclusive*    maxInclusive    = newRestriction->getMaxInclusive();
  XsdMaxLength*       maxLength       = newRestriction->getMaxLength();
  XsdMinExclusive*    minExclusive    = newRestriction->getMinExclusive();
  XsdMinInclusive*    minInclusive    = newRestriction->getMinInclusive();
  XsdMinLength*       minLength       = newRestriction->getMinLength();
  XsdLength*          length          = newRestriction->getLength();
  XsdFractionDigits*  fractionDigits  = newRestriction->getFractionDigits();
  XsdTotalDigits*     totalDigits     = newRestriction->getTotalDigits();
  XsdWhiteSpace*      whiteSpace      = newRestriction->getWhiteSpace();

  if (pattern != nullptr)
    existing->setPattern(pattern);

  if (maxExclusive != nullptr)
    existing->setMaxExclusive(maxExclusive);

  if (maxInclusive != nullptr)
    existing->setMaxInclusive(maxInclusive);

  if (maxLength != nullptr)
    existing->setMaxLength(maxLength);

  if (minExclusive != nullptr)
    existing->setMinExclusive(minExclusive);

  if (minInclusive != nullptr)
    existing->setMinInclusive(minInclusive);

  if (minLength != nullptr)
    existing->setMinLength(minLength);

  if (length != nullptr)
    existing->setLength(length);

  if (fractionDigits != nullptr)
    existing->setFractionDigits(fractionDigits);

  if (totalDigits != nullptr)
    existing->setTotalDigits(totalDigits);

  if (whiteSpace != nullptr)
    existing->setWhiteSpace(whiteSpace);

  updateExistingRestrictionEnumerations(existing, newRestriction);
}

template<typename T>
constexpr bool hasDifferentValue(T* existing, T* newRestriction)
{
  if (existing != nullptr && newRestriction != nullptr)
    return existing->getValue() != newRestriction->getValue();
  return bool(existing != nullptr) != bool(newRestriction != nullptr);
}


/**
 * Checks for any restriction overlap between two different {@link XsdRestriction} instances.
 * @param existing The existing restriction.
 * @param newRestriction The second restriction found.
 * @return True if an overlap between the restrictions occur, false if it doesn't occur.
 */
static bool existsRestrictionOverlap(
    XsdRestriction* existing,
    XsdRestriction* newRestriction)
{
  return hasDifferentValue(existing->getPattern()       , newRestriction->getPattern()        ) ||
      hasDifferentValue(existing->getWhiteSpace()    , newRestriction->getWhiteSpace()     ) ||
      hasDifferentValue(existing->getTotalDigits()   , newRestriction->getTotalDigits()    ) ||
      hasDifferentValue(existing->getFractionDigits(), newRestriction->getFractionDigits() ) ||
      hasDifferentValue(existing->getMaxExclusive()  , newRestriction->getMaxExclusive()   ) ||
      hasDifferentValue(existing->getMaxInclusive()  , newRestriction->getMaxInclusive()   ) ||
      hasDifferentValue(existing->getMaxLength()     , newRestriction->getMaxLength()      ) ||
      hasDifferentValue(existing->getMinExclusive()  , newRestriction->getMinExclusive()   ) ||
      hasDifferentValue(existing->getMinInclusive()  , newRestriction->getMinInclusive()   ) ||
      hasDifferentValue(existing->getMinLength()     , newRestriction->getMinLength()      ) ||
      hasDifferentValue(existing->getLength()        , newRestriction->getLength()         );
}


/**
 * Performs a copy of the current object for replacing purposes. The cloned objects are used to replace
 * {@link UnsolvedReference} objects in the reference solving process.
 * @param placeHolderAttributes The additional attributes to add to the clone.
 * @return A copy of the object from which is called upon.
 */
XsdSimpleType::XsdSimpleType(const XsdSimpleType& other, XsdAbstractElement* parent)
  : XsdSimpleType(other.getAttributesMap(), other.m_visitorFunction, parent)
{
  removeAttribute(REF_TAG);

  if (other.m_xsd_union != nullptr)
    m_xsd_union = new XsdUnion(*other.m_xsd_union, this);

  if (other.m_xsd_list != nullptr)
    m_xsd_list = new XsdList(*other.m_xsd_list, this);

  if (other.m_restriction != nullptr)
    m_restriction = new XsdRestriction(*other.m_restriction, this);
}

XsdList* XsdSimpleType::getList(void) const
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
std::list<XsdRestriction*> XsdSimpleType::getAllRestrictions(void) const
{
  std::map<std::string, XsdRestriction*> restrictions;
  StringMap xsdBuiltinTypes = XsdParserCore::getXsdTypesToCpp();

  if (m_restriction != nullptr && m_restriction->getBaseType())
    restrictions.emplace(xsdBuiltinTypes.at(m_restriction->getBaseType().value()), m_restriction);

  if (m_xsd_union != nullptr)
  {
    for(auto& unionMember :  m_xsd_union->getUnionElements())
    {
      auto unionMemberRestriction = unionMember->getRestriction();
      if (unionMemberRestriction != nullptr)
      {
        assert(unionMemberRestriction->getBaseType());
        assert(xsdBuiltinTypes.contains(unionMemberRestriction->getBaseType().value()));


        XsdRestriction* existingRestriction = nullptr;
        if(restrictions.contains(xsdBuiltinTypes.at(unionMemberRestriction->getBaseType().value())))
          existingRestriction = restrictions.at(xsdBuiltinTypes.at(unionMemberRestriction->getBaseType().value()));

        if(existingRestriction != nullptr)
        {
          if (existsRestrictionOverlap(existingRestriction, unionMemberRestriction))
            throw std::runtime_error("The xsd file is invalid because has contradictory restrictions.");
          updateExistingRestriction(existingRestriction, unionMemberRestriction);
        }
        else
          restrictions.emplace(xsdBuiltinTypes.at(unionMemberRestriction->getBaseType().value()), unionMemberRestriction);
      }
    }
  }

  std::list<XsdRestriction*> rvals;
  for(auto& pair : restrictions)
    rvals.push_back(pair.second);
  return rvals;
}

