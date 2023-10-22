#pragma once

#include <xsdelements/elementswrapper/ReferenceBase.h>
#include <xsdelements/elementswrapper/UnsolvedReference.h>
#include <xsdelements/xsdrestrictions/XsdStringRestrictions.h>

struct XsdAbstractElementVisitor;

/**
 * Represents a value that a given XSD type is allowed to take. The value is defined as a {@link std::string}.
 */
class XsdEnumeration : public XsdStringRestrictions
{
public:
  using XsdStringRestrictions::clone;
  constexpr static const std::string_view XSD_TAG = "xsd:enumeration";
  constexpr static const std::string_view XS_TAG = "xs:enumeration";
  constexpr static const std::string_view TAG = "enumeration";

public: // ctors
  XsdEnumeration(std::shared_ptr<XsdParserCore> parser,
                 StringMap attributesMap,
                 VisitorFunctionType visitorFunction,
                 std::shared_ptr<XsdAbstractElement> parent)
    : XsdStringRestrictions(parser, attributesMap, visitorFunction, parent)
  {
  }

public:
  void accept(std::shared_ptr<XsdAbstractElementVisitor> xsdAbstractElementVisitor) override;
    /**
     * Performs a copy of the current object for replacing purposes. The cloned objects are used to replace
     * {@link UnsolvedReference} objects in the reference solving process.
     * @param placeHolderAttributes The additional attributes to add to the clone.
     * @return A copy of the object from which is called upon.
     */
  std::shared_ptr<XsdEnumeration> clone(StringMap placeHolderAttributes);
  
};
