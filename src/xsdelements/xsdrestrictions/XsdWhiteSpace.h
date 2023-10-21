#pragma once



#include <core/utils/ParseData.h>
#include <xsdelements/AttributeValidations.h>
#include <xsdelements/XsdAbstractElement.h>
#include <xsdelements/XsdAnnotatedElements.h>
#include <xsdelements/elementswrapper/ReferenceBase.h>
#include <xsdelements/elementswrapper/UnsolvedReference.h>
#include <xsdelements/enums/WhiteSpaceEnum.h>
#include <xsdelements/visitors/XsdAbstractElementVisitor.h>

#include <xsdelements/XsdAnnotatedElements.h>

/**
 * States how the whiteSpace characters should be treated. The value is defined as an {@link std::string}.
 */
class XsdWhiteSpace : public XsdAnnotatedElements
{
public:
  using XsdAnnotatedElements::clone;
    constexpr static const std::string_view XSD_TAG = "xsd:whiteSpace";
    constexpr static const std::string_view XS_TAG = "xs:whiteSpace";
    constexpr static const std::string_view TAG = "whiteSpace";

private:
  bool m_fixed;
  WhiteSpaceEnum m_value;
public: // ctors
  XsdWhiteSpace(std::shared_ptr<XsdParserCore> parser,
                StringMap elementFieldsMapParam,
                VisitorFunctionReference visitorFunction,
                std::shared_ptr<XsdAbstractElement> parent)
        : XsdAnnotatedElements(parser, elementFieldsMapParam, visitorFunction, parent),
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
        xsdAbstractElementVisitor->visit(std::static_pointer_cast<XsdWhiteSpace>(shared_from_this()));
    }

    /**
     * Performs a copy of the current object for replacing purposes. The cloned objects are used to replace
     * {@link UnsolvedReference} objects in the reference solving process.
     * @param placeHolderAttributes The additional attributes to add to the clone.
     * @return A copy of the object from which is called upon.
     */
  std::shared_ptr<XsdWhiteSpace> clone(StringMap placeHolderAttributes)
    {
        placeHolderAttributes.merge(getAttributesMap());
        return create<XsdWhiteSpace>(getParser(),
                                     placeHolderAttributes,
                                     m_visitorFunction,
                                     nullptr);
    }

  static std::shared_ptr<ReferenceBase> parse(ParseData parseData)
  {
        return xsdParseSkeleton(parseData.node,
                                std::static_pointer_cast<XsdAbstractElement>(
                                  create<XsdWhiteSpace>(parseData.parserInstance,
                                                        getAttributesMap(parseData.node),
                                                        parseData.visitorFunction,
                                                        nullptr)));
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
