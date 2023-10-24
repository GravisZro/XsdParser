#pragma once




#include <xsdelements/XsdAbstractElement.h>
#include <xsdelements/elementswrapper/ReferenceBase.h>
#include <xsdelements/elementswrapper/UnsolvedReference.h>
#include <xsdelements/visitors/XsdAbstractElementVisitor.h>

#include <xsdelements/xsdrestrictions/XsdStringRestrictions.h>


/**
 * States a pattern that a given attribute must match in order to be considered valid. The value is defined as a
 * {@link std::string}. This value is usually defined as a regular expression.
 */
class XsdPattern : public XsdStringRestrictions
{
public:
  using XsdStringRestrictions::clone;
public: // ctors
  XsdPattern(std::shared_ptr<XsdParserCore> parser,
             StringMap attributesMap,
             VisitorFunctionType visitorFunction,
             std::shared_ptr<XsdAbstractElement> parent)
    : XsdStringRestrictions(parser, attributesMap, visitorFunction, parent)
  {
  }
public:
  void accept(std::shared_ptr<XsdAbstractElementVisitor> xsdAbstractElementVisitor) override
    {
        XsdStringRestrictions::accept(xsdAbstractElementVisitor);
        xsdAbstractElementVisitor->visit(std::static_pointer_cast<XsdPattern>(shared_from_this()));
    }

    /**
     * Performs a copy of the current object for replacing purposes. The cloned objects are used to replace
     * {@link UnsolvedReference} objects in the reference solving process.
     * @param placeHolderAttributes The additional attributes to add to the clone.
     * @return A copy of the object from which is called upon.
     */
  std::shared_ptr<XsdPattern> clone(StringMap placeHolderAttributes)
    {
        placeHolderAttributes.merge(getAttributesMap());
        return create<XsdPattern>(getParser(),
                                  placeHolderAttributes,
                                  m_visitorFunction,
                                  nullptr);
    }
};
