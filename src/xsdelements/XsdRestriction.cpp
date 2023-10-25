#include "XsdRestriction.h"

#include <xsdelements/elementswrapper/UnsolvedReference.h>

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



void XsdRestriction::initialize(void)
{
  XsdAnnotatedElements::initialize();
  m_base.reset();
  m_enumeration.clear();
  m_fractionDigits.reset();
  m_length.reset();
  m_maxExclusive.reset();
  m_maxInclusive.reset();
  m_maxLength.reset();
  m_minExclusive.reset();
  m_minInclusive.reset();
  m_minLength.reset();
  m_pattern.reset();
  m_totalDigits.reset();
  m_whiteSpace.reset();
  m_group.reset();
  m_all.reset();
  m_choice.reset();
  m_sequence.reset();

  if(haveAttribute(BASE_TAG))
    m_baseString = getAttribute(BASE_TAG);

  if (m_baseString)
  {
    if (XsdParserCore::getXsdTypesToCpp().contains(m_baseString.value()))
    {
      StringMap attributes;
      attributes.emplace(NAME_TAG, m_baseString.value());
      m_base = ReferenceBase::createFromXsd(
                 std::static_pointer_cast<XsdAbstractElement>(
                   create<XsdBuiltInDataType>(getParser(),
                                              attributes,
                                              nullptr,
                                              shared_from_this())));
    } else {
      auto parseMappers = XsdParserCore::getParseMappers();

      ConfigEntryData config;
      if(parseMappers.contains(TAG<XsdElement>::xsd))
        config = parseMappers.at(TAG<XsdElement>::xsd);
      else if(parseMappers.contains(TAG<XsdElement>::xs))
        config = parseMappers.at(TAG<XsdElement>::xs);

      if (config.parserFunction == nullptr && config.visitorFunction == nullptr)
        throw ParsingException("Invalid Parsing Configuration for XsdElement.");

      m_base = create<UnsolvedReference>(m_baseString.value(),
                                         create<XsdElement>(getParser(),
                                                            StringMap{},
                                                            config.visitorFunction,
                                                            shared_from_this()));
      getParser()->addUnsolvedReference(std::static_pointer_cast<UnsolvedReference>(m_base));
    }
  }
}


void XsdRestriction::replaceUnsolvedElements(std::shared_ptr<NamedConcreteElement> element)
{
      XsdAnnotatedElements::replaceUnsolvedElements(element);

      std::static_pointer_cast<XsdRestrictionVisitor>(getVisitor())->replaceUnsolvedAttributes(
            getParser(),
            element,
            shared_from_this());

      std::shared_ptr<XsdNamedElements> elem = element->getElement();

      bool isComplexOrSimpleType = std::dynamic_pointer_cast<XsdComplexType>(elem) ||
                                   std::dynamic_pointer_cast<XsdSimpleType>(elem);

      if (auto b = std::dynamic_pointer_cast<UnsolvedReference>(m_base);
          b && isComplexOrSimpleType &&
          compareReference(element, b)){
          m_base = element;
      }

      if (auto x = std::dynamic_pointer_cast<UnsolvedReference>(m_group);
          x && std::dynamic_pointer_cast<XsdGroup>(m_group->getElement()) &&
          std::dynamic_pointer_cast<XsdGroup>(elem) &&
          compareReference(element, x))
        m_group = element;
  }

  /**
   * Performs a copy of the current object for replacing purposes. The cloned objects are used to replace
   * {@link UnsolvedReference} objects in the reference solving process.
   * @param placeHolderAttributes The additional attributes to add to the clone.
   * @return A copy of the object from which is called upon.
   */
std::shared_ptr<XsdAbstractElement> XsdRestriction::clone(StringMap placeHolderAttributes)
  {
      placeHolderAttributes.merge(getAttributesMap());

      auto elementCopy = create<XsdRestriction>(getParser(),
                                                placeHolderAttributes,
                                                m_visitorFunction,
                                                nullptr);

      if (!m_enumeration.empty())
      {
        for(auto& enumerationObj : m_enumeration)
          elementCopy->m_enumeration.push_back(
              std::static_pointer_cast<XsdEnumeration>(
                  enumerationObj->XsdAbstractElement::clone(enumerationObj->getAttributesMap(), elementCopy)));
      }

      if (m_fractionDigits)
          elementCopy->m_fractionDigits = std::static_pointer_cast<XsdFractionDigits>(m_fractionDigits->XsdAbstractElement::clone(m_fractionDigits->getAttributesMap(), elementCopy));

      if (m_length)
          elementCopy->m_length = std::static_pointer_cast<XsdLength>(m_length->XsdAbstractElement::clone(m_length->getAttributesMap(), elementCopy));

      if (m_maxExclusive)
          elementCopy->m_maxExclusive = std::static_pointer_cast<XsdMaxExclusive>(m_maxExclusive->XsdAbstractElement::clone(m_maxExclusive->getAttributesMap(), elementCopy));

      if (m_maxInclusive)
          elementCopy->m_maxInclusive = std::static_pointer_cast<XsdMaxInclusive>(m_maxInclusive->XsdAbstractElement::clone(m_maxInclusive->getAttributesMap(), elementCopy));

      if (m_maxLength)
          elementCopy->m_maxLength = std::static_pointer_cast<XsdMaxLength>(m_maxLength->XsdAbstractElement::clone(m_maxLength->getAttributesMap(), elementCopy));

      if (m_minExclusive)
          elementCopy->m_minExclusive = std::static_pointer_cast<XsdMinExclusive>(m_minExclusive->XsdAbstractElement::clone(m_minExclusive->getAttributesMap(), elementCopy));

      if (m_minInclusive)
          elementCopy->m_minInclusive = std::static_pointer_cast<XsdMinInclusive>(m_minInclusive->XsdAbstractElement::clone(m_minInclusive->getAttributesMap(), elementCopy));

      if (m_minLength)
          elementCopy->m_minLength = std::static_pointer_cast<XsdMinLength>(m_minLength->XsdAbstractElement::clone(m_minLength->getAttributesMap(), elementCopy));

      if (m_pattern)
          elementCopy->m_pattern = std::static_pointer_cast<XsdPattern>(m_pattern->XsdAbstractElement::clone(m_pattern->getAttributesMap(), elementCopy));

      if (m_totalDigits)
          elementCopy->m_totalDigits = std::static_pointer_cast<XsdTotalDigits>(m_totalDigits->XsdAbstractElement::clone(m_totalDigits->getAttributesMap(), elementCopy));

      if (m_whiteSpace)
          elementCopy->m_whiteSpace = std::static_pointer_cast<XsdWhiteSpace>(m_whiteSpace->XsdAbstractElement::clone(m_whiteSpace->getAttributesMap(), elementCopy));

      if (m_all)
          elementCopy->m_all = std::static_pointer_cast<XsdAll>(m_all->XsdAbstractElement::clone(m_all->getAttributesMap(), elementCopy));

      if (m_choice)
          elementCopy->m_choice = std::static_pointer_cast<XsdChoice>(m_choice->XsdAbstractElement::clone(m_choice->getAttributesMap(), elementCopy));

      if (m_sequence)
          elementCopy->m_sequence = std::static_pointer_cast<XsdSequence>(m_sequence->XsdAbstractElement::clone(m_sequence->getAttributesMap(), elementCopy));

      if (m_group)
          elementCopy->m_group = ReferenceBase::clone(getParser(), m_group, elementCopy);

      elementCopy->m_base = m_base;

      return elementCopy;
  }



std::list<std::shared_ptr<XsdAttribute>> XsdRestriction::getXsdAttributes(void)
{
  return std::static_pointer_cast<XsdRestrictionVisitor>(getVisitor())->getXsdAttributes();
}


std::list<std::shared_ptr<XsdAttributeGroup>> XsdRestriction::getXsdAttributeGroup(void)
{
  return std::static_pointer_cast<XsdRestrictionVisitor>(getVisitor())->getXsdAttributeGroups();
}

  /**
   * @return The {@link XsdComplexType} from which this extension extends or null if the {@link XsdParserCore} wasn't
   * able to replace the {@link UnsolvedReference} created by the base attribute value.
   */
std::shared_ptr<XsdComplexType> XsdRestriction::getBaseAsComplexType(void)
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
std::shared_ptr<XsdSimpleType> XsdRestriction::getBaseAsSimpleType(void)
{
  if (std::dynamic_pointer_cast<NamedConcreteElement>(m_base))
    if(auto x = std::dynamic_pointer_cast<XsdSimpleType>(m_base->getElement()); x)
      return x;
  return nullptr;
}

  /**
   * @return The {@link XsdBuiltInDataType} from which this extension extends.
   */
std::shared_ptr<XsdBuiltInDataType> XsdRestriction::getBaseAsBuiltInDataType(void)
{
  if (std::dynamic_pointer_cast<NamedConcreteElement>(m_base))
    if(auto x = std::dynamic_pointer_cast<XsdBuiltInDataType>(m_base->getElement()); x)
      return x;
  return nullptr;
}


std::shared_ptr<XsdGroup> XsdRestriction::getGroup(void)
{
  if(auto x = std::dynamic_pointer_cast<ConcreteElement>(m_group); x)
    return std::static_pointer_cast<XsdGroup>(x->getElement());
  return nullptr;
}
