#pragma once



#include <xsdelements/AttributeValidations.h>
#include <xsdelements/XsdAbstractElement.h>
#include <xsdelements/elementswrapper/ReferenceBase.h>
#include <xsdelements/elementswrapper/UnsolvedReference.h>
#include <xsdelements/visitors/XsdAbstractElementVisitor.h>

#include <xsdelements/xsdrestrictions/XsdIntegerRestrictions.h>

/**
 * States the exact number of length to a given type, either a {@link std::string}, a {@link List}, or another measurable type.
 * The value is defined as an {@link int}.
 */
class XsdLength : public XsdIntegerRestrictions
{
public:
  using XsdIntegerRestrictions::clone;
  constexpr static const std::string_view XSD_TAG = "xsd:length";
  constexpr static const std::string_view XS_TAG = "xs:length";
  constexpr static const std::string_view TAG = "length";

public: // ctors
  XsdLength(std::shared_ptr<XsdParserCore> parser,
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
    m_value = AttributeValidations::validateRequiredNonNegativeInteger(*XSD_TAG, *VALUE_TAG, getAttribute(VALUE_TAG));
  }

  void accept(std::shared_ptr<XsdAbstractElementVisitor> xsdAbstractElementVisitor) override
    {
        XsdIntegerRestrictions::accept(xsdAbstractElementVisitor);
        xsdAbstractElementVisitor->visit(std::static_pointer_cast<XsdLength>(shared_from_this()));
    }

    /**
     * Performs a copy of the current object for replacing purposes. The cloned objects are used to replace
     * {@link UnsolvedReference} objects in the reference solving process.
     * @param placeHolderAttributes The additional attributes to add to the clone.
     * @return A copy of the object from which is called upon.
     */
  std::shared_ptr<XsdLength> clone(StringMap placeHolderAttributes)
  {
    placeHolderAttributes.merge(getAttributesMap());
    return create<XsdLength>(getParser(),
                             placeHolderAttributes,
                             m_visitorFunction,
                             nullptr);
  }
};
