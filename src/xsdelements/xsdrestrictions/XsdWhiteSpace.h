#pragma once




#include <xsdelements/AttributeValidations.h>
#include <xsdelements/XsdAbstractElement.h>
#include <xsdelements/XsdAnnotatedElements.h>
#include <xsdelements/elementswrapper/ReferenceBase.h>
#include <xsdelements/elementswrapper/UnsolvedReference.h>
#include <xsdelements/enums/WhiteSpaceEnum.h>
#include <xsdelements/visitors/XsdAbstractElementVisitor.h>

#include <xsdelements/XsdAnnotatedElements.h>

/**
 * States how the whiteSpace characters should be treated. The value is defined as an {@link std::string}.
 */
class XsdWhiteSpace : public XsdAnnotatedElements
{
public:
  using XsdAnnotatedElements::clone;
private:
  bool m_fixed;
  WhiteSpaceEnum m_value;
public: // ctors
  XsdWhiteSpace(std::shared_ptr<XsdParserCore> parser,
                StringMap attributesMap,
                VisitorFunctionType visitorFunction,
                std::shared_ptr<XsdAbstractElement> parent)
        : XsdAnnotatedElements(parser, attributesMap, visitorFunction, parent),
          m_fixed(false)
  {
  }
public:
  virtual void initialize(void) override
  {
    XsdAnnotatedElements::initialize();
    m_fixed = false;
    m_value.reset();
    if(haveAttribute(FIXED_TAG))
      m_fixed = AttributeValidations::validateBoolean(getAttribute(FIXED_TAG));
    if(haveAttribute(VALUE_TAG))
      m_value = AttributeValidations::belongsToEnum<WhiteSpaceEnum>(getAttribute(VALUE_TAG));
  }
public:
  void accept(std::shared_ptr<XsdAbstractElementVisitor> xsdAbstractElementVisitor) override
    {
        XsdAnnotatedElements::accept(xsdAbstractElementVisitor);
        xsdAbstractElementVisitor->visit(std::static_pointer_cast<XsdWhiteSpace>(shared_from_this()));
    }

    /**
     * Performs a copy of the current object for replacing purposes. The cloned objects are used to replace
     * {@link UnsolvedReference} objects in the reference solving process.
     * @param placeHolderAttributes The additional attributes to add to the clone.
     * @return A copy of the object from which is called upon.
     */
  std::shared_ptr<XsdWhiteSpace> clone(StringMap placeHolderAttributes)
    {
        placeHolderAttributes.merge(getAttributesMap());
        return create<XsdWhiteSpace>(getParser(),
                                     placeHolderAttributes,
                                     m_visitorFunction,
                                     nullptr);
    }

  bool isFixed(void) {
        return m_fixed;
    }

  WhiteSpaceEnum getValue(void) {
        return m_value;
    }

  static bool hasDifferentValue(std::shared_ptr<XsdWhiteSpace> o1, std::shared_ptr<XsdWhiteSpace> o2)
  {
    if (o1 && o2)
      return o1->getValue() == o2->getValue();
    return false;
  }
};
