#include "ParserConfig.h"

#include <xsdelements/elementswrapper/ReferenceBase.h>
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

const std::map<std::string, std::string> ParserConfig::getXsdTypesToCpp(void) const
{
  std::map<std::string, std::string> xsdTypesToCpp;

  // string types
  constexpr std::string_view stringType   = "std::string";
  constexpr std::string_view qNameType    = "QName"; // specialized
  // standard integer types
  constexpr std::string_view booleanType  = "bool";
  constexpr std::string_view longType     = "int64_t";
  constexpr std::string_view uLongType    = "uint64_t";
  constexpr std::string_view integerType  = "int32_t";
  constexpr std::string_view uIntegerType = "uint32_t";
  constexpr std::string_view shortType    = "int16_t";
  constexpr std::string_view uShortType   = "uint16_t";
  constexpr std::string_view byteType     = "int8_t";
  constexpr std::string_view uByteType    = "uint8_t";
  // floating point types
  constexpr std::string_view floatType    = "float";
  constexpr std::string_view doubleType   = "double";

  // time/date oriented types (specialized)
  xsdTypesToCpp.emplace("date",               "xs::date");
  xsdTypesToCpp.emplace("dateTime",           "xs::dateTime");
  xsdTypesToCpp.emplace("time",               "xs::time");
  xsdTypesToCpp.emplace("duration",           "xs::duration");
  xsdTypesToCpp.emplace("dayTimeDuration",    "xs::dayTimeDuration");
  xsdTypesToCpp.emplace("yearMonthDuration",  "xs::yearMonthDuration");

  // calendar types
  xsdTypesToCpp.emplace("gDay",       "std::chrono::day");
  xsdTypesToCpp.emplace("gMonth",     "std::chrono::month");
  xsdTypesToCpp.emplace("gMonthDay",  "std::chrono::month_day");
  xsdTypesToCpp.emplace("gYear",      "std::chrono::year");
  xsdTypesToCpp.emplace("gYearMonth", "std::chrono::year_month");

  // weird integer types
  xsdTypesToCpp.emplace("positiveInteger",    uIntegerType);
  xsdTypesToCpp.emplace("nonPositiveInteger", integerType);
  xsdTypesToCpp.emplace("negativeInteger",    integerType);
  xsdTypesToCpp.emplace("nonNegativeInteger", uIntegerType);

  // standard integer types
  xsdTypesToCpp.emplace("bool",          booleanType);
  xsdTypesToCpp.emplace("long",          longType);
  xsdTypesToCpp.emplace("integer",       integerType);
  xsdTypesToCpp.emplace("int",           integerType);
  xsdTypesToCpp.emplace("short",         shortType);
  xsdTypesToCpp.emplace("byte",          byteType);
  xsdTypesToCpp.emplace("unsignedLong",  uLongType);
  xsdTypesToCpp.emplace("unsignedInt",   uIntegerType);
  xsdTypesToCpp.emplace("unsignedShort", uShortType);
  xsdTypesToCpp.emplace("unsignedByte",  uByteType);

  // floating point types
  xsdTypesToCpp.emplace("decimal", floatType);
  xsdTypesToCpp.emplace("double",  doubleType);
  xsdTypesToCpp.emplace("float",   floatType);

  // string types
  xsdTypesToCpp.emplace("anyURI",           stringType);
  xsdTypesToCpp.emplace("string",           stringType);
  xsdTypesToCpp.emplace("normalizedString", stringType);
  xsdTypesToCpp.emplace("token",            stringType);
  xsdTypesToCpp.emplace("language",         stringType);
  xsdTypesToCpp.emplace("NMTOKEN",          stringType);
  xsdTypesToCpp.emplace("Name",             stringType);
  xsdTypesToCpp.emplace("NCName",           stringType);
  xsdTypesToCpp.emplace("ID",               stringType);
  xsdTypesToCpp.emplace("IDREF",            stringType);
  xsdTypesToCpp.emplace("ENTITY",           stringType);
  xsdTypesToCpp.emplace("untypedAtomic",    stringType);

  // qualified types
  xsdTypesToCpp.emplace("QName",    qNameType);
  xsdTypesToCpp.emplace("NOTATION", qNameType);

  for(auto& entry : xsdTypesToCpp)
  {
    if(!entry.first.contains(':'))
    {
      xsdTypesToCpp.emplace("xs:"  + entry.first, entry.second);
      xsdTypesToCpp.emplace("xsd:" + entry.first, entry.second);
    }
  }

  return xsdTypesToCpp;
}

static StringMap generateAttributeMap(pugi::xml_node node)
{
  StringMap attributesMapped;
  for(auto& attr : node.attributes())
    attributesMapped.emplace(std::make_pair(attr.name(), attr.value()));
  return attributesMapped;
}

template<typename T>
static std::shared_ptr<ReferenceBase> genericParser(std::shared_ptr<XsdParserCore> parserInstance,
                                                    pugi::xml_node node,
                                                    VisitorFunctionType visitorFunction,
                                                    std::shared_ptr<XsdAbstractElement> parent)
{
  return XsdAbstractElement::xsdParseSkeleton(
        node,
        std::static_pointer_cast<XsdAbstractElement>(
          create<T>(parserInstance,
                    generateAttributeMap(node),
                    visitorFunction,
                    parent)));
}

static std::shared_ptr<ReferenceBase> schemaParser(std::shared_ptr<XsdParserCore> parserInstance,
                                                   pugi::xml_node node,
                                                   VisitorFunctionType visitorFunction,
                                                   std::shared_ptr<XsdAbstractElement> parent)
{
  auto xsdSchemaRef = genericParser<XsdSchema>(parserInstance, node, visitorFunction, parent);
  auto xsdSchema = std::static_pointer_cast<XsdSchema>(xsdSchemaRef->getElement());

  std::list<std::shared_ptr<XsdImport>> importsList = xsdSchema->getChildren<XsdImport>();

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
static void addGenericEntry(std::map<std::string_view, ConfigEntryData>& mapper, ConfigEntryData entry)
{
  mapper.emplace(std::make_pair(TAG<T>::xsd, entry));
  mapper.emplace(std::make_pair(TAG<T>::xs , entry));
  mapper.emplace(std::make_pair(TAG<T>::id , entry));
}

#ifdef DEBUG
template<typename T, typename V>
static void addElementEntry(std::map<std::string_view, ConfigEntryData>& mapper)
{
  addGenericEntry<T>(mapper,
                     ConfigEntryData
                     {
                       typeid(T).name(),
                       genericParser<T>,
                       typeid(V).name(),
                       genericVisitor<T, V>
                     });
}
#if 0
template<typename T>
static void addAnnotatedEntry(std::map<std::string_view, ConfigEntryData>& mapper)
{
  addGenericEntry<T>(mapper,
                     ConfigEntryData
                     {
                       typeid(T).name(),
                       genericParser<T>,
                       typeid(XsdAnnotatedElements).name(),
                       genericVisitor<T, XsdAnnotatedElementsVisitorWrapper<T>>
                     });
}
#endif
#else
template<typename T, typename V>
static void addElementEntry(std::map<std::string_view, ConfigEntryData>& mapper)
{
  addGenericEntry<T>(mapper,
                     ConfigEntryData
                     {
                       genericParser<T>,
                       genericVisitor<T, V>
                     });
}
#endif

template<typename T>
static void addAnnotatedEntry(std::map<std::string_view, ConfigEntryData>& mapper)
{
  addElementEntry<T, XsdAnnotatedElementsVisitorWrapper<T>>(mapper);
}


const std::map<std::string_view, ConfigEntryData> ParserConfig::getParseMappers(void) const
{
  std::map<std::string_view, ConfigEntryData> mappers;

#ifdef DEBUG
  addGenericEntry<XsdSchema>(mappers,
                              ConfigEntryData
                              {
                                typeid(XsdSchema).name(),
                                schemaParser,
                                typeid(XsdSchema).name(),
                                genericVisitor<XsdSchema, XsdSchemaVisitor>
                              });

  addGenericEntry<XsdAppInfo>(mappers,
                              ConfigEntryData
                              {
                                typeid(XsdAppInfo).name(),
                                genericParser<XsdAppInfo>,
                                typeid(std::nullopt_t).name(),
                                nullptr
                              });

  addGenericEntry<XsdDocumentation>(mappers,
                              ConfigEntryData
                              {
                                typeid(XsdDocumentation).name(),
                                genericParser<XsdDocumentation>,
                                typeid(std::nullopt_t).name(),
                                nullptr
                              });
#else
  addGenericEntry<XsdSchema>(mappers,
                              ConfigEntryData
                              {
                                schemaParser,
                                genericVisitor<XsdSchema, XsdSchemaVisitor>
                              });

  addGenericEntry<XsdAppInfo>(mappers,
                              ConfigEntryData
                              {
                                genericParser<XsdAppInfo>,
                                nullptr
                              });

  addGenericEntry<XsdDocumentation>(mappers,
                              ConfigEntryData
                              {
                                genericParser<XsdDocumentation>,
                                nullptr
                              });
#endif

  addElementEntry<XsdAll           , XsdAllVisitor           >(mappers);
  addElementEntry<XsdAttribute     , XsdAttributeVisitor     >(mappers);
  addElementEntry<XsdAttributeGroup, XsdAttributeGroupVisitor>(mappers);
  addElementEntry<XsdChoice        , XsdChoiceVisitor        >(mappers);
  addElementEntry<XsdComplexType   , XsdComplexTypeVisitor   >(mappers);
  addElementEntry<XsdElement       , XsdElementVisitor       >(mappers);
  addElementEntry<XsdGroup         , XsdGroupVisitor         >(mappers);
  addElementEntry<XsdSequence      , XsdSequenceVisitor      >(mappers);
  addElementEntry<XsdSimpleType    , XsdSimpleTypeVisitor    >(mappers);
  addElementEntry<XsdList          , XsdListVisitor          >(mappers);
  addElementEntry<XsdRestriction   , XsdRestrictionVisitor   >(mappers);
  addElementEntry<XsdUnion         , XsdUnionVisitor         >(mappers);
  addElementEntry<XsdAnnotation    , XsdAnnotationVisitor    >(mappers);
  addElementEntry<XsdExtension     , XsdExtensionVisitor     >(mappers);
  addElementEntry<XsdSimpleContent , XsdSimpleContentVisitor >(mappers);

  addAnnotatedEntry<XsdInclude       >(mappers);
  addAnnotatedEntry<XsdImport        >(mappers);
  addAnnotatedEntry<XsdEnumeration   >(mappers);
  addAnnotatedEntry<XsdFractionDigits>(mappers);
  addAnnotatedEntry<XsdLength        >(mappers);
  addAnnotatedEntry<XsdMaxExclusive  >(mappers);
  addAnnotatedEntry<XsdMaxInclusive  >(mappers);
  addAnnotatedEntry<XsdMinExclusive  >(mappers);
  addAnnotatedEntry<XsdMinInclusive  >(mappers);
  addAnnotatedEntry<XsdMinLength     >(mappers);
  addAnnotatedEntry<XsdPattern       >(mappers);
  addAnnotatedEntry<XsdTotalDigits   >(mappers);
  addAnnotatedEntry<XsdWhiteSpace    >(mappers);

  return mappers;
}
