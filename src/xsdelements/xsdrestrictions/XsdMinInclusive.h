#pragma once

#include <xsdelements/AttributeValidations.h>
#include <xsdelements/XsdAbstractElement.h>
#include <xsdelements/visitors/XsdAbstractElementVisitor.h>

#include <xsdelements/xsdrestrictions/XsdStringRestrictions.h>

/**
 * States the minimum value that a given type might take, including the respective value. The value is defined
 * as a {@link std::string}.
 * Example: If the type has a {@link XsdMinInclusive} of 0 it means that the minimum value it can take is 0.
 */
class XsdMinInclusive : public XsdStringRestrictions
{
private:
    /**
     * Indicates if the value is fixed.
     */
    bool m_fixed;
public: // ctors
  XsdMinInclusive(std::shared_ptr<XsdParserCore> parser,
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
        xsdAbstractElementVisitor->visit(std::static_pointer_cast<XsdMinInclusive>(shared_from_this()));
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
        return create<XsdMinInclusive>(getParser(),
                                       placeHolderAttributes,
                                       m_visitorFunction,
                                       nullptr);
    }

  bool isFixed(void) {
        return m_fixed;
    }
};
