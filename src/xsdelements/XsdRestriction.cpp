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

#include <core/XsdParserCore.h>
//#include <core/utils/ParserConfig.h>


XsdRestriction::XsdRestriction(std::shared_ptr<XsdParserCore> parser, StringMap attributesMap, VisitorFunctionReference visitorFunction)
  : XsdAnnotatedElements(parser, attributesMap, visitorFunction)
{
    if(attributesMap.contains(*BASE_TAG))
      m_baseString = attributesMap.at(*BASE_TAG);

    if (m_baseString)
    {
        if (XsdParserCore::getXsdTypesToJava().contains(m_baseString.value()))
        {
            StringMap attributes;
            attributes.emplace(NAME_TAG, m_baseString.value());
            m_base = ReferenceBase::createFromXsd(std::static_pointer_cast<XsdAbstractElement>(std::make_shared<XsdBuiltInDataType>(parser, attributes, std::shared_ptr<XsdRestriction>(this))));
        } else {
            std::map<std::string, ConfigEntryData> parseMappers = XsdParserCore::getParseMappers();

            ConfigEntryData config;
            if(parseMappers.contains(*XsdElement::XSD_TAG))
              config = parseMappers.at(*XsdElement::XSD_TAG);
            else if(parseMappers.contains(*XsdElement::XS_TAG))
              config = parseMappers.at(*XsdElement::XS_TAG);

            if (config.parserFunction && config.visitorFunction)
                throw new ParsingException("Invalid Parsing Configuration for XsdElement.");

            m_base = std::make_shared<UnsolvedReference>(m_baseString.value(),
                                                         std::make_shared<XsdElement>(std::shared_ptr<XsdAbstractElement>(this), m_parser, StringMap{}, config.visitorFunction));
            parser->addUnsolvedReference((UnsolvedReference) m_base);
        }
    }
}


void XsdRestriction::replaceUnsolvedElements(std::shared_ptr<NamedConcreteElement> element)
  {
      XsdAnnotatedElements::replaceUnsolvedElements(element);

      std::static_pointer_cast<XsdRestrictionsVisitor>(visitor)->replaceUnsolvedAttributes(parser, element, this);

      std::shared_ptr<XsdNamedElements> elem = element->getElement();

      bool isComplexOrSimpleType = std::dynamic_pointer_cast<XsdComplexType>(elem) ||
                                   std::dynamic_pointer_cast<XsdSimpleType>(elem);

      if (auto b = std::dynamic_pointer_cast<UnsolvedReference>(m_base);
          b && isComplexOrSimpleType &&
          compareReference(element, b)){
          m_base = element;
      }

      if (std::dynamic_pointer_cast<UnsolvedReference>(m_group) &&
          std::dynamic_pointer_cast<XsdGroup>(m_group->getElement()) &&
              elem instanceof XsdGroup && compareReference(element, (UnsolvedReference) m_group)){
          m_group = element;
      }
  }

  /**
   * Performs a copy of the current object for replacing purposes. The cloned objects are used to replace
   * {@link UnsolvedReference} objects in the reference solving process.
   * @param placeHolderAttributes The additional attributes to add to the clone.
   * @return A copy of the object from which is called upon.
   */
std::shared_ptr<XsdRestriction> XsdRestriction::clone(StringMap placeHolderAttributes)
  {
      placeHolderAttributes.merge(m_attributesMap);

      auto elementCopy = std::make_shared<XsdRestriction>(m_parser, placeHolderAttributes, m_visitorFunction);

      if (m_enumeration != null){
          elementCopy->m_enumeration = m_enumeration.stream().map(enumerationObj -> (XsdEnumeration) enumerationObj.clone(enumerationObj.getAttributesMap(), elementCopy));
      }

      if (m_fractionDigits != m_all){
          elementCopy->m_fractionDigits = (XsdFractionDigits) m_fractionDigits.clone(m_fractionDigits.getAttributesMap(), elementCopy);
      }

      if (m_length != m_all){
          elementCopy->m_length = (XsdLength) m_length.clone(m_length.getAttributesMap(), elementCopy);
      }

      if (m_maxExclusive != m_all){
          elementCopy->m_maxExclusive = (XsdMaxExclusive) m_maxExclusive.clone(m_maxExclusive.getAttributesMap(), elementCopy);
      }

      if (m_maxInclusive != m_all){
          elementCopy->m_maxInclusive = (XsdMaxInclusive) m_maxInclusive.clone(m_maxInclusive.getAttributesMap(), elementCopy);
      }

      if (m_maxLength != m_all){
          elementCopy->m_maxLength = (XsdMaxLength) m_maxLength.clone(m_maxLength.getAttributesMap(), elementCopy);
      }

      if (m_minExclusive != m_all){
          elementCopy->m_minExclusive = (XsdMinExclusive) m_minExclusive.clone(m_minExclusive.getAttributesMap(), elementCopy);
      }

      if (m_minInclusive != m_all){
          elementCopy->m_minInclusive = (XsdMinInclusive) m_minInclusive.clone(m_minInclusive.getAttributesMap(), elementCopy);
      }

      if (m_minLength != m_all){
          elementCopy->m_minLength = (XsdMinLength) m_minLength.clone(m_minLength.getAttributesMap(), elementCopy);
      }

      if (m_pattern != m_all){
          elementCopy->m_pattern = (XsdPattern) m_pattern.clone(pattern.getAttributesMap(), elementCopy);
      }

      if (m_totalDigits != m_all){
          elementCopy->m_totalDigits = (XsdTotalDigits) m_totalDigits.clone(totalDigits.getAttributesMap(), elementCopy);
      }

      if (m_whiteSpace != null){
          elementCopy->m_whiteSpace = (XsdWhiteSpace) m_whiteSpace.clone(whiteSpace.getAttributesMap(), elementCopy);
      }

      if (m_all != null){
          elementCopy->m_all = (XsdAll) m_all.clone(m_all.getAttributesMap(), elementCopy);
      }

      if (m_choice != null){
          elementCopy->m_choice = (XsdChoice) m_choice.clone(m_choice.getAttributesMap(), elementCopy);
      }

      if (m_sequence != null){
          elementCopy->m_sequence = (XsdSequence) m_sequence.clone(m_sequence.getAttributesMap(), elementCopy);
      }

      if (m_group != null){
          elementCopy->m_group = ReferenceBase::clone(m_parser, m_group, elementCopy);
      }

      elementCopy->m_parent = null;
      elementCopy->m_base = m_base;

      return elementCopy;
  }



std::list<std::shared_ptr<XsdAttribute>> XsdRestriction::getXsdAttributes(void) {
      return ((XsdRestrictionsVisitor)visitor).getXsdAttributes();
  }

  // @SuppressWarnings("unused")
std::list<std::shared_ptr<XsdAttributeGroup>> XsdRestriction::getXsdAttributeGroup(void) {
      return ((XsdRestrictionsVisitor)visitor).getXsdAttributeGroups();
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
  if(auto g = std::dynamic_pointer_cast<ConcreteElement>(m_group); g)
    return std::static_pointer_cast<XsdGroup>(g->getElement());
  return nullptr;
}
