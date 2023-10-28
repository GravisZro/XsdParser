#pragma once

#include <xsdelements/enums/SimpleTypeFinalEnum.h>
#include <xsdelements/exceptions/ParsingException.h>
#include <xsdelements/visitors/XsdAbstractElementVisitor.h>

#include <xsdelements/XsdSchema.h>
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
  virtual void validateSchemaRules(void) const override
  {
    XsdNamedElements::validateSchemaRules();

    rule2();
    rule3();
  }

private:
  /**
   * Asserts that the current object has the required name attribute when not being a direct child of the XsdSchema element.
   * Throws an exception if the required attribute is not present.
   */
  void rule2(void) const
  {
    if (std::dynamic_pointer_cast<XsdSchema>(getParent()) == nullptr && getRawName())
      throw ParsingException(TAG<XsdSimpleType>::xsd + " element: The " + NAME_TAG + " should only be used when the parent of the " + TAG<XsdSimpleType>::xsd + " is the " + TAG<XsdSchema>::xsd + " element.");
  }

  /**
   * Asserts if the current has no value for its name attribute while being a direct child of the top level XsdSchema element,
   * which is required. Throws an exception if no name is present.
   */
  void rule3(void) const
  {
    if (std::dynamic_pointer_cast<XsdSchema>(getParent()) && !getRawName())
      throw ParsingException(TAG<XsdSimpleType>::xsd + " element: The " + NAME_TAG + " should is required the parent of the " + TAG<XsdSimpleType>::xsd + " is the " + TAG<XsdSchema>::xsd + " element.");
  }
public:
  void accept(std::shared_ptr<XsdAbstractElementVisitor> visitorParam) override
  {
    XsdNamedElements::accept(visitorParam);
    visitorParam->visit(std::static_pointer_cast<XsdSimpleType>(shared_from_this()));
  }

  /**
   * Performs a copy of the current object for replacing purposes. The cloned objects are used to replace
   * {@link UnsolvedReference} objects in the reference solving process.
   * @param placeHolderAttributes The additional attributes to add to the clone.
   * @return A copy of the object from which is called upon.
   */
  virtual std::shared_ptr<XsdAbstractElement> clone(StringMap placeHolderAttributes) override;

  std::shared_ptr<XsdRestriction> getRestriction(void) const
  {
    return m_restriction;
  }

  std::shared_ptr<XsdUnion> getUnion(void) const
  {
    return m_xsd_union;
  }

  std::shared_ptr<XsdList> getList(void) const;

  /**
   * This method obtains all the restrictions for the current {@link XsdSimpleType} element. It also joins multiple
   * restrictions with the same base attribute in the same {@link XsdRestriction} object, if a overlap doesn't occur.
   * In case of restriction overlap an exception is thrown because the information on the xsd file is contradictory.
   * @return A xsd_list of restrictions.
   */
  std::list<std::shared_ptr<XsdRestriction>> getAllRestrictions(void) const;

public:
  void setList(std::shared_ptr<XsdList> xsd_list)
  {
    m_xsd_list = xsd_list;
  }

  void setUnion(std::shared_ptr<XsdUnion> xsd_union)
  {
    m_xsd_union = xsd_union;
  }

  void setRestriction(std::shared_ptr<XsdRestriction> restriction)
  {
    m_restriction = restriction;
  }

  std::optional<std::string> getFinalObj(void) const
  {
    return m_finalObj;
  }
};
