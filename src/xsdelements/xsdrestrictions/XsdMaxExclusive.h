#pragma once




#include <xsdelements/AttributeValidations.h>
#include <xsdelements/XsdAbstractElement.h>
#include <xsdelements/elementswrapper/ReferenceBase.h>
#include <xsdelements/elementswrapper/UnsolvedReference.h>
#include <xsdelements/visitors/XsdAbstractElementVisitor.h>

#include <xsdelements/xsdrestrictions/XsdStringRestrictions.h>

/**
 * States the maximum value that a given type might take, excluding the respective value. The value is defined
 * as a {@link std::string}.
 * Example: If the type has a {@link XsdMaxExclusive#value} of 5 it means that the maximum value it can take is
 * 4.9999(9).
 */
class XsdMaxExclusive : public XsdStringRestrictions
{
public:
  using XsdStringRestrictions::clone;
    constexpr static const std::string_view XSD_TAG = "xsd:maxExclusive";
    constexpr static const std::string_view XS_TAG = "xs:maxExclusive";
    constexpr static const std::string_view TAG = "maxExclusive";

private:
    /**
     * Indicates if the value is fixed.
     */
    bool m_fixed;
public: // ctors
  XsdMaxExclusive(std::shared_ptr<XsdParserCore> parser,
                  StringMap attributesMap,
                  VisitorFunctionType visitorFunction,
                  std::shared_ptr<XsdAbstractElement> parent)
      : XsdStringRestrictions(parser, attributesMap, visitorFunction, parent),
        m_fixed(false)
  {
  }
public:
  virtual void initialize(void) override
  {
    XsdStringRestrictions::initialize();
    m_fixed = false;
    if(haveAttribute(FIXED_TAG))
      m_fixed = AttributeValidations::validateBoolean(getAttribute(FIXED_TAG));
  }
public:
  void accept(std::shared_ptr<XsdAbstractElementVisitor> xsdAbstractElementVisitor) override
    {
        XsdStringRestrictions::accept(xsdAbstractElementVisitor);
        xsdAbstractElementVisitor->visit(std::static_pointer_cast<XsdMaxExclusive>(shared_from_this()));
    }

    /**
     * Performs a copy of the current object for replacing purposes. The cloned objects are used to replace
     * {@link UnsolvedReference} objects in the reference solving process.
     * @param placeHolderAttributes The additional attributes to add to the clone.
     * @return A copy of the object from which is called upon.
     */
  std::shared_ptr<XsdMaxExclusive> clone(StringMap placeHolderAttributes)
  {
    placeHolderAttributes.merge(getAttributesMap());
    return create<XsdMaxExclusive>(getParser(),
                                   placeHolderAttributes,
                                   m_visitorFunction,
                                   nullptr);
  }

  bool isFixed(void) {
        return m_fixed;
    }
};
