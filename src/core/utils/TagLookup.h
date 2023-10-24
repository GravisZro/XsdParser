#ifndef TAGLOOKUP_H
#define TAGLOOKUP_H

#include <string_view>
template<typename T>
struct TAG;

#define MAKE_TAG(Type, String) \
class Type; \
template<> \
struct TAG<Type> \
{ \
  static constexpr std::string_view id = String; \
  static constexpr std::string_view xs = "xs:" String; \
  static constexpr std::string_view xsd = "xsd:" String; \
}

MAKE_TAG(XsdAll, "all");
MAKE_TAG(XsdAnnotation, "annotation");
MAKE_TAG(XsdAppInfo, "appinfo");
MAKE_TAG(XsdAttribute, "attribute");
MAKE_TAG(XsdAttributeGroup, "attributeGroup");
MAKE_TAG(XsdChoice, "choice");
MAKE_TAG(XsdComplexContent, "complexContent");
MAKE_TAG(XsdComplexType, "complexType");
MAKE_TAG(XsdDocumentation, "documentation");
MAKE_TAG(XsdElement, "element");
MAKE_TAG(XsdEnumeration, "enumeration");
MAKE_TAG(XsdExtension, "extension");
MAKE_TAG(XsdGroup, "group");
MAKE_TAG(XsdImport, "import");
MAKE_TAG(XsdInclude, "include");
MAKE_TAG(XsdList, "list");
MAKE_TAG(XsdRestriction, "restriction");
MAKE_TAG(XsdSchema, "schema");
MAKE_TAG(XsdSequence, "sequence");
MAKE_TAG(XsdSimpleContent, "simpleContent");
MAKE_TAG(XsdSimpleType, "simpleType");
MAKE_TAG(XsdUnion, "union");
MAKE_TAG(XsdFractionDigits, "fractionDigits");
MAKE_TAG(XsdLength, "length");
MAKE_TAG(XsdMaxExclusive, "maxExclusive");
MAKE_TAG(XsdMaxInclusive, "maxInclusive");
MAKE_TAG(XsdMaxLength, "maxLength");
MAKE_TAG(XsdMinExclusive, "minExclusive");
MAKE_TAG(XsdMinInclusive, "minInclusive");
MAKE_TAG(XsdMinLength, "minLength");
MAKE_TAG(XsdPattern, "pattern");
MAKE_TAG(XsdTotalDigits, "totalDigits");
MAKE_TAG(XsdWhiteSpace, "whiteSpace");

#endif // TAGLOOKUP_H
