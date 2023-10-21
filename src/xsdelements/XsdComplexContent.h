#pragma once


#include <core/utils/ParseData.h>
#include <xsdelements/elementswrapper/ConcreteElement.h>
#include <xsdelements/elementswrapper/ReferenceBase.h>
#include <xsdelements/elementswrapper/UnsolvedReference.h>
#include <xsdelements/visitors/XsdAbstractElementVisitor.h>

#include <xsdelements/XsdAnnotatedElements.h>

/**
 * A class representing the xsd:complexContent element.
 *
 * @see <a href="https://www.w3schools.com/xml/el_complexcontent.asp">xsd:complexContent element description and usage at w3c</a>
 */
class XsdComplexContent : public XsdAnnotatedElements
{
public:
  using XsdAnnotatedElements::clone;
    constexpr static const std::string_view XSD_TAG = "xsd:complexContent";
    constexpr static const std::string_view XS_TAG = "xs:complexContent";
    constexpr static const std::string_view TAG = "complexContent";

private:
    /**
     * A {@link XsdRestriction} object wrapped in a {@link ReferenceBase} object.
     */
    std::shared_ptr<ReferenceBase> m_restriction;

    /**
     * A {@link XsdExtension} object wrapped in a {@link ReferenceBase} object.
     */
    std::shared_ptr<ReferenceBase> m_extension;

    /**
     * Specifies whether character data is allowed to appear between the child elements of this element.
     */
    bool m_mixed;
public: // ctors
    XsdComplexContent(std::shared_ptr<XsdParserCore> parser,
                      StringMap attributesMap,
                      VisitorFunctionReference visitorFunction,
                      std::shared_ptr<XsdAbstractElement> parent);
public:
  void accept(std::shared_ptr<XsdAbstractElementVisitor> visitorParam)
    {
        XsdAnnotatedElements::accept(visitorParam);
        visitorParam->visit(std::static_pointer_cast<XsdComplexContent>(shared_from_this()));
    }

  std::shared_ptr<XsdComplexContent> clone(StringMap placeHolderAttributes);

  bool isMixed(void) {
        return m_mixed;
    }

  std::shared_ptr<XsdExtension> getXsdExtension(void);
  std::shared_ptr<XsdRestriction> getXsdRestriction(void);

  static std::shared_ptr<ReferenceBase> parse(ParseData parseData)
  {
    return xsdParseSkeleton(parseData.node,
                            std::static_pointer_cast<XsdAbstractElement>(
                              create<XsdComplexContent>(parseData.parserInstance,
                                                        getAttributesMap(parseData.node),
                                                        parseData.visitorFunction,
                                                        nullptr)));
  }

  void setExtension(std::shared_ptr<ReferenceBase> extension) {
        m_extension = extension;
    }

  void setRestriction(std::shared_ptr<ReferenceBase> restriction) {
        m_restriction = restriction;
    }
};
