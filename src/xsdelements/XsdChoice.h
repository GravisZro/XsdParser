#pragma once


//#include <core/XsdParserCore.h>
#include <core/utils/ParseData.h>
#include <xsdelements/elementswrapper/ReferenceBase.h>
#include <xsdelements/elementswrapper/UnsolvedReference.h>
#include <xsdelements/visitors/XsdAbstractElementVisitor.h>

#include <xsdelements/XsdMultipleElements.h>
#include <xsdelements/AttributeValidations.h>

#include <map>
#include <functional>
// import java.util.stream.Stream;

/**
 * A class representing the xsd:choice element. Since it shares the same attributes as {@link XsdChoice} or
 * {@link XsdSequence} it extends {@link XsdMultipleElements}. For more information check {@link XsdMultipleElements}.
 *
 * @see <a href="https://www.w3schools.com/xml/el_choice.asp">xsd:choice element description and usage at w3c</a>
 */
class XsdChoice : public XsdMultipleElements
{
public:
  using XsdMultipleElements::clone;
    constexpr static const std::string_view XSD_TAG = "xsd:choice";
    constexpr static const std::string_view XS_TAG = "xs:choice";
    constexpr static const std::string_view TAG = "choice";

private:
    /**
     * Specifies the minimum number of times this element can occur in the parent element. The value can be any
     * number bigger or equal to 0. Default value is 1. This attribute cannot be used if the parent element is the
     * std::shared_ptr<XsdSchema> element.
     */
    int m_minOccurs;

    /**
     * Specifies the maximum number of times this element can occur in the parent element. The value can be any
     * number bigger or equal to 0, or if you want to set no limit on the maximum number, use the value "unbounded".
     * Default value is 1. This attribute cannot be used if the parent element is the std::shared_ptr<XsdSchema> element.
     */
    std::string m_maxOccurs;

    XsdChoice(std::shared_ptr<XsdParserCore> parser,
              StringMap attributesMap,
              VisitorFunctionReference visitorFunction)
        : XsdMultipleElements(parser, attributesMap, visitorFunction),
          m_minOccurs(1),
          m_maxOccurs("1")
    {
      if(attributesMap.contains(*MIN_OCCURS_TAG))
        m_minOccurs = AttributeValidations::validateNonNegativeInteger(*XSD_TAG, *MIN_OCCURS_TAG, attributesMap.at(*MIN_OCCURS_TAG));

      if(attributesMap.contains(*MAX_OCCURS_TAG))
        m_maxOccurs = AttributeValidations::maxOccursValidation(*XSD_TAG, attributesMap.at(*MAX_OCCURS_TAG));
    }
public:
  void accept(std::shared_ptr<XsdAbstractElementVisitor> visitorParam)
    {
        XsdMultipleElements::accept(visitorParam);
        visitorParam->visit(std::shared_ptr<XsdChoice>(this));
    }

    /**
     * Performs a copy of the current object for replacing purposes. The cloned objects are used to replace
     * {@link UnsolvedReference} objects in the reference solving process.
     * @param placeHolderAttributes The additional attributes to add to the clone.
     * @return A copy of the object from which is called upon.
     */
  std::shared_ptr<XsdChoice> clone(StringMap placeHolderAttributes)
    {
        placeHolderAttributes.merge(m_attributesMap);

        auto elementCopy = std::make_shared<XsdChoice>(getParser(), placeHolderAttributes, m_visitorFunction);
        for(auto& element : getElements())
            elementCopy->m_elements.push_back(ReferenceBase::clone(m_parser, element, elementCopy));

        elementCopy->setParent(nullptr);

        return elementCopy;
    }

  static std::shared_ptr<ReferenceBase> parse(ParseData parseData)
{
        return xsdParseSkeleton(parseData.node, std::static_pointer_cast<XsdAbstractElement>(std::make_shared<XsdChoice>(parseData.parserInstance, XsdAbstractElement::getAttributesMap(parseData.node), parseData.visitorFunction)));
    }

    // @SuppressWarnings("unused")
  int getMinOccurs(void) {
        return m_minOccurs;
    }

    // @SuppressWarnings("unused")
  std::string getMaxOccurs(void) {
        return m_maxOccurs;
    }

    /**
     * @return The children elements that are of the type {@link XsdChoice}.
     */
    // @SuppressWarnings("unused")
  std::list<std::shared_ptr<XsdChoice>> getChildrenChoices(){
        return getXsdElements().filter(element -> element instanceof XsdChoice).map(element -> (XsdChoice) element);
    }

    /**
     * @return The children elements that are of the type {@link XsdSequence}.
     */
    // @SuppressWarnings("unused")
  std::list<std::shared_ptr<XsdSequence>> getChildrenSequences(){
        return getXsdElements().filter(element -> element instanceof XsdSequence).map(element -> (XsdSequence) element);
    }

    /**
     * @return The children elements that are of the type {@link XsdGroup}.
     */
    // @SuppressWarnings("unused")
  std::list<std::shared_ptr<XsdGroup>> getChildrenGroups(){
        return getXsdElements().filter(element -> element instanceof XsdGroup).map(element -> (XsdGroup) element);
    }
};
