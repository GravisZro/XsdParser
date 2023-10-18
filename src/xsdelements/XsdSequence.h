#pragma once


//#include <core/XsdParserCore.h>
#include <core/utils/ParseData.h>
#include <xsdelements/elementswrapper/ReferenceBase.h>
#include <xsdelements/elementswrapper/UnsolvedReference.h>
#include <xsdelements/visitors/XsdAbstractElementVisitor.h>
#include <xsdelements/XsdMultipleElements.h>

#include <xsdelements/AttributeValidations.h>


/**
 * A class representing the xsd:sequence element. Since it shares the same attributes as {@link XsdAll} or
 * {@link XsdChoice} it extends {@link XsdMultipleElements}. For more information check {@link XsdMultipleElements}.
 *
 * @see <a href="https://www.w3schools.com/xml/el_sequence.asp">xsd:sequence description and usage at w3c</a>
 */
class XsdSequence : public XsdMultipleElements
{
public:
  using XsdMultipleElements::clone;
    constexpr static const std::string_view XSD_TAG = "xsd:sequence";
    constexpr static const std::string_view XS_TAG = "xs:sequence";
    constexpr static const std::string_view TAG = "sequence";

private:
    /**
     * Specifies the minimum number of times this element can occur in the parent element. The value can be any
     * number bigger or equal to 0. Default value is 1. This attribute cannot be used if the parent element is the
     * XsdSchema element.
     */
    int m_minOccurs;

    /**
     * Specifies the maximum number of times this element can occur in the parent element. The value can be any
     * number bigger or equal to 0, or if you want to set no limit on the maximum number, use the value "unbounded".
     * Default value is 1. This attribute cannot be used if the parent element is the XsdSchema element.
     */
    std::string m_maxOccurs;
public:
    XsdSequence(std::shared_ptr<XsdParserCore> parser, StringMap attributesMap, VisitorFunctionReference visitorFunction)
      : XsdMultipleElements(parser, attributesMap, visitorFunction),
        m_minOccurs(1),
        m_maxOccurs("1")
    {
      if(attributesMap.contains(*MIN_OCCURS_TAG))
        m_minOccurs = AttributeValidations::validateNonNegativeInteger(*XSD_TAG, *MIN_OCCURS_TAG, attributesMap.at(*MIN_OCCURS_TAG));

      if(m_attributesMap.contains(*MAX_OCCURS_TAG))
        m_maxOccurs = AttributeValidations::maxOccursValidation(*XSD_TAG, attributesMap.at(*MAX_OCCURS_TAG));
    }
public:
  void accept(std::shared_ptr<XsdAbstractElementVisitor> visitorParam)
    {
        XsdMultipleElements::accept(visitorParam);
        visitorParam->visit(std::shared_ptr<XsdSequence>(this));
    }

    /**
     * Performs a copy of the current object for replacing purposes. The cloned objects are used to replace
     * {@link UnsolvedReference} objects in the reference solving process.
     * @param placeHolderAttributes The additional attributes to add to the clone.
     * @return A copy of the object from which is called upon.
     */
  std::shared_ptr<XsdSequence> clone(StringMap placeHolderAttributes)
    {
        placeHolderAttributes.merge(m_attributesMap);

        auto elementCopy = std::make_shared<XsdSequence>(getParser(), placeHolderAttributes, m_visitorFunction);

        for(auto& element : getElements())
            elementCopy->m_elements.push_back(ReferenceBase::clone(m_parser, element, elementCopy));

        elementCopy->m_cloneOf = std::shared_ptr<XsdAbstractElement>(this);
        elementCopy->setParent(nullptr);

        return elementCopy;
    }

  static std::shared_ptr<ReferenceBase> parse(ParseData parseData)
  {
        return xsdParseSkeleton(parseData.node, std::static_pointer_cast<XsdAbstractElement>(std::make_shared<XsdSequence>(parseData.parserInstance, XsdAbstractElement::getAttributesMap(parseData.node), parseData.visitorFunction)));
    }

  int getMinOccurs(void) {
        return m_minOccurs;
    }

  std::string getMaxOccurs(void) {
        return m_maxOccurs;
    }

    /**
     * @return The children elements that are of the type {@link XsdChoice}.
     */
  std::list<std::shared_ptr<XsdChoice>> getChildrenChoices(void)
  {
    std::list<std::shared_ptr<XsdChoice>> rval;
    for(auto& element : getXsdElements())
      if(auto x = std::dynamic_pointer_cast<XsdChoice>(element); x)
        rval.push_back(x);
    return rval;
  }

    /**
     * @return The children elements that are of the type {@link XsdSequence}.
     */
  std::list<std::shared_ptr<XsdSequence>> getChildrenSequences(void)
  {
    std::list<std::shared_ptr<XsdSequence>> rval;
    for(auto& element : getXsdElements())
      if(auto x = std::dynamic_pointer_cast<XsdSequence>(element); x)
        rval.push_back(x);
    return rval;
  }

    /**
     * @return The children elements that are of the type {@link XsdGroup}.
     */
  std::list<std::shared_ptr<XsdGroup>> getChildrenGroups(void)
  {
    std::list<std::shared_ptr<XsdGroup>> rval;
    for(auto& element : getXsdElements())
      if(auto x = std::dynamic_pointer_cast<XsdGroup>(element); x)
        rval.push_back(x);
    return rval;
  }
};
