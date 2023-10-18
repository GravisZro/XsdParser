#pragma once
// package org.xmlet.xsdparser.core.utils;

#include <xsdelements/AttributeValidations.h>
#include <xsdelements/XsdAll.h>
#include <xsdelements/XsdAnnotatedElements.h>
#include <xsdelements/XsdAnnotationChildren.h>
#include <xsdelements/XsdAnnotation.h>
#include <xsdelements/XsdAppInfo.h>
#include <xsdelements/XsdAttributeGroup.h>
#include <xsdelements/XsdAttribute.h>
#include <xsdelements/XsdBuiltInDataType.h>
#include <xsdelements/XsdChoice.h>
#include <xsdelements/XsdComplexContent.h>
#include <xsdelements/XsdComplexType.h>
#include <xsdelements/XsdDocumentation.h>
#include <xsdelements/XsdElement.h>
#include <xsdelements/XsdExtension.h>
#include <xsdelements/XsdGroup.h>
#include <xsdelements/XsdIdentifierElements.h>
#include <xsdelements/XsdImport.h>
#include <xsdelements/XsdList.h>
#include <xsdelements/XsdMultipleElements.h>
#include <xsdelements/XsdNamedElements.h>
#include <xsdelements/XsdRestriction.h>
#include <xsdelements/XsdSchema.h>
#include <xsdelements/XsdSequence.h>
#include <xsdelements/XsdSimpleContent.h>
#include <xsdelements/XsdSimpleType.h>
#include <xsdelements/XsdUnion.h>

#include <xsdelements/visitors/AttributesVisitor.h>
#include <xsdelements/visitors/XsdAbstractElementVisitor.h>
#include <xsdelements/visitors/XsdAllVisitor.h>
#include <xsdelements/visitors/XsdAnnotatedElementsVisitor.h>
#include <xsdelements/visitors/XsdAnnotationVisitor.h>
#include <xsdelements/visitors/XsdAttributeGroupVisitor.h>
#include <xsdelements/visitors/XsdAttributeVisitor.h>
#include <xsdelements/visitors/XsdChoiceVisitor.h>
#include <xsdelements/visitors/XsdComplexContentVisitor.h>
#include <xsdelements/visitors/XsdComplexTypeVisitor.h>
#include <xsdelements/visitors/XsdElementVisitor.h>
#include <xsdelements/visitors/XsdExtensionVisitor.h>
#include <xsdelements/visitors/XsdGroupVisitor.h>
#include <xsdelements/visitors/XsdListVisitor.h>
#include <xsdelements/visitors/XsdRestrictionsVisitor.h>
#include <xsdelements/visitors/XsdSchemaVisitor.h>
#include <xsdelements/visitors/XsdSequenceVisitor.h>
#include <xsdelements/visitors/XsdSimpleContentVisitor.h>
#include <xsdelements/visitors/XsdSimpleTypeVisitor.h>
#include <xsdelements/visitors/XsdUnionVisitor.h>

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


#include <core/utils/ParserConfig.h>
#include <unordered_map>
#include <map>
#include <string_view>

const std::map<std::u16string, std::u16string> ParserConfig::getXsdTypesToJava(void)
{
  std::map<std::u16string, std::u16string> xsdTypesToJava;

  std::u16string_view string = u"std::string";
  std::u16string_view xmlGregorianCalendar = u"XMLGregorianCalendar";
  std::u16string_view duration = u"Duration";
  std::u16string_view bigInteger = u"BigInteger";
  std::u16string_view integer = u"Integer";
  std::u16string_view shortString = u"Short";
  std::u16string_view qName = u"QName";
  std::u16string_view longString = u"Long";
  std::u16string_view byteString = u"Byte";

  xsdTypesToJava.insert(std::make_pair(u"xsd:anyURI", string));
  xsdTypesToJava.insert(std::make_pair(u"xs:anyURI", string));
  xsdTypesToJava.insert(std::make_pair(u"anyURI", string));
  xsdTypesToJava.insert(std::make_pair(u"xsd:bool", u"Boolean"));
  xsdTypesToJava.insert(std::make_pair(u"xs:bool", u"Boolean"));
  xsdTypesToJava.insert(std::make_pair(u"bool", u"Boolean"));
  xsdTypesToJava.insert(std::make_pair(u"xsd:date", xmlGregorianCalendar));
  xsdTypesToJava.insert(std::make_pair(u"xs:date", xmlGregorianCalendar));
  xsdTypesToJava.insert(std::make_pair(u"date", xmlGregorianCalendar));
  xsdTypesToJava.insert(std::make_pair(u"xsd:dateTime", xmlGregorianCalendar));
  xsdTypesToJava.insert(std::make_pair(u"xs:dateTime", xmlGregorianCalendar));
  xsdTypesToJava.insert(std::make_pair(u"dateTime", xmlGregorianCalendar));
  xsdTypesToJava.insert(std::make_pair(u"xsd:time", xmlGregorianCalendar));
  xsdTypesToJava.insert(std::make_pair(u"xs:time", xmlGregorianCalendar));
  xsdTypesToJava.insert(std::make_pair(u"time", xmlGregorianCalendar));
  xsdTypesToJava.insert(std::make_pair(u"xsd:duration", duration));
  xsdTypesToJava.insert(std::make_pair(u"xs:duration", duration));
  xsdTypesToJava.insert(std::make_pair(u"duration", duration));
  xsdTypesToJava.insert(std::make_pair(u"xsd:dayTimeDuration", duration));
  xsdTypesToJava.insert(std::make_pair(u"xs:dayTimeDuration", duration));
  xsdTypesToJava.insert(std::make_pair(u"dayTimeDuration", duration));
  xsdTypesToJava.insert(std::make_pair(u"xsd:yearMonthDuration", duration));
  xsdTypesToJava.insert(std::make_pair(u"xs:yearMonthDuration", duration));
  xsdTypesToJava.insert(std::make_pair(u"yearMonthDuration", duration));
  xsdTypesToJava.insert(std::make_pair(u"xsd:gDay", xmlGregorianCalendar));
  xsdTypesToJava.insert(std::make_pair(u"xs:gDay", xmlGregorianCalendar));
  xsdTypesToJava.insert(std::make_pair(u"gDay", xmlGregorianCalendar));
  xsdTypesToJava.insert(std::make_pair(u"xsd:gMonth", xmlGregorianCalendar));
  xsdTypesToJava.insert(std::make_pair(u"xs:gMonth", xmlGregorianCalendar));
  xsdTypesToJava.insert(std::make_pair(u"gMonth", xmlGregorianCalendar));
  xsdTypesToJava.insert(std::make_pair(u"xsd:gMonthDay", xmlGregorianCalendar));
  xsdTypesToJava.insert(std::make_pair(u"xs:gMonthDay", xmlGregorianCalendar));
  xsdTypesToJava.insert(std::make_pair(u"gMonthDay", xmlGregorianCalendar));
  xsdTypesToJava.insert(std::make_pair(u"xsd:gYear", xmlGregorianCalendar));
  xsdTypesToJava.insert(std::make_pair(u"xs:gYear", xmlGregorianCalendar));
  xsdTypesToJava.insert(std::make_pair(u"gYear", xmlGregorianCalendar));
  xsdTypesToJava.insert(std::make_pair(u"xsd:gYearMonth", xmlGregorianCalendar));
  xsdTypesToJava.insert(std::make_pair(u"xs:gYearMonth", xmlGregorianCalendar));
  xsdTypesToJava.insert(std::make_pair(u"gYearMonth", xmlGregorianCalendar));
  xsdTypesToJava.insert(std::make_pair(u"xsd:decimal", u"BigDecimal"));
  xsdTypesToJava.insert(std::make_pair(u"xs:decimal", u"BigDecimal"));
  xsdTypesToJava.insert(std::make_pair(u"decimal", u"BigDecimal"));
  xsdTypesToJava.insert(std::make_pair(u"xsd:integer", bigInteger));
  xsdTypesToJava.insert(std::make_pair(u"xs:integer", bigInteger));
  xsdTypesToJava.insert(std::make_pair(u"integer", bigInteger));
  xsdTypesToJava.insert(std::make_pair(u"xsd:nonPositiveInteger", bigInteger));
  xsdTypesToJava.insert(std::make_pair(u"xs:nonPositiveInteger", bigInteger));
  xsdTypesToJava.insert(std::make_pair(u"nonPositiveInteger", bigInteger));
  xsdTypesToJava.insert(std::make_pair(u"xsd:negativeInteger", bigInteger));
  xsdTypesToJava.insert(std::make_pair(u"xs:negativeInteger", bigInteger));
  xsdTypesToJava.insert(std::make_pair(u"negativeInteger", bigInteger));
  xsdTypesToJava.insert(std::make_pair(u"xsd:long", longString));
  xsdTypesToJava.insert(std::make_pair(u"xs:long", longString));
  xsdTypesToJava.insert(std::make_pair(u"long", longString));
  xsdTypesToJava.insert(std::make_pair(u"xsd:int", integer));
  xsdTypesToJava.insert(std::make_pair(u"xs:int", integer));
  xsdTypesToJava.insert(std::make_pair(u"int", integer));
  xsdTypesToJava.insert(std::make_pair(u"xsd:short", shortString));
  xsdTypesToJava.insert(std::make_pair(u"xs:short", shortString));
  xsdTypesToJava.insert(std::make_pair(u"short", shortString));
  xsdTypesToJava.insert(std::make_pair(u"xsd:byte", byteString));
  xsdTypesToJava.insert(std::make_pair(u"xs:byte", byteString));
  xsdTypesToJava.insert(std::make_pair(u"byte", byteString));
  xsdTypesToJava.insert(std::make_pair(u"xsd:nonNegativeInteger", bigInteger));
  xsdTypesToJava.insert(std::make_pair(u"xs:nonNegativeInteger", bigInteger));
  xsdTypesToJava.insert(std::make_pair(u"nonNegativeInteger", bigInteger));
  xsdTypesToJava.insert(std::make_pair(u"xsd:unsignedLong", bigInteger));
  xsdTypesToJava.insert(std::make_pair(u"xs:unsignedLong", bigInteger));
  xsdTypesToJava.insert(std::make_pair(u"unsignedLong", bigInteger));
  xsdTypesToJava.insert(std::make_pair(u"xsd:unsignedInt", longString));
  xsdTypesToJava.insert(std::make_pair(u"xs:unsignedInt", longString));
  xsdTypesToJava.insert(std::make_pair(u"unsignedInt", longString));
  xsdTypesToJava.insert(std::make_pair(u"xsd:unsignedShort", integer));
  xsdTypesToJava.insert(std::make_pair(u"xs:unsignedShort", integer));
  xsdTypesToJava.insert(std::make_pair(u"unsignedShort", integer));
  xsdTypesToJava.insert(std::make_pair(u"xsd:unsignedByte", shortString));
  xsdTypesToJava.insert(std::make_pair(u"xs:unsignedByte", shortString));
  xsdTypesToJava.insert(std::make_pair(u"unsignedByte", shortString));
  xsdTypesToJava.insert(std::make_pair(u"xsd:positiveInteger", bigInteger));
  xsdTypesToJava.insert(std::make_pair(u"xs:positiveInteger", bigInteger));
  xsdTypesToJava.insert(std::make_pair(u"positiveInteger", bigInteger));
  xsdTypesToJava.insert(std::make_pair(u"xsd:double", u"Double"));
  xsdTypesToJava.insert(std::make_pair(u"xs:double", u"Double"));
  xsdTypesToJava.insert(std::make_pair(u"double", u"Double"));
  xsdTypesToJava.insert(std::make_pair(u"xsd:float", u"Float"));
  xsdTypesToJava.insert(std::make_pair(u"xs:float", u"Float"));
  xsdTypesToJava.insert(std::make_pair(u"float", u"Float"));
  xsdTypesToJava.insert(std::make_pair(u"xsd:QName", qName));
  xsdTypesToJava.insert(std::make_pair(u"xs:QName", qName));
  xsdTypesToJava.insert(std::make_pair(u"QName", qName));
  xsdTypesToJava.insert(std::make_pair(u"xsd:NOTATION", qName));
  xsdTypesToJava.insert(std::make_pair(u"xs:NOTATION", qName));
  xsdTypesToJava.insert(std::make_pair(u"NOTATION", qName));
  xsdTypesToJava.insert(std::make_pair(u"xsd:string", string));
  xsdTypesToJava.insert(std::make_pair(u"xs:string", string));
  xsdTypesToJava.insert(std::make_pair(u"string", string));
  xsdTypesToJava.insert(std::make_pair(u"xsd:normalizedString", string));
  xsdTypesToJava.insert(std::make_pair(u"xs:normalizedString", string));
  xsdTypesToJava.insert(std::make_pair(u"normalizedString", string));
  xsdTypesToJava.insert(std::make_pair(u"xsd:token", string));
  xsdTypesToJava.insert(std::make_pair(u"xs:token", string));
  xsdTypesToJava.insert(std::make_pair(u"token", string));
  xsdTypesToJava.insert(std::make_pair(u"xsd:language", string));
  xsdTypesToJava.insert(std::make_pair(u"xs:language", string));
  xsdTypesToJava.insert(std::make_pair(u"language", string));
  xsdTypesToJava.insert(std::make_pair(u"xsd:NMTOKEN", string));
  xsdTypesToJava.insert(std::make_pair(u"xs:NMTOKEN", string));
  xsdTypesToJava.insert(std::make_pair(u"NMTOKEN", string));
  xsdTypesToJava.insert(std::make_pair(u"xsd:Name", string));
  xsdTypesToJava.insert(std::make_pair(u"xs:Name", string));
  xsdTypesToJava.insert(std::make_pair(u"Name", string));
  xsdTypesToJava.insert(std::make_pair(u"xsd:NCName", string));
  xsdTypesToJava.insert(std::make_pair(u"xs:NCName", string));
  xsdTypesToJava.insert(std::make_pair(u"NCName", string));
  xsdTypesToJava.insert(std::make_pair(u"xsd:ID", string));
  xsdTypesToJava.insert(std::make_pair(u"xs:ID", string));
  xsdTypesToJava.insert(std::make_pair(u"ID", string));
  xsdTypesToJava.insert(std::make_pair(u"xsd:IDREF", string));
  xsdTypesToJava.insert(std::make_pair(u"xs:IDREF", string));
  xsdTypesToJava.insert(std::make_pair(u"IDREF", string));
  xsdTypesToJava.insert(std::make_pair(u"xsd:ENTITY", string));
  xsdTypesToJava.insert(std::make_pair(u"xs:ENTITY", string));
  xsdTypesToJava.insert(std::make_pair(u"ENTITY", string));
  xsdTypesToJava.insert(std::make_pair(u"xsd:untypedAtomic", string));
  xsdTypesToJava.insert(std::make_pair(u"xs:untypedAtomic", string));
  xsdTypesToJava.insert(std::make_pair(u"untypedAtomic", string));

  return xsdTypesToJava;
}


const std::map<std::u16string, ConfigEntryData> ParserConfig::getParseMappers(void)
{
  std::map<std::u16string, ConfigEntryData> parseMappers;

  parseMappers.insert(std::make_pair(XsdSchema::XSD_TAG, new ConfigEntryData(XsdSchema::parse, elem -> new XsdSchemaVisitor((XsdSchema) elem))));
  parseMappers.insert(std::make_pair(XsdSchema::XS_TAG, new ConfigEntryData(XsdSchema::parse, elem -> new XsdSchemaVisitor((XsdSchema) elem))));
  parseMappers.insert(std::make_pair(XsdSchema::TAG, new ConfigEntryData(XsdSchema::parse, elem -> new XsdSchemaVisitor((XsdSchema) elem))));
  parseMappers.insert(std::make_pair(XsdAll::XSD_TAG, new ConfigEntryData(XsdAll::parse, elem -> new XsdAllVisitor((XsdAll) elem))));
  parseMappers.insert(std::make_pair(XsdAll::XS_TAG, new ConfigEntryData(XsdAll::parse, elem -> new XsdAllVisitor((XsdAll) elem))));
  parseMappers.insert(std::make_pair(XsdAll::TAG, new ConfigEntryData(XsdAll::parse, elem -> new XsdAllVisitor((XsdAll) elem))));
  parseMappers.insert(std::make_pair(XsdAttribute::XSD_TAG, new ConfigEntryData(XsdAttribute::parse, elem -> new XsdAttributeVisitor((XsdAttribute) elem))));
  parseMappers.insert(std::make_pair(XsdAttribute::XS_TAG, new ConfigEntryData(XsdAttribute::parse, elem -> new XsdAttributeVisitor((XsdAttribute) elem))));
  parseMappers.insert(std::make_pair(XsdAttribute::TAG, new ConfigEntryData(XsdAttribute::parse, elem -> new XsdAttributeVisitor((XsdAttribute) elem))));
  parseMappers.insert(std::make_pair(XsdAttributeGroup::XSD_TAG, new ConfigEntryData(XsdAttributeGroup::parse, elem -> new XsdAttributeGroupVisitor((XsdAttributeGroup) elem))));
  parseMappers.insert(std::make_pair(XsdAttributeGroup::XS_TAG, new ConfigEntryData(XsdAttributeGroup::parse, elem -> new XsdAttributeGroupVisitor((XsdAttributeGroup) elem))));
  parseMappers.insert(std::make_pair(XsdAttributeGroup::TAG, new ConfigEntryData(XsdAttributeGroup::parse, elem -> new XsdAttributeGroupVisitor((XsdAttributeGroup) elem))));
  parseMappers.insert(std::make_pair(XsdChoice::XSD_TAG, new ConfigEntryData(XsdChoice::parse, elem -> new XsdChoiceVisitor((XsdChoice) elem))));
  parseMappers.insert(std::make_pair(XsdChoice::XS_TAG, new ConfigEntryData(XsdChoice::parse, elem -> new XsdChoiceVisitor((XsdChoice) elem))));
  parseMappers.insert(std::make_pair(XsdChoice::TAG, new ConfigEntryData(XsdChoice::parse, elem -> new XsdChoiceVisitor((XsdChoice) elem))));
  parseMappers.insert(std::make_pair(XsdComplexType::XSD_TAG, new ConfigEntryData(XsdComplexType::parse, elem -> new XsdComplexTypeVisitor((XsdComplexType) elem))));
  parseMappers.insert(std::make_pair(XsdComplexType::XS_TAG, new ConfigEntryData(XsdComplexType::parse, elem -> new XsdComplexTypeVisitor((XsdComplexType) elem))));
  parseMappers.insert(std::make_pair(XsdComplexType::TAG, new ConfigEntryData(XsdComplexType::parse, elem -> new XsdComplexTypeVisitor((XsdComplexType) elem))));
  parseMappers.insert(std::make_pair(XsdElement::XSD_TAG, new ConfigEntryData(XsdElement::parse, elem -> new XsdElementVisitor((XsdElement) elem))));
  parseMappers.insert(std::make_pair(XsdElement::XS_TAG, new ConfigEntryData(XsdElement::parse, elem -> new XsdElementVisitor((XsdElement) elem))));
  parseMappers.insert(std::make_pair(XsdElement::TAG, new ConfigEntryData(XsdElement::parse, elem -> new XsdElementVisitor((XsdElement) elem))));
  parseMappers.insert(std::make_pair(XsdGroup::XSD_TAG, new ConfigEntryData(XsdGroup::parse, elem -> new XsdGroupVisitor((XsdGroup) elem))));
  parseMappers.insert(std::make_pair(XsdGroup::XS_TAG, new ConfigEntryData(XsdGroup::parse, elem -> new XsdGroupVisitor((XsdGroup) elem))));
  parseMappers.insert(std::make_pair(XsdGroup::TAG, new ConfigEntryData(XsdGroup::parse, elem -> new XsdGroupVisitor((XsdGroup) elem))));
  parseMappers.insert(std::make_pair(XsdInclude::XSD_TAG, new ConfigEntryData(XsdInclude::parse, elem -> new XsdAnnotatedElementsVisitor((XsdInclude) elem))));
  parseMappers.insert(std::make_pair(XsdInclude::XS_TAG, new ConfigEntryData(XsdInclude::parse, elem -> new XsdAnnotatedElementsVisitor((XsdInclude) elem))));
  parseMappers.insert(std::make_pair(XsdInclude::TAG, new ConfigEntryData(XsdInclude::parse, elem -> new XsdAnnotatedElementsVisitor((XsdInclude) elem))));
  parseMappers.insert(std::make_pair(XsdImport::XSD_TAG, new ConfigEntryData(XsdImport::parse, elem -> new XsdAnnotatedElementsVisitor((XsdImport) elem))));
  parseMappers.insert(std::make_pair(XsdImport::XS_TAG, new ConfigEntryData(XsdImport::parse, elem -> new XsdAnnotatedElementsVisitor((XsdImport) elem))));
  parseMappers.insert(std::make_pair(XsdImport::TAG, new ConfigEntryData(XsdImport::parse, elem -> new XsdAnnotatedElementsVisitor((XsdImport) elem))));
  parseMappers.insert(std::make_pair(XsdSequence::XSD_TAG, new ConfigEntryData(XsdSequence::parse, elem -> new XsdSequenceVisitor((XsdSequence) elem))));
  parseMappers.insert(std::make_pair(XsdSequence::XS_TAG, new ConfigEntryData(XsdSequence::parse, elem -> new XsdSequenceVisitor((XsdSequence) elem))));
  parseMappers.insert(std::make_pair(XsdSequence::TAG, new ConfigEntryData(XsdSequence::parse, elem -> new XsdSequenceVisitor((XsdSequence) elem))));
  parseMappers.insert(std::make_pair(XsdSimpleType::XSD_TAG, new ConfigEntryData(XsdSimpleType::parse, elem -> new XsdSimpleTypeVisitor((XsdSimpleType) elem))));
  parseMappers.insert(std::make_pair(XsdSimpleType::XS_TAG, new ConfigEntryData(XsdSimpleType::parse, elem -> new XsdSimpleTypeVisitor((XsdSimpleType) elem))));
  parseMappers.insert(std::make_pair(XsdSimpleType::TAG, new ConfigEntryData(XsdSimpleType::parse, elem -> new XsdSimpleTypeVisitor((XsdSimpleType) elem))));
  parseMappers.insert(std::make_pair(XsdList::XSD_TAG, new ConfigEntryData(XsdList::parse, elem -> new XsdListVisitor((XsdList) elem))));
  parseMappers.insert(std::make_pair(XsdList::XS_TAG, new ConfigEntryData(XsdList::parse, elem -> new XsdListVisitor((XsdList) elem))));
  parseMappers.insert(std::make_pair(XsdList::TAG, new ConfigEntryData(XsdList::parse, elem -> new XsdListVisitor((XsdList) elem))));
  parseMappers.insert(std::make_pair(XsdRestriction::XSD_TAG, new ConfigEntryData(XsdRestriction::parse, elem -> new XsdRestrictionsVisitor((XsdRestriction) elem))));
  parseMappers.insert(std::make_pair(XsdRestriction::XS_TAG, new ConfigEntryData(XsdRestriction::parse, elem -> new XsdRestrictionsVisitor((XsdRestriction) elem))));
  parseMappers.insert(std::make_pair(XsdRestriction::TAG, new ConfigEntryData(XsdRestriction::parse, elem -> new XsdRestrictionsVisitor((XsdRestriction) elem))));
  parseMappers.insert(std::make_pair(XsdUnion::XSD_TAG, new ConfigEntryData(XsdUnion::parse, elem -> new XsdUnionVisitor((XsdUnion) elem))));
  parseMappers.insert(std::make_pair(XsdUnion::XS_TAG, new ConfigEntryData(XsdUnion::parse, elem -> new XsdUnionVisitor((XsdUnion) elem))));
  parseMappers.insert(std::make_pair(XsdUnion::TAG, new ConfigEntryData(XsdUnion::parse, elem -> new XsdUnionVisitor((XsdUnion) elem))));

  parseMappers.insert(std::make_pair(XsdAnnotation::XSD_TAG, new ConfigEntryData(XsdAnnotation::parse, elem -> new XsdAnnotationVisitor((XsdAnnotation) elem))));
  parseMappers.insert(std::make_pair(XsdAnnotation::XS_TAG, new ConfigEntryData(XsdAnnotation::parse, elem -> new XsdAnnotationVisitor((XsdAnnotation) elem))));
  parseMappers.insert(std::make_pair(XsdAnnotation::TAG, new ConfigEntryData(XsdAnnotation::parse, elem -> new XsdAnnotationVisitor((XsdAnnotation) elem))));
  parseMappers.insert(std::make_pair(XsdAppInfo::XSD_TAG, new ConfigEntryData(XsdAppInfo::parse, null)));
  parseMappers.insert(std::make_pair(XsdAppInfo::XS_TAG, new ConfigEntryData(XsdAppInfo::parse, null)));
  parseMappers.insert(std::make_pair(XsdAppInfo::TAG, new ConfigEntryData(XsdAppInfo::parse, null)));
  parseMappers.insert(std::make_pair(XsdComplexContent::XSD_TAG, new ConfigEntryData(XsdComplexContent::parse, elem -> new XsdComplexContentVisitor((XsdComplexContent) elem))));
  parseMappers.insert(std::make_pair(XsdComplexContent::XS_TAG, new ConfigEntryData(XsdComplexContent::parse, elem -> new XsdComplexContentVisitor((XsdComplexContent) elem))));
  parseMappers.insert(std::make_pair(XsdComplexContent::TAG, new ConfigEntryData(XsdComplexContent::parse, elem -> new XsdComplexContentVisitor((XsdComplexContent) elem))));
  parseMappers.insert(std::make_pair(XsdDocumentation::XSD_TAG, new ConfigEntryData(XsdDocumentation::parse, null)));
  parseMappers.insert(std::make_pair(XsdDocumentation::XS_TAG, new ConfigEntryData(XsdDocumentation::parse, null)));
  parseMappers.insert(std::make_pair(XsdDocumentation::TAG, new ConfigEntryData(XsdDocumentation::parse, null)));
  parseMappers.insert(std::make_pair(XsdExtension::XSD_TAG, new ConfigEntryData(XsdExtension::parse, elem -> new XsdExtensionVisitor((XsdExtension) elem))));
  parseMappers.insert(std::make_pair(XsdExtension::XS_TAG, new ConfigEntryData(XsdExtension::parse, elem -> new XsdExtensionVisitor((XsdExtension) elem))));
  parseMappers.insert(std::make_pair(XsdExtension::TAG, new ConfigEntryData(XsdExtension::parse, elem -> new XsdExtensionVisitor((XsdExtension) elem))));
  parseMappers.insert(std::make_pair(XsdSimpleContent::XSD_TAG, new ConfigEntryData(XsdSimpleContent::parse, elem -> new XsdSimpleContentVisitor((XsdSimpleContent) elem))));
  parseMappers.insert(std::make_pair(XsdSimpleContent::XS_TAG, new ConfigEntryData(XsdSimpleContent::parse, elem -> new XsdSimpleContentVisitor((XsdSimpleContent) elem))));
  parseMappers.insert(std::make_pair(XsdSimpleContent::TAG, new ConfigEntryData(XsdSimpleContent::parse, elem -> new XsdSimpleContentVisitor((XsdSimpleContent) elem))));

  parseMappers.insert(std::make_pair(XsdEnumeration::XSD_TAG, new ConfigEntryData(XsdEnumeration::parse, elem -> new XsdAnnotatedElementsVisitor((XsdEnumeration) elem))));
  parseMappers.insert(std::make_pair(XsdEnumeration::XS_TAG, new ConfigEntryData(XsdEnumeration::parse, elem -> new XsdAnnotatedElementsVisitor((XsdEnumeration) elem))));
  parseMappers.insert(std::make_pair(XsdEnumeration::TAG, new ConfigEntryData(XsdEnumeration::parse, elem -> new XsdAnnotatedElementsVisitor((XsdEnumeration) elem))));
  parseMappers.insert(std::make_pair(XsdFractionDigits::XSD_TAG, new ConfigEntryData(XsdFractionDigits::parse, elem -> new XsdAnnotatedElementsVisitor((XsdFractionDigits) elem))));
  parseMappers.insert(std::make_pair(XsdFractionDigits::XS_TAG, new ConfigEntryData(XsdFractionDigits::parse, elem -> new XsdAnnotatedElementsVisitor((XsdFractionDigits) elem))));
  parseMappers.insert(std::make_pair(XsdFractionDigits::TAG, new ConfigEntryData(XsdFractionDigits::parse, elem -> new XsdAnnotatedElementsVisitor((XsdFractionDigits) elem))));
  parseMappers.insert(std::make_pair(XsdLength::XSD_TAG, new ConfigEntryData(XsdLength::parse, elem -> new XsdAnnotatedElementsVisitor((XsdLength) elem))));
  parseMappers.insert(std::make_pair(XsdLength::XS_TAG, new ConfigEntryData(XsdLength::parse, elem -> new XsdAnnotatedElementsVisitor((XsdLength) elem))));
  parseMappers.insert(std::make_pair(XsdLength::TAG, new ConfigEntryData(XsdLength::parse, elem -> new XsdAnnotatedElementsVisitor((XsdLength) elem))));
  parseMappers.insert(std::make_pair(XsdMaxExclusive::XSD_TAG, new ConfigEntryData(XsdMaxExclusive::parse, elem -> new XsdAnnotatedElementsVisitor((XsdMaxExclusive) elem))));
  parseMappers.insert(std::make_pair(XsdMaxExclusive::XS_TAG, new ConfigEntryData(XsdMaxExclusive::parse, elem -> new XsdAnnotatedElementsVisitor((XsdMaxExclusive) elem))));
  parseMappers.insert(std::make_pair(XsdMaxExclusive::TAG, new ConfigEntryData(XsdMaxExclusive::parse, elem -> new XsdAnnotatedElementsVisitor((XsdMaxExclusive) elem))));
  parseMappers.insert(std::make_pair(XsdMaxInclusive::XSD_TAG, new ConfigEntryData(XsdMaxInclusive::parse, elem -> new XsdAnnotatedElementsVisitor((XsdMaxInclusive) elem))));
  parseMappers.insert(std::make_pair(XsdMaxInclusive::XS_TAG, new ConfigEntryData(XsdMaxInclusive::parse, elem -> new XsdAnnotatedElementsVisitor((XsdMaxInclusive) elem))));
  parseMappers.insert(std::make_pair(XsdMaxInclusive::TAG, new ConfigEntryData(XsdMaxInclusive::parse, elem -> new XsdAnnotatedElementsVisitor((XsdMaxInclusive) elem))));
  parseMappers.insert(std::make_pair(XsdMaxLength::XSD_TAG, new ConfigEntryData(XsdMaxLength::parse, elem -> new XsdAnnotatedElementsVisitor((XsdMaxLength) elem))));
  parseMappers.insert(std::make_pair(XsdMaxLength::XS_TAG, new ConfigEntryData(XsdMaxLength::parse, elem -> new XsdAnnotatedElementsVisitor((XsdMaxLength) elem))));
  parseMappers.insert(std::make_pair(XsdMaxLength::TAG, new ConfigEntryData(XsdMaxLength::parse, elem -> new XsdAnnotatedElementsVisitor((XsdMaxLength) elem))));
  parseMappers.insert(std::make_pair(XsdMinExclusive::XSD_TAG, new ConfigEntryData(XsdMinExclusive::parse, elem -> new XsdAnnotatedElementsVisitor((XsdMinExclusive) elem))));
  parseMappers.insert(std::make_pair(XsdMinExclusive::XS_TAG, new ConfigEntryData(XsdMinExclusive::parse, elem -> new XsdAnnotatedElementsVisitor((XsdMinExclusive) elem))));
  parseMappers.insert(std::make_pair(XsdMinExclusive::TAG, new ConfigEntryData(XsdMinExclusive::parse, elem -> new XsdAnnotatedElementsVisitor((XsdMinExclusive) elem))));
  parseMappers.insert(std::make_pair(XsdMinInclusive::XSD_TAG, new ConfigEntryData(XsdMinInclusive::parse, elem -> new XsdAnnotatedElementsVisitor((XsdMinInclusive) elem))));
  parseMappers.insert(std::make_pair(XsdMinInclusive::XS_TAG, new ConfigEntryData(XsdMinInclusive::parse, elem -> new XsdAnnotatedElementsVisitor((XsdMinInclusive) elem))));
  parseMappers.insert(std::make_pair(XsdMinInclusive::TAG, new ConfigEntryData(XsdMinInclusive::parse, elem -> new XsdAnnotatedElementsVisitor((XsdMinInclusive) elem))));
  parseMappers.insert(std::make_pair(XsdMinLength::XSD_TAG, new ConfigEntryData(XsdMinLength::parse, elem -> new XsdAnnotatedElementsVisitor((XsdMinLength) elem))));
  parseMappers.insert(std::make_pair(XsdMinLength::XS_TAG, new ConfigEntryData(XsdMinLength::parse, elem -> new XsdAnnotatedElementsVisitor((XsdMinLength) elem))));
  parseMappers.insert(std::make_pair(XsdMinLength::TAG, new ConfigEntryData(XsdMinLength::parse, elem -> new XsdAnnotatedElementsVisitor((XsdMinLength) elem))));
  parseMappers.insert(std::make_pair(XsdPattern::XSD_TAG, new ConfigEntryData(XsdPattern::parse, elem -> new XsdAnnotatedElementsVisitor((XsdPattern) elem))));
  parseMappers.insert(std::make_pair(XsdPattern::XS_TAG, new ConfigEntryData(XsdPattern::parse, elem -> new XsdAnnotatedElementsVisitor((XsdPattern) elem))));
  parseMappers.insert(std::make_pair(XsdPattern::TAG, new ConfigEntryData(XsdPattern::parse, elem -> new XsdAnnotatedElementsVisitor((XsdPattern) elem))));
  parseMappers.insert(std::make_pair(XsdTotalDigits::XSD_TAG, new ConfigEntryData(XsdTotalDigits::parse, elem -> new XsdAnnotatedElementsVisitor((XsdTotalDigits) elem))));
  parseMappers.insert(std::make_pair(XsdTotalDigits::XS_TAG, new ConfigEntryData(XsdTotalDigits::parse, elem -> new XsdAnnotatedElementsVisitor((XsdTotalDigits) elem))));
  parseMappers.insert(std::make_pair(XsdTotalDigits::TAG, new ConfigEntryData(XsdTotalDigits::parse, elem -> new XsdAnnotatedElementsVisitor((XsdTotalDigits) elem))));
  parseMappers.insert(std::make_pair(XsdWhiteSpace::XSD_TAG, new ConfigEntryData(XsdWhiteSpace::parse, elem -> new XsdAnnotatedElementsVisitor((XsdWhiteSpace) elem))));
  parseMappers.insert(std::make_pair(XsdWhiteSpace::XS_TAG, new ConfigEntryData(XsdWhiteSpace::parse, elem -> new XsdAnnotatedElementsVisitor((XsdWhiteSpace) elem))));
  parseMappers.insert(std::make_pair(XsdWhiteSpace::TAG, new ConfigEntryData(XsdWhiteSpace::parse, elem -> new XsdAnnotatedElementsVisitor((XsdWhiteSpace) elem))));

  return parseMappers;
}
