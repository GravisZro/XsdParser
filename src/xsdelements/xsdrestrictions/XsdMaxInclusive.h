#pragma once


//#include <core/XsdParserCore.h>
#include <core/utils/ParseData.h>
#include <xsdelements/AttributeValidations.h>
#include <xsdelements/XsdAbstractElement.h>
#include <xsdelements/elementswrapper/ReferenceBase.h>
#include <xsdelements/elementswrapper/UnsolvedReference.h>
#include <xsdelements/visitors/XsdAbstractElementVisitor.h>
#include <xsdelements/xsdrestrictions/XsdStringRestrictions.h>


#include <map>
#include <functional>

/**
 * States the maximum value that a given type might take, including the respective value. The value is defined
 * as a {@link std::string}.
 * Example: If the type has a {@link XsdMaxInclusive#value} of 5 it means that the maximum value it can take is 5.
 */
class XsdMaxInclusive : public XsdStringRestrictions
{
public:
    constexpr static const std::string_view XSD_TAG = "xsd:maxInclusive";
    constexpr static const std::string_view XS_TAG = "xs:maxInclusive";
    constexpr static const std::string_view TAG = "maxInclusive";

private:
    /**
     * Indicates if the value is fixed.
     */
    bool m_fixed;

    XsdMaxInclusive(std::shared_ptr<XsdParserCore> parser,
                    StringMap elementFieldsMapParam,
                    VisitorFunctionReference visitorFunction)
        : XsdStringRestrictions(parser, elementFieldsMapParam, visitorFunction),
          m_fixed(false)
  {
    if(m_attributesMap.contains(*FIXED_TAG))
      m_fixed = AttributeValidations::validateBoolean(elementFieldsMapParam.at(*FIXED_TAG));
  }

  void accept(std::shared_ptr<XsdAbstractElementVisitor> xsdAbstractElementVisitor)
    {
        XsdStringRestrictions::accept(xsdAbstractElementVisitor);
        xsdAbstractElementVisitor->visit(std::shared_ptr<XsdMaxInclusive>(this));
    }

    /**
     * Performs a copy of the current object for replacing purposes. The cloned objects are used to replace
     * {@link UnsolvedReference} objects in the reference solving process.
     * @param placeHolderAttributes The additional attributes to add to the clone.
     * @return A copy of the object from which is called upon.
     */
  std::shared_ptr<XsdMaxInclusive> clone(StringMap placeHolderAttributes)
    {
        placeHolderAttributes.merge(m_attributesMap);

        auto elementCopy = std::make_shared<XsdMaxInclusive>(getParser(), placeHolderAttributes, m_visitorFunction);

        elementCopy->setParent(nullptr);

        return elementCopy;
    }

  static std::shared_ptr<ReferenceBase> parse(ParseData parseData)
  {
        return xsdParseSkeleton(parseData.node, std::static_pointer_cast<XsdAbstractElement>(std::make_shared<XsdMaxInclusive>(parseData.parserInstance, XsdAbstractElement::getAttributesMap(parseData.node), parseData.visitorFunction)));
    }

  bool isFixed(void) {
        return m_fixed;
    }
};
