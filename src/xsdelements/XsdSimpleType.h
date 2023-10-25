#pragma once

#include <xsdelements/elementswrapper/ReferenceBase.h>
#include <xsdelements/elementswrapper/UnsolvedReference.h>
#include <xsdelements/enums/SimpleTypeFinalEnum.h>
#include <xsdelements/exceptions/ParsingException.h>
#include <xsdelements/visitors/XsdAbstractElementVisitor.h>

#include <xsdelements/XsdNamedElements.h>
#include <xsdelements/AttributeValidations.h>

class XsdRestriction;
class XsdUnion;
class XsdList;

/**
 * A class representing the xsd:simpleType element.
 *
 * @see <a href="https://www.w3schools.com/xml/el_simpleType.asp">xsd:simpleType description and usage at W3C</a>
 */
class XsdSimpleType : public XsdNamedElements
{
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
                VisitorFunctionType visitorFunction,
                std::shared_ptr<XsdAbstractElement> parent)
    : XsdNamedElements(parser, attributesMap, visitorFunction, parent) { }
public:
  virtual void initialize(void) override
  {
    XsdNamedElements::initialize();
    m_restriction.reset();
    m_xsd_union.reset();
    m_xsd_list.reset();
    m_finalObj = AttributeValidations::getFinalDefaultValue(getParent());

    if(haveAttribute(FINAL_TAG))
      m_finalObj = AttributeValidations::belongsToEnum<SimpleTypeFinalEnum>(getAttribute(FINAL_TAG) );
  }
    /**
     * Runs verifications on each concrete element to ensure that the XSD schema rules are verified.
     */
  virtual void validateSchemaRules(void) const override;

private:
    /**
     * Asserts that the current object has the required name attribute when not being a direct child of the XsdSchema element.
     * Throws an exception if the required attribute is not present.
     */
    void rule2(void) const;

    /**
     * Asserts if the current has no value for its name attribute while being a direct child of the top level XsdSchema element,
     * which is required. Throws an exception if no name is present.
     */
    void rule3(void) const;
public:
  void accept(std::shared_ptr<XsdAbstractElementVisitor> visitorParam) override;
    /**
     * Performs a copy of the current object for replacing purposes. The cloned objects are used to replace
     * {@link UnsolvedReference} objects in the reference solving process.
     * @param placeHolderAttributes The additional attributes to add to the clone.
     * @return A copy of the object from which is called upon.
     */
  virtual std::shared_ptr<XsdAbstractElement> clone(StringMap placeHolderAttributes) override;

  

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
