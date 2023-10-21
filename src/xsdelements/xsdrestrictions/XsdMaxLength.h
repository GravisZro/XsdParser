#pragma once



#include <core/utils/ParseData.h>
#include <xsdelements/AttributeValidations.h>
#include <xsdelements/XsdAbstractElement.h>
#include <xsdelements/elementswrapper/ReferenceBase.h>
#include <xsdelements/elementswrapper/UnsolvedReference.h>
#include <xsdelements/visitors/XsdAbstractElementVisitor.h>

#include <xsdelements/xsdrestrictions/XsdIntegerRestrictions.h>

/**
 * States the maximum length of a given type, either a {@link std::string}, a {@link List} or another measurable type.
 * This limit including the respective value. The value is defined as an {@link int}.
 * Example: If the type has a {@link XsdMaxLength#value} of 5 it means that the {@link std::string}, {@link List} or another
 * measurable type should have a maximum length of 5.
 */
class XsdMaxLength : public XsdIntegerRestrictions
{
public:
  using XsdIntegerRestrictions::clone;
    constexpr static const std::string_view XSD_TAG = "xsd:maxLength";
    constexpr static const std::string_view XS_TAG = "xs:maxLength";
    constexpr static const std::string_view TAG = "maxLength";

public: // ctors
  XsdMaxLength(std::shared_ptr<XsdParserCore> parser,
               StringMap elementFieldsMapParam,
               VisitorFunctionReference visitorFunction,
               std::shared_ptr<XsdAbstractElement> parent)
        : XsdIntegerRestrictions(parser, elementFieldsMapParam, visitorFunction, parent)
  {
    assert(haveAttribute(VALUE_TAG));
        m_value = AttributeValidations::validateRequiredNonNegativeInteger(*XSD_TAG, *VALUE_TAG, getAttribute(VALUE_TAG));
    }
public:
  void accept(std::shared_ptr<XsdAbstractElementVisitor> xsdAbstractElementVisitor)
    {
        XsdIntegerRestrictions::accept(xsdAbstractElementVisitor);
        xsdAbstractElementVisitor->visit(std::static_pointer_cast<XsdMaxLength>(shared_from_this()));
    }

    /**
     * Performs a copy of the current object for replacing purposes. The cloned objects are used to replace
     * {@link UnsolvedReference} objects in the reference solving process.
     * @param placeHolderAttributes The additional attributes to add to the clone.
     * @return A copy of the object from which is called upon.
     */
  std::shared_ptr<XsdMaxLength> clone(StringMap placeHolderAttributes)
    {
        placeHolderAttributes.merge(getAttributesMap());
        return create<XsdMaxLength>(getParser(),
                                    placeHolderAttributes,
                                    m_visitorFunction,
                                    nullptr);
    }

  static std::shared_ptr<ReferenceBase> parse(ParseData parseData)
  {
        return xsdParseSkeleton(parseData.node,
                                std::static_pointer_cast<XsdAbstractElement>(
                                  create<XsdMaxLength>(parseData.parserInstance,
                                                       getAttributesMap(parseData.node),
                                                       parseData.visitorFunction,
                                                       nullptr)));
    }
};
