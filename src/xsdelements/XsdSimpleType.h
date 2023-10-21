#pragma once



//#include <core/utils/ParseData.h>
#include <xsdelements/elementswrapper/ReferenceBase.h>
#include <xsdelements/elementswrapper/UnsolvedReference.h>
#include <xsdelements/enums/SimpleTypeFinalEnum.h>
#include <xsdelements/exceptions/ParsingException.h>
#include <xsdelements/visitors/XsdAbstractElementVisitor.h>

#include <xsdelements/XsdNamedElements.h>

//using XsdIntegerRestrictions::hasDifferentValue;
//using XsdStringRestrictions::hasDifferentValue;
//using XsdWhiteSpace::hasDifferentValue;

/**
 * A class representing the xsd:simpleType element.
 *
 * @see <a href="https://www.w3schools.com/xml/el_simpleType.asp">xsd:simpleType description and usage at W3C</a>
 */
class XsdSimpleType : public XsdNamedElements
{
public:
  using XsdNamedElements::clone;
  constexpr static const std::string_view XSD_TAG = "xsd:simpleType";
  constexpr static const std::string_view XS_TAG = "xs:simpleType";
  constexpr static const std::string_view TAG = "simpleType";

private:
    /**
     * A {@link XsdRestriction} instance that is present in the {@link XsdSimpleType} instance.
     */
    std::shared_ptr<XsdRestriction> m_restriction;

    /**
     * A {@link XsdUnion} instance that is present in the {@link XsdSimpleType} instance.
     */
    std::shared_ptr<XsdUnion> m_xsd_union;

    /**
     * A {@link XsdList} instance that is present in the {@link XsdSimpleType} instance.
     */
    std::shared_ptr<XsdList> m_xsd_list;

    /**
     * Prevents other elements to derive depending on its value.
     */
    SimpleTypeFinalEnum m_finalObj;

public: // ctors
    XsdSimpleType(std::shared_ptr<XsdParserCore> parser,
                  StringMap attributesMap,
                  VisitorFunctionReference visitorFunction,
                  std::shared_ptr<XsdAbstractElement> parent = nullptr);
public:
    /**
     * Runs verifications on each concrete element to ensure that the XSD schema rules are verified.
     */
  virtual void validateSchemaRules(void) override;

private:
    /**
     * Asserts that the current object has the required name attribute when not being a direct child of the XsdSchema element.
     * Throws an exception if the required attribute is not present.
     */
    void rule2(void);

    /**
     * Asserts if the current has no value for its name attribute while being a direct child of the top level XsdSchema element,
     * which is required. Throws an exception if no name is present.
     */
    void rule3(void);
public:
  void accept(std::shared_ptr<XsdAbstractElementVisitor> visitorParam);
    /**
     * Performs a copy of the current object for replacing purposes. The cloned objects are used to replace
     * {@link UnsolvedReference} objects in the reference solving process.
     * @param placeHolderAttributes The additional attributes to add to the clone.
     * @return A copy of the object from which is called upon.
     */
  std::shared_ptr<XsdSimpleType> clone(StringMap placeHolderAttributes);

  static std::shared_ptr<ReferenceBase> parse(ParseData parseData);

  std::shared_ptr<XsdRestriction> getRestriction(void) {
        return m_restriction;
    }

  std::shared_ptr<XsdUnion> getUnion(void) {
        return m_xsd_union;
    }

  std::shared_ptr<XsdList> getList(void);

    /**
     * This method obtains all the restrictions for the current {@link XsdSimpleType} element. It also joins multiple
     * restrictions with the same base attribute in the same {@link XsdRestriction} object, if a overlap doesn't occur.
     * In case of restriction overlap an exception is thrown because the information on the xsd file is contradictory.
     * @return A xsd_list of restrictions.
     */
  std::list<std::shared_ptr<XsdRestriction>> getAllRestrictions(void);

private:
    /**
     * Joins two distinct {@link XsdRestriction} instances. This method assumes that the information of both
     * {@link XsdRestriction} objects don't have overlapping or contradictory information.
     * @param existing The existing restriction.
     * @param newRestriction The new restriction.
     */
    void updateExistingRestriction(std::shared_ptr<XsdRestriction> existing, std::shared_ptr<XsdRestriction> newRestriction);

    /**
     * Updates the existing {@link XsdRestriction} with the restrictions of the new {@link XsdRestriction} instance.
     * @param existing The existing {@link XsdRestriction} instance.
     * @param newRestriction The new {@link XsdRestriction} instance.
     */
    void updateExistingRestrictionEnumerations(std::shared_ptr<XsdRestriction> existing, std::shared_ptr<XsdRestriction> newRestriction);

    /**
     * Checks for any restriction overlap between two different {@link XsdRestriction} instances.
     * @param existing The existing restriction.
     * @param newRestriction The second restriction found.
     * @return True if an overlap between the restrictions occur, false if it doesn't occur.
     */
    bool existsRestrictionOverlap(std::shared_ptr<XsdRestriction> existing, std::shared_ptr<XsdRestriction> newRestriction);
public:
  void setList(std::shared_ptr<XsdList> xsd_list) {
        m_xsd_list = xsd_list;
    }

  void setUnion(std::shared_ptr<XsdUnion> xsd_union) {
        m_xsd_union = xsd_union;
    }

  void setRestriction(std::shared_ptr<XsdRestriction> restriction) {
        m_restriction = restriction;
    }

  std::optional<std::string> getFinalObj(void) {
        return m_finalObj.getValue();
    }
};
