#pragma once



#include <core/utils/ParseData.h>
#include <xsdelements/XsdAbstractElement.h>
#include <xsdelements/elementswrapper/ReferenceBase.h>
#include <xsdelements/elementswrapper/UnsolvedReference.h>

#include <xsdelements/xsdrestrictions/XsdStringRestrictions.h>

class XsdAbstractElementVisitor;
class XsdParserCore;
class XsdAbstractElement;

/**
 * Represents a value that a given XSD type is allowed to take. The value is defined as a {@link std::string}.
 */
class XsdEnumeration : public XsdStringRestrictions
{
public:
    constexpr static const std::string_view XSD_TAG = "xsd:enumeration";
    constexpr static const std::string_view XS_TAG = "xs:enumeration";
    constexpr static const std::string_view TAG = "enumeration";

public:
  using XsdStringRestrictions::clone;
  XsdEnumeration(std::shared_ptr<XsdParserCore> parser,
                 StringMap elementFieldsMapParam,
                 VisitorFunctionReference visitorFunction);

public:
  void accept(std::shared_ptr<XsdAbstractElementVisitor> xsdAbstractElementVisitor);
    /**
     * Performs a copy of the current object for replacing purposes. The cloned objects are used to replace
     * {@link UnsolvedReference} objects in the reference solving process.
     * @param placeHolderAttributes The additional attributes to add to the clone.
     * @return A copy of the object from which is called upon.
     */
  std::shared_ptr<XsdEnumeration> clone(StringMap placeHolderAttributes);
  static std::shared_ptr<ReferenceBase> parse(ParseData parseData);
};
