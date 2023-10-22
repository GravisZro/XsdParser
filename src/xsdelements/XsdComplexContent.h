#pragma once

#include <xsdelements/elementswrapper/ConcreteElement.h>
#include <xsdelements/elementswrapper/ReferenceBase.h>
#include <xsdelements/elementswrapper/UnsolvedReference.h>
#include <xsdelements/visitors/XsdAbstractElementVisitor.h>

#include <xsdelements/XsdAnnotatedElements.h>
#include <xsdelements/AttributeValidations.h>

class XsdExtension;
class XsdRestriction;

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
                    VisitorFunctionType visitorFunction,
                    std::shared_ptr<XsdAbstractElement> parent)
    : XsdAnnotatedElements(parser, attributesMap, visitorFunction, parent),
      m_mixed(false)
  {
  }

public:
  virtual void initialize(void) override
  {
    XsdAnnotatedElements::initialize();
    m_restriction.reset();
    m_extension.reset();
    m_mixed = false;
    if(haveAttribute(MIXED_TAG))
      m_mixed = AttributeValidations::validateBoolean(getAttribute(MIXED_TAG));
  }

  void accept(std::shared_ptr<XsdAbstractElementVisitor> visitorParam) override
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


  void setExtension(std::shared_ptr<ReferenceBase> extension) {
        m_extension = extension;
    }

  void setRestriction(std::shared_ptr<ReferenceBase> restriction) {
        m_restriction = restriction;
    }
};
