#pragma once

#include <xsdelements/XsdAbstractElement.h>
#include <xsdelements/visitors/XsdAbstractElementVisitor.h>

#include <xsdelements/XsdAnnotatedElements.h>

/**
 * This class serves as a base to every different restriction that has its restricting parameter defined as an {@link std::string}.
 * Classes like {@link XsdPattern} or {@link XsdEnumeration} should extend this class.
 */
class XsdStringRestrictions : public XsdAnnotatedElements
{
public:
    using XsdAnnotatedElements::clone;
private:
    /**
     * The value of associated with a given restriction. This field has different meanings depending on the concrete
     * restriction, e.g. if the concrete class is {@link XsdEnumeration} this field means that the attribute which
     * has the restriction can only have the value that is specified in this field.
     */
    std::optional<std::string> m_value;

public: // ctors
    XsdStringRestrictions(std::shared_ptr<XsdParserCore> parser,
                          StringMap elementFieldsMapParam,
                          VisitorFunctionType visitorFunction,
                          std::shared_ptr<XsdAbstractElement> parent)
        : XsdAnnotatedElements(parser, elementFieldsMapParam, visitorFunction, parent)
    {
      if(haveAttribute(VALUE_TAG))
        m_value = getAttribute(VALUE_TAG);
    }
public:
    /**
     * Compares two different objects of this type.
     * @param o1 The first object.
     * @param o2 The object to compare.
     * @return True if the value of both classes is different, False if the value is equal.
     */
    static bool hasDifferentValue(std::shared_ptr<XsdStringRestrictions> o1, std::shared_ptr<XsdStringRestrictions> o2)
    {
      if (!o1 && !o2)
        return false;

      if (o1 && o2)
        return o1->getValue() == o2->getValue();

      return false;
    }

  std::optional<std::string> getValue(void) {
        return m_value;
    }
};
