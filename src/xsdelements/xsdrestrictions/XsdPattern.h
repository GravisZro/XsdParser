#pragma once



#include <core/utils/ParseData.h>
#include <xsdelements/XsdAbstractElement.h>
#include <xsdelements/elementswrapper/ReferenceBase.h>
#include <xsdelements/elementswrapper/UnsolvedReference.h>
#include <xsdelements/visitors/XsdAbstractElementVisitor.h>

#include <xsdelements/xsdrestrictions/XsdStringRestrictions.h>


/**
 * States a pattern that a given attribute must match in order to be considered valid. The value is defined as a
 * {@link std::string}. This value is usually defined as a regular expression.
 */
class XsdPattern : public XsdStringRestrictions
{
public:
  using XsdStringRestrictions::clone;
  constexpr static const std::string_view XSD_TAG = "xsd:pattern";
  constexpr static const std::string_view XS_TAG = "xs:pattern";
  constexpr static const std::string_view TAG = "pattern";

public: // ctors
  XsdPattern(std::shared_ptr<XsdParserCore> parser,
             StringMap elementFieldsMapParam,
             VisitorFunctionReference visitorFunction)
    : XsdStringRestrictions(parser, elementFieldsMapParam, visitorFunction)
  { }
public:
  void accept(std::shared_ptr<XsdAbstractElementVisitor> xsdAbstractElementVisitor)
    {
        XsdStringRestrictions::accept(xsdAbstractElementVisitor);
        xsdAbstractElementVisitor->visit(std::static_pointer_cast<XsdPattern>(shared_from_this()));
    }

    /**
     * Performs a copy of the current object for replacing purposes. The cloned objects are used to replace
     * {@link UnsolvedReference} objects in the reference solving process.
     * @param placeHolderAttributes The additional attributes to add to the clone.
     * @return A copy of the object from which is called upon.
     */
  std::shared_ptr<XsdPattern> clone(StringMap placeHolderAttributes)
    {
        placeHolderAttributes.merge(getAttributesMap());
        auto elementCopy = create<XsdPattern>(getParser(),
                                                        placeHolderAttributes,
                                                        m_visitorFunction);
        elementCopy->setParent(nullptr);
        return elementCopy;
    }

  static std::shared_ptr<ReferenceBase> parse(ParseData parseData)
  {
        return xsdParseSkeleton(parseData.node,
                                std::static_pointer_cast<XsdAbstractElement>(
                                  create<XsdPattern>(parseData.parserInstance,
                                                     getAttributesMap(parseData.node),
                                                     parseData.visitorFunction)));
    }
};
