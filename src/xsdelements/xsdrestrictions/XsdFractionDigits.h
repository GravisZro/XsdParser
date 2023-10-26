#pragma once

#include <xsdelements/AttributeValidations.h>
#include <xsdelements/XsdAbstractElement.h>
#include <xsdelements/visitors/XsdAbstractElementVisitor.h>

#include <xsdelements/xsdrestrictions/XsdIntegerRestrictions.h>

/**
 * States the number of fraction digits allowed in a numeric type. The value is defined as an {@link int}.
 */
class XsdFractionDigits : public XsdIntegerRestrictions
{
public: // ctors
  XsdFractionDigits(std::shared_ptr<XsdParserCore> parser,
                    StringMap attributesMap,
                    VisitorFunctionType visitorFunction,
                    std::shared_ptr<XsdAbstractElement> parent)
        : XsdIntegerRestrictions(parser, attributesMap, visitorFunction, parent)
  {
  }

public:
  virtual void initialize(void) override
  {
    XsdIntegerRestrictions::initialize();
    assert(haveAttribute(VALUE_TAG));
    m_value = AttributeValidations::validateRequiredNonNegativeInteger(*TAG<XsdFractionDigits>::xsd, *VALUE_TAG, getAttribute(VALUE_TAG));
  }

  void accept(std::shared_ptr<XsdAbstractElementVisitor> xsdAbstractElementVisitor) override
    {
        XsdIntegerRestrictions::accept(xsdAbstractElementVisitor);
        xsdAbstractElementVisitor->visit(std::static_pointer_cast<XsdFractionDigits>(shared_from_this()));
    }

    /**
     * Performs a copy of the current object for replacing purposes. The cloned objects are used to replace
     * {@link UnsolvedReference} objects in the reference solving process.
     * @param placeHolderAttributes The additional attributes to add to the clone.
     * @return A copy of the object from which is called upon.
     */
  virtual std::shared_ptr<XsdAbstractElement> clone(StringMap placeHolderAttributes) override
  {
    placeHolderAttributes.merge(getAttributesMap());
    return create<XsdFractionDigits>(getParser(),
                                     placeHolderAttributes,
                                     m_visitorFunction,
                                     nullptr);
  }
};
