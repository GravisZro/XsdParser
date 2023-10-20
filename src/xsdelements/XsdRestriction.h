#pragma once

#include <xsdelements/XsdAbstractElement.h>
#include <xsdelements/XsdAnnotatedElements.h>

class XsdBuiltInDataType;

/**
 * A class representing the xsd:restriction element.
 *
 * @see <a href="https://www.w3schools.com/xml/el_restriction.asp">xsd:restriction description and usage at W3C</a>
 */
class XsdRestriction : public XsdAnnotatedElements
{
public:
  using XsdAnnotatedElements::clone;
    constexpr static const std::string_view XSD_TAG = "xsd:restriction";
    constexpr static const std::string_view XS_TAG = "xs:restriction";
    constexpr static const std::string_view TAG = "restriction";

private:
    /**
     * The {@link XsdSimpleType} instance of this {@link XsdRestriction} instance.
     */
    std::shared_ptr<ReferenceBase> m_base;

    /**
     * A List of {@link XsdEnumeration} items, that represent a set of possible values for a given type.
     */
    std::list<std::shared_ptr<XsdEnumeration>> m_enumeration;

    /**
     * A {@link XsdFractionDigits} instance that specifies the number of fraction digits allowed in a numeric type.
     */
    std::shared_ptr<XsdFractionDigits> m_fractionDigits;

    /**
     * A {@link XsdLength} instance that specifies the specific length of a List or std::string type.
     */
    std::shared_ptr<XsdLength> m_length;

    /**
     * A {@link XsdMaxExclusive} instance that specifies the maxExclusive value for a numeric type.
     */
    std::shared_ptr<XsdMaxExclusive> m_maxExclusive;

    /**
     * A {@link XsdMaxInclusive} instance that specifies the maxInclusive value for a numeric type.
     */
    std::shared_ptr<XsdMaxInclusive> m_maxInclusive;

    /**
     * A {@link XsdMaxLength} instance that specifies the maxLength of a List or a std::string type.
     */
    std::shared_ptr<XsdMaxLength> m_maxLength;

    /**
     * A {@link XsdMinExclusive} instance that specifies the minExclusive value for a numeric type.
     */
    std::shared_ptr<XsdMinExclusive> m_minExclusive;

    /**
     * A {@link XsdMinInclusive} instance that specifies the minInclusive value for a numeric type.
     */
    std::shared_ptr<XsdMinInclusive> m_minInclusive;

    /**
     * A {@link XsdMinLength} instance that specifies the minLength of a List or a std::string type.
     */
    std::shared_ptr<XsdMinLength> m_minLength;

    /**
     * A {@link XsdPattern} instance that specifies a regex pattern that a std::string type should follow.
     */
    std::shared_ptr<XsdPattern> m_pattern;

    /**
     * A {@link XsdTotalDigits} instance that specifies the total number of digits that a numeric type is allowed to have.
     */
    std::shared_ptr<XsdTotalDigits> m_totalDigits;

    /**
     * A {@link XsdWhiteSpace} instance that specifies how the whitespace characters should be dealt with.
     */
    std::shared_ptr<XsdWhiteSpace> m_whiteSpace;

    std::shared_ptr<ReferenceBase> m_group;

    std::shared_ptr<XsdAll> m_all;

    std::shared_ptr<XsdChoice> m_choice;

    std::shared_ptr<XsdSequence> m_sequence;

    /**
     * The name of the type where this instance restrictions should be applied.
     */
    std::optional<std::string> m_baseString;
public:
  XsdRestriction(std::shared_ptr<XsdParserCore> parser, StringMap attributesMap, VisitorFunctionReference visitorFunction);
public:
  XsdRestriction(std::shared_ptr<XsdAbstractElement> parent,
                 std::shared_ptr<XsdParserCore> parser,
                 StringMap elementFieldsMapParam,
                 VisitorFunctionReference visitorFunction)
  : XsdRestriction(parser, elementFieldsMapParam, visitorFunction)
  {
    setParent(parent);
  }

  void accept(std::shared_ptr<XsdAbstractElementVisitor> visitorParam)
    {
        XsdAnnotatedElements::accept(visitorParam);
        visitorParam->visit(nondeleted_ptr<XsdRestriction>(this));
    }

  void replaceUnsolvedElements(std::shared_ptr<NamedConcreteElement> element);
  std::shared_ptr<XsdRestriction> clone(StringMap placeHolderAttributes);

  static std::shared_ptr<ReferenceBase> parse(ParseData parseData)
  {
        return xsdParseSkeleton(parseData.node, std::static_pointer_cast<XsdAbstractElement>(std::make_shared<XsdRestriction>(parseData.parserInstance, XsdAbstractElement::getAttributesMap(parseData.node), parseData.visitorFunction)));
    }

  std::list<std::shared_ptr<XsdAttribute>> getXsdAttributes(void);
  std::list<std::shared_ptr<XsdAttributeGroup>> getXsdAttributeGroup(void);
  std::shared_ptr<XsdComplexType> getBaseAsComplexType(void);
  std::shared_ptr<XsdSimpleType> getBaseAsSimpleType(void);
  std::shared_ptr<XsdBuiltInDataType> getBaseAsBuiltInDataType(void);

  std::optional<std::string> getBase(void) {
        return m_baseString;
    }

  std::list<std::shared_ptr<XsdEnumeration>> getEnumeration(void) {
        return m_enumeration;
    }

    void setEnumeration(std::list<std::shared_ptr<XsdEnumeration>> enumeration){
        m_enumeration = enumeration;
    }

  std::shared_ptr<XsdFractionDigits> getFractionDigits(void) {
        return m_fractionDigits;
    }

  void setFractionDigits(std::shared_ptr<XsdFractionDigits> fractionDigits) {
        m_fractionDigits = fractionDigits;
    }

  std::shared_ptr<XsdLength> getLength(void) {
        return m_length;
    }

  void setLength(std::shared_ptr<XsdLength> length) {
        m_length = length;
    }

  std::shared_ptr<XsdMaxExclusive> getMaxExclusive(void) {
        return m_maxExclusive;
    }

  void setMaxExclusive(std::shared_ptr<XsdMaxExclusive> maxExclusive) {
        m_maxExclusive = maxExclusive;
    }

  std::shared_ptr<XsdMaxInclusive> getMaxInclusive(void) {
        return m_maxInclusive;
    }

  void setMaxInclusive(std::shared_ptr<XsdMaxInclusive> maxInclusive) {
        m_maxInclusive = maxInclusive;
    }

  std::shared_ptr<XsdMaxLength> getMaxLength(void) {
        return m_maxLength;
    }

  void setMaxLength(std::shared_ptr<XsdMaxLength> maxLength) {
        m_maxLength = maxLength;
    }

  std::shared_ptr<XsdMinExclusive> getMinExclusive(void) {
        return m_minExclusive;
    }

  void setMinExclusive(std::shared_ptr<XsdMinExclusive> minExclusive) {
        m_minExclusive = minExclusive;
    }

  std::shared_ptr<XsdMinInclusive> getMinInclusive(void) {
        return m_minInclusive;
    }

  void setMinInclusive(std::shared_ptr<XsdMinInclusive> minInclusive) {
        m_minInclusive = minInclusive;
    }

  std::shared_ptr<XsdMinLength> getMinLength(void) {
        return m_minLength;
    }

  void setMinLength(std::shared_ptr<XsdMinLength> minLength) {
        m_minLength = minLength;
    }

  std::shared_ptr<XsdPattern> getPattern(void) {
        return m_pattern;
    }

  void setPattern(std::shared_ptr<XsdPattern> pattern) {
        m_pattern = pattern;
    }

  std::shared_ptr<XsdTotalDigits> getTotalDigits(void) {
        return m_totalDigits;
    }

  void setTotalDigits(std::shared_ptr<XsdTotalDigits> totalDigits) {
        m_totalDigits = totalDigits;
    }

  std::shared_ptr<XsdWhiteSpace> getWhiteSpace(void) {
        return m_whiteSpace;
    }

  void setWhiteSpace(std::shared_ptr<XsdWhiteSpace> whiteSpace) {
        m_whiteSpace = whiteSpace;
    }

  void add(std::shared_ptr<XsdEnumeration> enumerationMember) {
        m_enumeration.push_back(enumerationMember);
    }

  std::shared_ptr<XsdGroup> getGroup(void);

  void setGroup(std::shared_ptr<ReferenceBase> group) {
        m_group = group;
    }

  std::shared_ptr<XsdAll> getAll(void) {
        return m_all;
    }

  void setAll(std::shared_ptr<XsdAll> all) {
        m_all = all;
    }

  std::shared_ptr<XsdChoice> getChoice(void) {
        return m_choice;
    }

  void setChoice(std::shared_ptr<XsdChoice> choice) {
        m_choice = choice;
    }

  std::shared_ptr<XsdSequence> getSequence(void) {
        return m_sequence;
    }

  void setSequence(std::shared_ptr<XsdSequence> sequence) {
        m_sequence = sequence;
    }
};
