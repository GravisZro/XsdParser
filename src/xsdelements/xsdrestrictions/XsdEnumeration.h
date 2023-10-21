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
  using XsdStringRestrictions::clone;
    constexpr static const std::string_view XSD_TAG = "xsd:enumeration";
    constexpr static const std::string_view XS_TAG = "xs:enumeration";
    constexpr static const std::string_view TAG = "enumeration";

public: // ctors
  XsdEnumeration(std::shared_ptr<XsdParserCore> parser,
                 StringMap elementFieldsMapParam,
                 VisitorFunctionType visitorFunction,
                 std::shared_ptr<XsdAbstractElement> parent);

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
