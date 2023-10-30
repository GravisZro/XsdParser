#include "XsdRestriction.h"

#include <xsdelements/elementswrapper/UnsolvedReference.h>
#include <xsdelements/elementswrapper/NamedConcreteElement.h>

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

#include <xsdelements/XsdElement.h>
#include <xsdelements/XsdBuiltInDataType.h>
#include <xsdelements/visitors/XsdRestrictionVisitor.h>

#include <xsdelements/XsdComplexType.h>
#include <xsdelements/XsdSimpleType.h>
#include <xsdelements/XsdAll.h>
#include <xsdelements/XsdChoice.h>
#include <xsdelements/XsdSequence.h>
#include <xsdelements/XsdGroup.h>

#include <core/XsdParserCore.h>

XsdRestriction::XsdRestriction(StringMap attributesMap,
                               VisitorFunctionType visitorFunction,
                               XsdAbstractElement* parent)
  : XsdAnnotatedElements(attributesMap, visitorFunction, parent),
    m_base(nullptr),
    m_fractionDigits(nullptr),
    m_length(nullptr),
    m_maxExclusive(nullptr),
    m_maxInclusive(nullptr),
    m_maxLength(nullptr),
    m_minExclusive(nullptr),
    m_minInclusive(nullptr),
    m_minLength(nullptr),
    m_pattern(nullptr),
    m_totalDigits(nullptr),
    m_whiteSpace(nullptr),
    m_group(nullptr),
    m_all(nullptr),
    m_choice(nullptr),
    m_sequence(nullptr)
{
  if(haveAttribute(BASE_TAG))
    m_baseString = getAttribute(BASE_TAG);

  if (m_baseString)
  {
    if (XsdParserCore::getXsdTypesToCpp().contains(m_baseString.value()))
    {
      StringMap attributes;
      attributes.emplace(NAME_TAG, m_baseString.value());
      m_base = ReferenceBase::createFromXsd(
                 static_cast<XsdAbstractElement*>(
                   new XsdBuiltInDataType(attributes,
                                          nullptr,
                                          this)));
    }
    else
    {
      auto parseMappers = XsdParserCore::getParseMappers();

      ConfigEntryData config;
      if(parseMappers.contains(TAG<XsdElement>::xsd))
        config = parseMappers.at(TAG<XsdElement>::xsd);
      else if(parseMappers.contains(TAG<XsdElement>::xs))
        config = parseMappers.at(TAG<XsdElement>::xs);

      if (config.parserFunction == nullptr && config.visitorFunction == nullptr)
        throw ParsingException("Invalid Parsing Configuration for XsdElement.");

      m_base = new UnsolvedReference(m_baseString.value(),
                                     new XsdElement(StringMap{},
                                                    config.visitorFunction,
                                                    this));
      getParser()->addUnsolvedReference(static_cast<UnsolvedReference*>(m_base));
    }
  }
}


/**
 * Performs a copy of the current object for replacing purposes. The cloned objects are used to replace
 * {@link UnsolvedReference} objects in the reference solving process.
 * @param placeHolderAttributes The additional attributes to add to the clone.
 * @return A copy of the object from which is called upon.
 */
XsdRestriction::XsdRestriction(const XsdRestriction& other, XsdAbstractElement* parent)
  : XsdAnnotatedElements(other.getAttributesMap(), other.m_visitorFunction, parent)
{
  if (!other.m_enumeration.empty())
  {
    for(auto& enumerationObj : static_cast<XsdRestriction*>(this)->m_enumeration)
      m_enumeration.push_back(new XsdEnumeration(*enumerationObj, this));
  }

  if (other.m_fractionDigits != nullptr)
    m_fractionDigits = new XsdFractionDigits(*other.m_fractionDigits, this);

  if (other.m_length != nullptr)
    m_length = new XsdLength(*other.m_length, this);

  if (other.m_maxExclusive != nullptr)
    m_maxExclusive = new XsdMaxExclusive(*other.m_maxExclusive, this);

  if (other.m_maxInclusive != nullptr)
    m_maxInclusive = new XsdMaxInclusive(*other.m_maxInclusive, this);

  if (other.m_maxLength != nullptr)
    m_maxLength = new XsdMaxLength(*other.m_maxLength, this);

  if (other.m_minExclusive != nullptr)
    m_minExclusive = new XsdMinExclusive(*other.m_minExclusive, this);

  if (other.m_minInclusive != nullptr)
    m_minInclusive = new XsdMinInclusive(*other.m_minInclusive, this);

  if (other.m_minLength != nullptr)
    m_minLength = new XsdMinLength(*other.m_minLength, this);

  if (other.m_pattern != nullptr)
    m_pattern = new XsdPattern(*other.m_pattern, this);

  if (other.m_totalDigits != nullptr)
    m_totalDigits = new XsdTotalDigits(*other.m_totalDigits, this);

  if (other.m_whiteSpace != nullptr)
    m_whiteSpace = new XsdWhiteSpace(*other.m_whiteSpace, this);

  if (other.m_all != nullptr)
    m_all = new XsdAll(*other.m_all, this);

  if (other.m_choice != nullptr)
    m_choice = new XsdChoice(*other.m_choice, this);

  if (other.m_sequence != nullptr)
    m_sequence = new XsdSequence(*other.m_sequence, this);

  if (other.m_group != nullptr)
    m_group = new ReferenceBase(m_group, this);

  m_base = other.m_base;
}

void XsdRestriction::replaceUnsolvedElements(NamedConcreteElement* elementWrapper)
{
  XsdAnnotatedElements::replaceUnsolvedElements(elementWrapper);

  static_cast<XsdRestrictionVisitor*>(getVisitor())->replaceUnsolvedAttributes(elementWrapper, this);

  XsdNamedElements* element = elementWrapper->getElement();

  bool isComplexOrSimpleType = dynamic_cast<XsdComplexType*>(element) != nullptr ||
                                                                         dynamic_cast<XsdSimpleType*>(element) != nullptr;

  if (auto x = dynamic_cast<UnsolvedReference*>(m_base);
      x != nullptr &&
      isComplexOrSimpleType &&
      compareReference(elementWrapper, x))
    m_base = elementWrapper;

  if (auto x = dynamic_cast<UnsolvedReference*>(m_group);
      x != nullptr &&
      dynamic_cast<XsdGroup*>(m_group->getElement()) != nullptr &&
      dynamic_cast<XsdGroup*>(element) != nullptr &&
      compareReference(elementWrapper, x))
    m_group = elementWrapper;
}


std::list<XsdAttribute*> XsdRestriction::getXsdAttributes(void) const
{
  return static_cast<XsdRestrictionVisitor*>(getVisitor())->getXsdAttributes();
}


std::list<XsdAttributeGroup*> XsdRestriction::getXsdAttributeGroup(void) const
{
  return static_cast<XsdRestrictionVisitor*>(getVisitor())->getXsdAttributeGroups();
}
