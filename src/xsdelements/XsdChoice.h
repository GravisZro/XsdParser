#pragma once

#include <xsdelements/elementswrapper/ReferenceBase.h>
#include <xsdelements/elementswrapper/UnsolvedReference.h>
#include <xsdelements/visitors/XsdAbstractElementVisitor.h>

#include <xsdelements/XsdMultipleElements.h>
#include <xsdelements/AttributeValidations.h>

class XsdSequence;
class XsdGroup;

/**
 * A class representing the xsd:choice element. Since it shares the same attributes as {@link XsdChoice} or
 * {@link XsdSequence} it extends {@link XsdMultipleElements}. For more information check {@link XsdMultipleElements}.
 *
 * @see <a href="https://www.w3schools.com/xml/el_choice.asp">xsd:choice element description and usage at w3c</a>
 */
class XsdChoice : public XsdMultipleElements
{
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
public: // ctors
  XsdChoice(std::shared_ptr<XsdParserCore> parser,
            StringMap attributesMap,
            VisitorFunctionType visitorFunction,
            std::shared_ptr<XsdAbstractElement> parent)
    : XsdMultipleElements(parser, attributesMap, visitorFunction, parent),
      m_minOccurs (INT_MIN)
  {
  }

public:
  virtual void initialize(void) override
  {
    XsdMultipleElements::initialize();
    m_minOccurs = 1;
    m_maxOccurs = "1";
    if(haveAttribute(MIN_OCCURS_TAG))
      m_minOccurs = AttributeValidations::validateNonNegativeInteger(*TAG<XsdChoice>::xsd, *MIN_OCCURS_TAG, getAttribute(MIN_OCCURS_TAG));

    if(haveAttribute(MAX_OCCURS_TAG))
      m_maxOccurs = AttributeValidations::maxOccursValidation(*TAG<XsdChoice>::xsd, getAttribute(MAX_OCCURS_TAG));
  }

  void accept(std::shared_ptr<XsdAbstractElementVisitor> visitorParam) override
    {
        XsdMultipleElements::accept(visitorParam);
        visitorParam->visit(std::static_pointer_cast<XsdChoice>(shared_from_this()));
    }

  virtual std::shared_ptr<XsdAbstractElement> clone(StringMap placeHolderAttributes) override;


  int getMinOccurs(void) {
        return m_minOccurs;
    }

  std::string getMaxOccurs(void) {
        return m_maxOccurs;
    }

  std::list<std::shared_ptr<XsdChoice>> getChildrenChoices(void);
  std::list<std::shared_ptr<XsdSequence>> getChildrenSequences(void);
  std::list<std::shared_ptr<XsdGroup>> getChildrenGroups(void);
};
