#pragma once

#include <xsdelements/XsdAbstractElement.h>
#include <xsdelements/XsdAnnotatedElements.h>
#include <xsdelements/visitors/XsdAbstractElementVisitor.h>
#include <xsdelements/elementswrapper/ReferenceBase.h>
#include <xsdelements/elementswrapper/NamedConcreteElement.h>

class XsdNamedElements;
class XsdBuiltInDataType;
class XsdEnumeration;
class XsdFractionDigits;
class XsdLength;
class XsdMaxExclusive;
class XsdMaxInclusive;
class XsdMaxLength;
class XsdMinExclusive;
class XsdMinInclusive;
class XsdMinLength;
class XsdPattern;
class XsdTotalDigits;
class XsdWhiteSpace;
class XsdAll;
class XsdChoice;
class XsdSequence;
class XsdAttribute;
class XsdAttributeGroup;
class XsdComplexType;
class XsdSimpleType;
class XsdGroup;
class NamedConcreteElement;

/**
 * A class representing the xsd:restriction element.
 *
 * @see <a href="https://www.w3schools.com/xml/el_restriction.asp">xsd:restriction description and usage at W3C</a>
 */
class XsdRestriction : public XsdAnnotatedElements
{
public: // ctors
  XsdRestriction(StringMap attributesMap,
                 VisitorFunctionType visitorFunction,
                 XsdAbstractElement* parent);

  XsdRestriction(const XsdRestriction& other, XsdAbstractElement* parent = nullptr);
public:

  void accept(XsdAbstractElementVisitor* visitorParam) override
  {
    XsdAnnotatedElements::accept(visitorParam);
    visitorParam->visit(static_cast<XsdRestriction*>(this));
  }

  virtual void replaceUnsolvedElements(NamedConcreteElement* elementWrapper) override;

  std::list<XsdAttribute*> getXsdAttributes(void) const;
  std::list<XsdAttributeGroup*> getXsdAttributeGroup(void) const;

  /**
   * @tparam One of the following classes:
   *      * {@link XsdNamedElements}
   *      * {@link XsdComplexType}
   *      * {@link XsdSimpleType}
   *      * {@link XsdBuiltInDataType}
   * @return the base from which this extension extends or null if the {@link XsdParserCore} wasn't able to
   * replace the {@link UnsolvedReference} created by the base attribute value.
   */
  template<typename T, std::enable_if_t<std::is_same_v<XsdNamedElements  , T> ||
                                        std::is_same_v<XsdComplexType    , T> ||
                                        std::is_same_v<XsdSimpleType     , T> ||
                                        std::is_same_v<XsdBuiltInDataType, T>, bool> = true>
  T* getBaseAs(void) const
  {
    if(dynamic_cast<NamedConcreteElement*>(m_base) != nullptr)
      if(auto x = dynamic_cast<T*>(m_base->getElement()); x != nullptr)
        return x;
    return nullptr;
  }


  std::optional<std::string> getBaseType(void) const
  {
    return m_baseString;
  }

  std::list<XsdEnumeration*> getEnumeration(void) const
  {
    return m_enumeration;
  }

  void setEnumeration(std::list<XsdEnumeration*> enumeration)
  {
    m_enumeration = enumeration;
  }

  XsdFractionDigits* getFractionDigits(void) const
  {
    return m_fractionDigits;
  }

  void setFractionDigits(XsdFractionDigits* fractionDigits)
  {
    m_fractionDigits = fractionDigits;
  }

  XsdLength* getLength(void) const
  {
    return m_length;
  }

  void setLength(XsdLength* length)
  {
    m_length = length;
  }

  XsdMaxExclusive* getMaxExclusive(void) const
  {
    return m_maxExclusive;
  }

  void setMaxExclusive(XsdMaxExclusive* maxExclusive)
  {
    m_maxExclusive = maxExclusive;
  }

  XsdMaxInclusive* getMaxInclusive(void) const
  {
    return m_maxInclusive;
  }

  void setMaxInclusive(XsdMaxInclusive* maxInclusive)
  {
    m_maxInclusive = maxInclusive;
  }

  XsdMaxLength* getMaxLength(void) const
  {
    return m_maxLength;
  }

  void setMaxLength(XsdMaxLength* maxLength)
  {
    m_maxLength = maxLength;
  }

  XsdMinExclusive* getMinExclusive(void) const
  {
    return m_minExclusive;
  }

  void setMinExclusive(XsdMinExclusive* minExclusive)
  {
    m_minExclusive = minExclusive;
  }

  XsdMinInclusive* getMinInclusive(void) const
  {
    return m_minInclusive;
  }

  void setMinInclusive(XsdMinInclusive* minInclusive)
  {
    m_minInclusive = minInclusive;
  }

  XsdMinLength* getMinLength(void) const
  {
    return m_minLength;
  }

  void setMinLength(XsdMinLength* minLength)
  {
    m_minLength = minLength;
  }

  XsdPattern* getPattern(void) const
  {
    return m_pattern;
  }

  void setPattern(XsdPattern* pattern)
  {
    m_pattern = pattern;
  }

  XsdTotalDigits* getTotalDigits(void) const
  {
    return m_totalDigits;
  }

  void setTotalDigits(XsdTotalDigits* totalDigits)
  {
    m_totalDigits = totalDigits;
  }

  XsdWhiteSpace* getWhiteSpace(void) const
  {
    return m_whiteSpace;
  }

  void setWhiteSpace(XsdWhiteSpace* whiteSpace)
  {
    m_whiteSpace = whiteSpace;
  }

  void add(XsdEnumeration* enumerationMember)
  {
    m_enumeration.push_back(enumerationMember);
  }

  XsdGroup* getGroup(void) const;

  void setGroup(ReferenceBase* group)
  {
    m_group = group;
  }

  XsdAll* getAll(void) const
  {
    return m_all;
  }

  void setAll(XsdAll* all)
  {
    m_all = all;
  }

  XsdChoice* getChoice(void) const
  {
    return m_choice;
  }

  void setChoice(XsdChoice* choice)
  {
    m_choice = choice;
  }

  XsdSequence* getSequence(void) const
  {
    return m_sequence;
  }

  void setSequence(XsdSequence* sequence)
  {
    m_sequence = sequence;
  }

private:
  /**
   * The {@link XsdSimpleType} instance of this {@link XsdRestriction} instance.
   */
  ReferenceBase* m_base;

  /**
   * A List of {@link XsdEnumeration} items, that represent a set of possible values for a given type.
   */
  std::list<XsdEnumeration*> m_enumeration;

  /**
   * A {@link XsdFractionDigits} instance that specifies the number of fraction digits allowed in a numeric type.
   */
  XsdFractionDigits* m_fractionDigits;

  /**
   * A {@link XsdLength} instance that specifies the specific length of a List or std::string type.
   */
  XsdLength* m_length;

  /**
   * A {@link XsdMaxExclusive} instance that specifies the maxExclusive value for a numeric type.
   */
  XsdMaxExclusive* m_maxExclusive;

  /**
   * A {@link XsdMaxInclusive} instance that specifies the maxInclusive value for a numeric type.
   */
  XsdMaxInclusive* m_maxInclusive;

  /**
   * A {@link XsdMaxLength} instance that specifies the maxLength of a List or a std::string type.
   */
  XsdMaxLength* m_maxLength;

  /**
   * A {@link XsdMinExclusive} instance that specifies the minExclusive value for a numeric type.
   */
  XsdMinExclusive* m_minExclusive;

  /**
   * A {@link XsdMinInclusive} instance that specifies the minInclusive value for a numeric type.
   */
  XsdMinInclusive* m_minInclusive;

  /**
   * A {@link XsdMinLength} instance that specifies the minLength of a List or a std::string type.
   */
  XsdMinLength* m_minLength;

  /**
   * A {@link XsdPattern} instance that specifies a regex pattern that a std::string type should follow.
   */
  XsdPattern* m_pattern;

  /**
   * A {@link XsdTotalDigits} instance that specifies the total number of digits that a numeric type is allowed to have.
   */
  XsdTotalDigits* m_totalDigits;

  /**
   * A {@link XsdWhiteSpace} instance that specifies how the whitespace characters should be dealt with.
   */
  XsdWhiteSpace* m_whiteSpace;

  ReferenceBase* m_group;

  XsdAll* m_all;

  XsdChoice* m_choice;

  XsdSequence* m_sequence;

  /**
   * The name of the type where this instance restrictions should be applied.
   */
  std::optional<std::string> m_baseString;
};
