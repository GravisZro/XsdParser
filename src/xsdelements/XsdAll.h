#pragma once

#include <xsdelements/XsdMultipleElements.h>

#include <map>
#include <string>
#include <functional>

class XsdAbstractElementVisitor;
class XsdAbstractElement;
class XsdParserCore;

/**
 * A class representing the xsd:all element. Since it shares the same attributes as {@link XsdChoice} or {@link XsdSequence}
 * it extends {@link XsdMultipleElements}. For more information check {@link XsdMultipleElements}.
 *
 * @see <a href="https://www.w3schools.com/xml/el_all.asp">xsd:all element definition and usage</a>
 */
class XsdAll : public XsdMultipleElements
{
public:
  using XsdMultipleElements::clone;
    constexpr static const std::string_view XSD_TAG = "xsd:all";
    constexpr static const std::string_view XS_TAG = "xs:all";
    constexpr static const std::string_view TAG = "all";

private:
    /**
     * Specifies the minimum number of times this element can occur in the parent element. The value can be any
     * number bigger or equal to 0. Default value is 1. This attribute cannot be used if the parent element is the
     * std::shared_ptr<XsdSchema> element.
     */
    int m_minOccurs;

    /**
     * Specifies the maximum number of times this element can occur in the parent element. The value can be any
     * number bigger or equal to 0. Default value is 1. This attribute cannot be used if the parent element is the
     * std::shared_ptr<XsdSchema> element.
     */
    int m_maxOccurs;

    XsdAll(std::shared_ptr<XsdParserCore> parser,
           StringMap attributesMap,
           VisitorFunctionReference visitorFunction);
public:
  void accept(std::shared_ptr<XsdAbstractElementVisitor> visitorParam);

  static std::shared_ptr<ReferenceBase> parse(ParseData parseData);

    /**
     * Performs a copy of the current object for replacing purposes. The cloned objects are used to replace
     * {@link UnsolvedReference} objects in the reference solving process.
     * @param placeHolderAttributes The additional attributes to add to the clone.
     * @return A copy of the object from which is called upon.
     */
  std::shared_ptr<XsdAll> clone(StringMap placeHolderAttributes);

    // @SuppressWarnings("unused")
  int getMinOccurs(void) {
        return m_minOccurs;
    }

    // @SuppressWarnings("unused")
  int getMaxOccurs(void) {
        return m_maxOccurs;
    }
};
