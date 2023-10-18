#pragma once


//#include <core/XsdParserCore.h>
#include <core/utils/ParseData.h>
#include <xsdelements/AttributeValidations.h>
#include <xsdelements/XsdAbstractElement.h>
#include <xsdelements/XsdAnnotatedElements.h>
#include <xsdelements/elementswrapper/ReferenceBase.h>
#include <xsdelements/elementswrapper/UnsolvedReference.h>
#include <xsdelements/enums/WhiteSpaceEnum.h>
#include <xsdelements/visitors/XsdAbstractElementVisitor.h>


#include <map>
#include <functional>

/**
 * States how the whiteSpace characters should be treated. The value is defined as an {@link std::string}.
 */
class XsdWhiteSpace : public XsdAnnotatedElements
{
public:
    constexpr static const std::string_view XSD_TAG = "xsd:whiteSpace";
    constexpr static const std::string_view XS_TAG = "xs:whiteSpace";
    constexpr static const std::string_view TAG = "whiteSpace";

private:
  bool m_fixed;
  WhiteSpaceEnum m_value;

  XsdWhiteSpace(std::shared_ptr<XsdParserCore> parser,
                StringMap elementFieldsMapParam,
                VisitorFunctionReference visitorFunction)
        : XsdAnnotatedElements(parser, elementFieldsMapParam, visitorFunction),
          m_fixed(false)
  {
    if(elementFieldsMapParam.contains(*FIXED_TAG))
      m_fixed = AttributeValidations::validateBoolean(elementFieldsMapParam.at(*FIXED_TAG));
    if(elementFieldsMapParam.contains(*VALUE_TAG))
      m_value = AttributeValidations::belongsToEnum<WhiteSpaceEnum>(elementFieldsMapParam.at(*VALUE_TAG));
  }
public:
  void accept(std::shared_ptr<XsdAbstractElementVisitor> xsdAbstractElementVisitor)
    {
        XsdAnnotatedElements::accept(xsdAbstractElementVisitor);
        xsdAbstractElementVisitor->visit(std::shared_ptr<XsdWhiteSpace>(this));
    }

    /**
     * Performs a copy of the current object for replacing purposes. The cloned objects are used to replace
     * {@link UnsolvedReference} objects in the reference solving process.
     * @param placeHolderAttributes The additional attributes to add to the clone.
     * @return A copy of the object from which is called upon.
     */
  std::shared_ptr<XsdWhiteSpace> clone(StringMap placeHolderAttributes)
    {
        placeHolderAttributes.merge(m_attributesMap);

        auto elementCopy = std::make_shared<XsdWhiteSpace>(getParser(), placeHolderAttributes, m_visitorFunction);

        elementCopy->setParent(nullptr);

        return elementCopy;
    }

  static std::shared_ptr<ReferenceBase> parse(ParseData parseData)
  {
        return xsdParseSkeleton(parseData.node, std::static_pointer_cast<XsdAbstractElement>(std::make_shared<XsdWhiteSpace>(parseData.parserInstance, XsdAbstractElement::getAttributesMap(parseData.node), parseData.visitorFunction)));
    }

  bool isFixed(void) {
        return m_fixed;
    }

  WhiteSpaceEnum getValue(void) {
        return m_value;
    }

  static bool hasDifferentValue(std::shared_ptr<XsdWhiteSpace> o1, std::shared_ptr<XsdWhiteSpace> o2)
  {
    if (o1 && o2)
      return o1->getValue() == o2->getValue();
    return false;
  }
};
