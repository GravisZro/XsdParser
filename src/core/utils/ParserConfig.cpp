#include "ParserConfig.h"

#include <xsdelements/AttributeValidations.h>
#include <xsdelements/XsdAbstractElement.h>
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
#include <xsdelements/XsdInclude.h>
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
#include <xsdelements/visitors/XsdRestrictionVisitor.h>
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

#include <core/utils/SchemaLocation.h>
#include <core/utils/ParserConfig.h>

const std::map<std::string, std::string> ParserConfig::getXsdTypesToJava(void)
{
  std::map<std::string, std::string> xsdTypesToJava;

  constexpr std::string_view string = "std::string";
  constexpr std::string_view xmlGregorianCalendar = "XMLGregorianCalendar";
  constexpr std::string_view duration = "Duration";
  constexpr std::string_view bigInteger = "BigInteger";
  constexpr std::string_view integer = "Integer";
  constexpr std::string_view shortString = "Short";
  constexpr std::string_view qName = "QName";
  constexpr std::string_view longString = "Long";
  constexpr std::string_view byteString = "Byte";

  xsdTypesToJava.emplace("xsd:anyURI", string);
  xsdTypesToJava.emplace("xs:anyURI", string);
  xsdTypesToJava.emplace("anyURI", string);
  xsdTypesToJava.emplace("xsd:bool", "Boolean");
  xsdTypesToJava.emplace("xs:bool", "Boolean");
  xsdTypesToJava.emplace("bool", "Boolean");
  xsdTypesToJava.emplace("xsd:date", xmlGregorianCalendar);
  xsdTypesToJava.emplace("xs:date", xmlGregorianCalendar);
  xsdTypesToJava.emplace("date", xmlGregorianCalendar);
  xsdTypesToJava.emplace("xsd:dateTime", xmlGregorianCalendar);
  xsdTypesToJava.emplace("xs:dateTime", xmlGregorianCalendar);
  xsdTypesToJava.emplace("dateTime", xmlGregorianCalendar);
  xsdTypesToJava.emplace("xsd:time", xmlGregorianCalendar);
  xsdTypesToJava.emplace("xs:time", xmlGregorianCalendar);
  xsdTypesToJava.emplace("time", xmlGregorianCalendar);
  xsdTypesToJava.emplace("xsd:duration", duration);
  xsdTypesToJava.emplace("xs:duration", duration);
  xsdTypesToJava.emplace("duration", duration);
  xsdTypesToJava.emplace("xsd:dayTimeDuration", duration);
  xsdTypesToJava.emplace("xs:dayTimeDuration", duration);
  xsdTypesToJava.emplace("dayTimeDuration", duration);
  xsdTypesToJava.emplace("xsd:yearMonthDuration", duration);
  xsdTypesToJava.emplace("xs:yearMonthDuration", duration);
  xsdTypesToJava.emplace("yearMonthDuration", duration);
  xsdTypesToJava.emplace("xsd:gDay", xmlGregorianCalendar);
  xsdTypesToJava.emplace("xs:gDay", xmlGregorianCalendar);
  xsdTypesToJava.emplace("gDay", xmlGregorianCalendar);
  xsdTypesToJava.emplace("xsd:gMonth", xmlGregorianCalendar);
  xsdTypesToJava.emplace("xs:gMonth", xmlGregorianCalendar);
  xsdTypesToJava.emplace("gMonth", xmlGregorianCalendar);
  xsdTypesToJava.emplace("xsd:gMonthDay", xmlGregorianCalendar);
  xsdTypesToJava.emplace("xs:gMonthDay", xmlGregorianCalendar);
  xsdTypesToJava.emplace("gMonthDay", xmlGregorianCalendar);
  xsdTypesToJava.emplace("xsd:gYear", xmlGregorianCalendar);
  xsdTypesToJava.emplace("xs:gYear", xmlGregorianCalendar);
  xsdTypesToJava.emplace("gYear", xmlGregorianCalendar);
  xsdTypesToJava.emplace("xsd:gYearMonth", xmlGregorianCalendar);
  xsdTypesToJava.emplace("xs:gYearMonth", xmlGregorianCalendar);
  xsdTypesToJava.emplace("gYearMonth", xmlGregorianCalendar);
  xsdTypesToJava.emplace("xsd:decimal", "BigDecimal");
  xsdTypesToJava.emplace("xs:decimal", "BigDecimal");
  xsdTypesToJava.emplace("decimal", "BigDecimal");
  xsdTypesToJava.emplace("xsd:integer", bigInteger);
  xsdTypesToJava.emplace("xs:integer", bigInteger);
  xsdTypesToJava.emplace("integer", bigInteger);
  xsdTypesToJava.emplace("xsd:nonPositiveInteger", bigInteger);
  xsdTypesToJava.emplace("xs:nonPositiveInteger", bigInteger);
  xsdTypesToJava.emplace("nonPositiveInteger", bigInteger);
  xsdTypesToJava.emplace("xsd:negativeInteger", bigInteger);
  xsdTypesToJava.emplace("xs:negativeInteger", bigInteger);
  xsdTypesToJava.emplace("negativeInteger", bigInteger);
  xsdTypesToJava.emplace("xsd:long", longString);
  xsdTypesToJava.emplace("xs:long", longString);
  xsdTypesToJava.emplace("long", longString);
  xsdTypesToJava.emplace("xsd:int", integer);
  xsdTypesToJava.emplace("xs:int", integer);
  xsdTypesToJava.emplace("int", integer);
  xsdTypesToJava.emplace("xsd:short", shortString);
  xsdTypesToJava.emplace("xs:short", shortString);
  xsdTypesToJava.emplace("short", shortString);
  xsdTypesToJava.emplace("xsd:byte", byteString);
  xsdTypesToJava.emplace("xs:byte", byteString);
  xsdTypesToJava.emplace("byte", byteString);
  xsdTypesToJava.emplace("xsd:nonNegativeInteger", bigInteger);
  xsdTypesToJava.emplace("xs:nonNegativeInteger", bigInteger);
  xsdTypesToJava.emplace("nonNegativeInteger", bigInteger);
  xsdTypesToJava.emplace("xsd:unsignedLong", bigInteger);
  xsdTypesToJava.emplace("xs:unsignedLong", bigInteger);
  xsdTypesToJava.emplace("unsignedLong", bigInteger);
  xsdTypesToJava.emplace("xsd:unsignedInt", longString);
  xsdTypesToJava.emplace("xs:unsignedInt", longString);
  xsdTypesToJava.emplace("unsignedInt", longString);
  xsdTypesToJava.emplace("xsd:unsignedShort", integer);
  xsdTypesToJava.emplace("xs:unsignedShort", integer);
  xsdTypesToJava.emplace("unsignedShort", integer);
  xsdTypesToJava.emplace("xsd:unsignedByte", shortString);
  xsdTypesToJava.emplace("xs:unsignedByte", shortString);
  xsdTypesToJava.emplace("unsignedByte", shortString);
  xsdTypesToJava.emplace("xsd:positiveInteger", bigInteger);
  xsdTypesToJava.emplace("xs:positiveInteger", bigInteger);
  xsdTypesToJava.emplace("positiveInteger", bigInteger);
  xsdTypesToJava.emplace("xsd:double", "Double");
  xsdTypesToJava.emplace("xs:double", "Double");
  xsdTypesToJava.emplace("double", "Double");
  xsdTypesToJava.emplace("xsd:float", "Float");
  xsdTypesToJava.emplace("xs:float", "Float");
  xsdTypesToJava.emplace("float", "Float");
  xsdTypesToJava.emplace("xsd:QName", qName);
  xsdTypesToJava.emplace("xs:QName", qName);
  xsdTypesToJava.emplace("QName", qName);
  xsdTypesToJava.emplace("xsd:NOTATION", qName);
  xsdTypesToJava.emplace("xs:NOTATION", qName);
  xsdTypesToJava.emplace("NOTATION", qName);
  xsdTypesToJava.emplace("xsd:string", string);
  xsdTypesToJava.emplace("xs:string", string);
  xsdTypesToJava.emplace("string", string);
  xsdTypesToJava.emplace("xsd:normalizedString", string);
  xsdTypesToJava.emplace("xs:normalizedString", string);
  xsdTypesToJava.emplace("normalizedString", string);
  xsdTypesToJava.emplace("xsd:token", string);
  xsdTypesToJava.emplace("xs:token", string);
  xsdTypesToJava.emplace("token", string);
  xsdTypesToJava.emplace("xsd:language", string);
  xsdTypesToJava.emplace("xs:language", string);
  xsdTypesToJava.emplace("language", string);
  xsdTypesToJava.emplace("xsd:NMTOKEN", string);
  xsdTypesToJava.emplace("xs:NMTOKEN", string);
  xsdTypesToJava.emplace("NMTOKEN", string);
  xsdTypesToJava.emplace("xsd:Name", string);
  xsdTypesToJava.emplace("xs:Name", string);
  xsdTypesToJava.emplace("Name", string);
  xsdTypesToJava.emplace("xsd:NCName", string);
  xsdTypesToJava.emplace("xs:NCName", string);
  xsdTypesToJava.emplace("NCName", string);
  xsdTypesToJava.emplace("xsd:ID", string);
  xsdTypesToJava.emplace("xs:ID", string);
  xsdTypesToJava.emplace("ID", string);
  xsdTypesToJava.emplace("xsd:IDREF", string);
  xsdTypesToJava.emplace("xs:IDREF", string);
  xsdTypesToJava.emplace("IDREF", string);
  xsdTypesToJava.emplace("xsd:ENTITY", string);
  xsdTypesToJava.emplace("xs:ENTITY", string);
  xsdTypesToJava.emplace("ENTITY", string);
  xsdTypesToJava.emplace("xsd:untypedAtomic", string);
  xsdTypesToJava.emplace("xs:untypedAtomic", string);
  xsdTypesToJava.emplace("untypedAtomic", string);

  return xsdTypesToJava;
}

static StringMap generateAttributeMap(pugi::xml_node node)
{
  StringMap attributesMapped;
  for(auto& attr : node.attributes())
    attributesMapped.emplace(std::make_pair(attr.name(), attr.value()));
  return attributesMapped;
}

template<typename T>
static std::shared_ptr<ReferenceBase> genericParser(const ParseData& parseData)
{
  return XsdAbstractElement::xsdParseSkeleton(parseData.node,
                                              std::static_pointer_cast<XsdAbstractElement>(
                                                create<T>(parseData.parserInstance,
                                                          generateAttributeMap(parseData.node),
                                                          parseData.visitorFunction,
                                                          nullptr)));
}

template<typename T>
static std::shared_ptr<ReferenceBase> annotatedParser(const ParseData& parseData)
{
  return XsdAnnotationChildren::xsdAnnotationChildrenParse(parseData.node,
                                                        std::static_pointer_cast<XsdAnnotationChildren>(
                                                          create<T>(parseData.parserInstance,
                                                                    generateAttributeMap(parseData.node))));
}


static std::shared_ptr<ReferenceBase> schemaParser(const ParseData& parseData)
{
  auto xsdSchemaRef = genericParser<XsdSchema>(parseData);
  auto xsdSchema = std::static_pointer_cast<XsdSchema>(xsdSchemaRef->getElement());

  std::list<std::shared_ptr<XsdImport>> importsList = xsdSchema->getChildrenImports();

  std::map<std::string, SchemaLocation> prefixLocations;
  for(auto& nspair : xsdSchema->getNamespaces())
    for(auto& import : importsList)
      if(import->getNamespace() == nspair.second.getName() && import->getSchemaLocation())
      {
        prefixLocations.emplace(nspair.first, import->getSchemaLocation());
        break;
      }

  xsdSchema->updatePrefixLocations(prefixLocations);
  return xsdSchemaRef;
}

template<typename ClassType, typename VisitorType>
static std::shared_ptr<XsdAbstractElementVisitor> genericVisitor(std::shared_ptr<XsdAbstractElement> element)
{
  return std::static_pointer_cast<XsdAbstractElementVisitor>(
        create<VisitorType>(
          std::static_pointer_cast<ClassType>(element)));
}

template<typename T>
static void addEntry(std::map<std::string_view, ConfigEntryData>& mapper, ConfigEntryData entry)
{
  mapper.emplace(std::make_pair(T::XSD_TAG, entry ));
  mapper.emplace(std::make_pair(T::XS_TAG, entry ));
  mapper.emplace(std::make_pair(T::TAG, entry ));
}

#ifdef DEBUG
template<typename T, typename V>
static void addGenericEntry(std::map<std::string_view, ConfigEntryData>& mapper)
{
  addEntry<T>(mapper, ConfigEntryData { typeid(T).name(), genericParser<T>, typeid(T).name(), genericVisitor<T, V> });
}

template<typename T>
static void addAnnotatedEntry(std::map<std::string_view, ConfigEntryData>& mapper)
{
  addEntry<T>(mapper, ConfigEntryData { typeid(T).name(), genericParser<T>, typeid(XsdAnnotatedElements).name(), genericVisitor<XsdAnnotatedElements, XsdAnnotatedElementsVisitor> });
}
#else
template<typename T, typename V>
static void addGenericEntry(std::map<std::string_view, ConfigEntryData>& mapper)
  { addEntry<T>(mapper, ConfigEntryData { genericParser<T>, genericVisitor<T, V> }); }

template<typename T>
static void addAnnotatedEntry(std::map<std::string_view, ConfigEntryData>& mapper)
  { addEntry<T>(mapper, ConfigEntryData { genericParser<T>, genericVisitor<XsdAnnotatedElements, XsdAnnotatedElementsVisitor> }); }
#endif

const std::map<std::string_view, ConfigEntryData> ParserConfig::getParseMappers(void)
{
  std::map<std::string_view, ConfigEntryData> mappers;

#ifdef DEBUG
  addEntry<XsdSchema>(mappers, ConfigEntryData { typeid(XsdSchema).name(), schemaParser, typeid(XsdSchema).name(), genericVisitor<XsdSchema, XsdSchemaVisitor> });

  addEntry<XsdAppInfo>(mappers, ConfigEntryData { typeid(XsdAppInfo).name(), annotatedParser<XsdAppInfo>, typeid(std::nullopt_t).name(), nullptr });
  addEntry<XsdDocumentation>(mappers, ConfigEntryData { typeid(XsdDocumentation).name(), annotatedParser<XsdDocumentation>, typeid(std::nullopt_t).name(), nullptr });
#else
  addEntry<XsdSchema>(mappers, ConfigEntryData { schemaParser, genericVisitor<XsdSchema, XsdSchemaVisitor> });

  addEntry<XsdAppInfo>(mappers, ConfigEntryData { annotatedParser<XsdAppInfo>, nullptr });
  addEntry<XsdDocumentation>(mappers, ConfigEntryData { annotatedParser<XsdDocumentation>, nullptr });
#endif

  addGenericEntry<XsdAll, XsdAllVisitor>(mappers);
  addGenericEntry<XsdAttribute, XsdAttributeVisitor>(mappers);
  addGenericEntry<XsdAttributeGroup, XsdAttributeGroupVisitor>(mappers);
  addGenericEntry<XsdChoice, XsdChoiceVisitor>(mappers);
  addGenericEntry<XsdComplexType, XsdComplexTypeVisitor>(mappers);
  addGenericEntry<XsdElement, XsdElementVisitor>(mappers);
  addGenericEntry<XsdGroup, XsdGroupVisitor>(mappers);
  addGenericEntry<XsdSequence, XsdSequenceVisitor>(mappers);
  addGenericEntry<XsdSimpleType, XsdSimpleTypeVisitor>(mappers);
  addGenericEntry<XsdList, XsdListVisitor>(mappers);
  addGenericEntry<XsdRestriction, XsdRestrictionVisitor>(mappers);
  addGenericEntry<XsdUnion, XsdUnionVisitor>(mappers);
  addGenericEntry<XsdAnnotation, XsdAnnotationVisitor>(mappers);
  addGenericEntry<XsdExtension, XsdExtensionVisitor>(mappers);
  addGenericEntry<XsdSimpleContent, XsdSimpleContentVisitor>(mappers);

  addAnnotatedEntry<XsdInclude>(mappers);
  addAnnotatedEntry<XsdImport>(mappers);
  addAnnotatedEntry<XsdEnumeration>(mappers);
  addAnnotatedEntry<XsdFractionDigits>(mappers);
  addAnnotatedEntry<XsdLength>(mappers);
  addAnnotatedEntry<XsdMaxExclusive>(mappers);
  addAnnotatedEntry<XsdMaxInclusive>(mappers);
  addAnnotatedEntry<XsdMinExclusive>(mappers);
  addAnnotatedEntry<XsdMinInclusive>(mappers);
  addAnnotatedEntry<XsdMinLength>(mappers);
  addAnnotatedEntry<XsdPattern>(mappers);
  addAnnotatedEntry<XsdTotalDigits>(mappers);
  addAnnotatedEntry<XsdWhiteSpace>(mappers);

  return mappers;
}
