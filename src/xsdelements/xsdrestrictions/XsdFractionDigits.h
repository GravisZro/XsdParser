#pragma once



#include <core/utils/ParseData.h>
#include <xsdelements/AttributeValidations.h>
#include <xsdelements/XsdAbstractElement.h>
#include <xsdelements/elementswrapper/ReferenceBase.h>
#include <xsdelements/elementswrapper/UnsolvedReference.h>
#include <xsdelements/visitors/XsdAbstractElementVisitor.h>

#include <xsdelements/xsdrestrictions/XsdIntegerRestrictions.h>

/**
 * States the number of fraction digits allowed in a numeric type. The value is defined as an {@link int}.
 */
class XsdFractionDigits : public XsdIntegerRestrictions
{
public:
  using XsdIntegerRestrictions::clone;
    constexpr static const std::string_view XSD_TAG = "xsd:fractionDigits";
    constexpr static const std::string_view XS_TAG = "xs:fractionDigits";
    constexpr static const std::string_view TAG = "fractionDigits";

public: // ctors
  XsdFractionDigits(std::shared_ptr<XsdParserCore> parser,
                    StringMap elementFieldsMapParam,
                    VisitorFunctionReference visitorFunction)
        : XsdIntegerRestrictions(parser, elementFieldsMapParam, visitorFunction)
  {
    assert(haveAttribute(VALUE_TAG));
    m_value = AttributeValidations::validateRequiredNonNegativeInteger(*XSD_TAG, *VALUE_TAG, getAttribute(VALUE_TAG));
  }

public:
  void accept(std::shared_ptr<XsdAbstractElementVisitor> xsdAbstractElementVisitor)
    {
        XsdIntegerRestrictions::accept(xsdAbstractElementVisitor);
        xsdAbstractElementVisitor->visit(std::static_pointer_cast<XsdFractionDigits>(shared_from_this()));
    }

    /**
     * Performs a copy of the current object for replacing purposes. The cloned objects are used to replace
     * {@link UnsolvedReference} objects in the reference solving process.
     * @param placeHolderAttributes The additional attributes to add to the clone.
     * @return A copy of the object from which is called upon.
     */
  std::shared_ptr<XsdFractionDigits> clone(StringMap placeHolderAttributes)
    {
        placeHolderAttributes.merge(getAttributesMap());
        auto elementCopy = create<XsdFractionDigits>(getParser(),
                                                     placeHolderAttributes,
                                                     m_visitorFunction);
        elementCopy->setParent(nullptr);
        return elementCopy;
    }

  static std::shared_ptr<ReferenceBase> parse(ParseData parseData)
  {
        return xsdParseSkeleton(parseData.node,
                                std::static_pointer_cast<XsdAbstractElement>(
                                  create<XsdFractionDigits>(parseData.parserInstance,
                                                            getAttributesMap(parseData.node),
                                                            parseData.visitorFunction)));
    }
};
