TEMPLATE = app
CONFIG += console c++2b strict_c++
CONFIG -= app_bundle
CONFIG -= qt

CONFIG += link_pkgconfig
PKGCONFIG += pugixml

INCLUDEPATH += src

HEADERS += \
  src/core/XsdParser.h \
  src/core/XsdParserCore.h \
  src/core/XsdParserJar.h \
  src/core/utils/CommonTypes.h \
  src/core/utils/ConfigEntryData.h \
  src/core/utils/DefaultParserConfig.h \
  src/core/utils/NamespaceInfo.h \
  src/core/utils/NonDeletedPtr.h \
  src/core/utils/ParserConfig.h \
  src/core/utils/SchemaLocation.h \
  src/core/utils/StringOperations.h \
  src/core/utils/TagLookup.h \
  src/core/utils/UnsolvedReferenceItem.h \
  src/xsdelements/AttributeValidations.h \
  src/xsdelements/XsdAbstractElement.h \
  src/xsdelements/XsdAll.h \
  src/xsdelements/XsdAnnotatedElements.h \
  src/xsdelements/XsdAnnotation.h \
  src/xsdelements/XsdAnnotationChildren.h \
  src/xsdelements/XsdAppInfo.h \
  src/xsdelements/XsdAttribute.h \
  src/xsdelements/XsdAttributeGroup.h \
  src/xsdelements/XsdBuiltInDataType.h \
  src/xsdelements/XsdChoice.h \
  src/xsdelements/XsdComplexContent.h \
  src/xsdelements/XsdComplexType.h \
  src/xsdelements/XsdDocumentation.h \
  src/xsdelements/XsdElement.h \
  src/xsdelements/XsdExtension.h \
  src/xsdelements/XsdGroup.h \
  src/xsdelements/XsdIdentifierElements.h \
  src/xsdelements/XsdImport.h \
  src/xsdelements/XsdInclude.h \
  src/xsdelements/XsdList.h \
  src/xsdelements/XsdMultipleElements.h \
  src/xsdelements/XsdNamedElements.h \
  src/xsdelements/XsdRestriction.h \
  src/xsdelements/XsdSchema.h \
  src/xsdelements/XsdSequence.h \
  src/xsdelements/XsdSimpleContent.h \
  src/xsdelements/XsdSimpleType.h \
  src/xsdelements/XsdUnion.h \
  src/xsdelements/elementswrapper/ConcreteElement.h \
  src/xsdelements/elementswrapper/NamedConcreteElement.h \
  src/xsdelements/elementswrapper/ReferenceBase.h \
  src/xsdelements/elementswrapper/UnsolvedReference.h \
  src/xsdelements/enums/BlockDefaultEnum.h \
  src/xsdelements/enums/BlockEnum.h \
  src/xsdelements/enums/ComplexTypeBlockEnum.h \
  src/xsdelements/enums/FinalDefaultEnum.h \
  src/xsdelements/enums/FinalEnum.h \
  src/xsdelements/enums/FormEnum.h \
  src/xsdelements/enums/SimpleTypeFinalEnum.h \
  src/xsdelements/enums/UsageEnum.h \
  src/xsdelements/enums/WhiteSpaceEnum.h \
  src/xsdelements/enums/XsdEnum.h \
  src/xsdelements/exceptions/ParentAvailableException.h \
  src/xsdelements/exceptions/ParsingException.h \
  src/xsdelements/exceptions/VisitorNotFoundException.h \
  src/xsdelements/visitors/AttributesVisitor.h \
  src/xsdelements/visitors/XsdAbstractElementVisitor.h \
  src/xsdelements/visitors/XsdAllVisitor.h \
  src/xsdelements/visitors/XsdAnnotatedElementsVisitor.h \
  src/xsdelements/visitors/XsdAnnotationVisitor.h \
  src/xsdelements/visitors/XsdAttributeGroupVisitor.h \
  src/xsdelements/visitors/XsdAttributeVisitor.h \
  src/xsdelements/visitors/XsdChoiceVisitor.h \
  src/xsdelements/visitors/XsdComplexContentVisitor.h \
  src/xsdelements/visitors/XsdComplexTypeVisitor.h \
  src/xsdelements/visitors/XsdElementVisitor.h \
  src/xsdelements/visitors/XsdExtensionVisitor.h \
  src/xsdelements/visitors/XsdGroupVisitor.h \
  src/xsdelements/visitors/XsdListVisitor.h \
  src/xsdelements/visitors/XsdNamedElementsVisitor.h \
  src/xsdelements/visitors/XsdRestrictionVisitor.h \
  src/xsdelements/visitors/XsdSchemaVisitor.h \
  src/xsdelements/visitors/XsdSequenceVisitor.h \
  src/xsdelements/visitors/XsdSimpleContentVisitor.h \
  src/xsdelements/visitors/XsdSimpleTypeVisitor.h \
  src/xsdelements/visitors/XsdUnionVisitor.h \
  src/xsdelements/xsdrestrictions/XsdEnumeration.h \
  src/xsdelements/xsdrestrictions/XsdFractionDigits.h \
  src/xsdelements/xsdrestrictions/XsdIntegerRestrictions.h \
  src/xsdelements/xsdrestrictions/XsdLength.h \
  src/xsdelements/xsdrestrictions/XsdMaxExclusive.h \
  src/xsdelements/xsdrestrictions/XsdMaxInclusive.h \
  src/xsdelements/xsdrestrictions/XsdMaxLength.h \
  src/xsdelements/xsdrestrictions/XsdMinExclusive.h \
  src/xsdelements/xsdrestrictions/XsdMinInclusive.h \
  src/xsdelements/xsdrestrictions/XsdMinLength.h \
  src/xsdelements/xsdrestrictions/XsdPattern.h \
  src/xsdelements/xsdrestrictions/XsdStringRestrictions.h \
  src/xsdelements/xsdrestrictions/XsdTotalDigits.h \
  src/xsdelements/xsdrestrictions/XsdWhiteSpace.h

SOURCES += \
  src/core/XsdParser.cpp \
  src/core/XsdParserCore.cpp \
  src/core/utils/ParserConfig.cpp \
  src/core/utils/SchemaLocation.cpp \
  src/main.cpp \
  src/xsdelements/AttributeValidations.cpp \
  src/xsdelements/XsdAbstractElement.cpp \
  src/xsdelements/XsdAll.cpp \
  src/xsdelements/XsdAnnotation.cpp \
  src/xsdelements/XsdAttribute.cpp \
  src/xsdelements/XsdAttributeGroup.cpp \
  src/xsdelements/XsdChoice.cpp \
  src/xsdelements/XsdComplexContent.cpp \
  src/xsdelements/XsdComplexType.cpp \
  src/xsdelements/XsdElement.cpp \
  src/xsdelements/XsdExtension.cpp \
  src/xsdelements/XsdGroup.cpp \
  src/xsdelements/XsdImport.cpp \
  src/xsdelements/XsdInclude.cpp \
  src/xsdelements/XsdMultipleElements.cpp \
  src/xsdelements/XsdNamedElements.cpp \
  src/xsdelements/XsdRestriction.cpp \
  src/xsdelements/XsdSchema.cpp \
  src/xsdelements/XsdSequence.cpp \
  src/xsdelements/XsdSimpleType.cpp \
  src/xsdelements/XsdUnion.cpp \
  src/xsdelements/elementswrapper/ConcreteElement.cpp \
  src/xsdelements/elementswrapper/NamedConcreteElement.cpp \
  src/xsdelements/elementswrapper/ReferenceBase.cpp \
  src/xsdelements/elementswrapper/UnsolvedReference.cpp \
  src/xsdelements/visitors/XsdAbstractElementVisitor.cpp \
  src/xsdelements/visitors/XsdComplexTypeVisitor.cpp \
  src/xsdelements/visitors/XsdNamedElementsVisitor.cpp \
  src/xsdelements/visitors/XsdRestrictionVisitor.cpp \
  src/xsdelements/visitors/XsdSchemaVisitor.cpp \
  src/xsdelements/visitors/XsdSimpleTypeVisitor.cpp \
  src/xsdelements/xsdrestrictions/XsdEnumeration.cpp

