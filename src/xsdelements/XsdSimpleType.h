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
public: // ctors
  XsdSimpleType(StringMap attributesMap,
                VisitorFunctionType visitorFunction,
                XsdAbstractElement* parent)
    : XsdNamedElements(attributesMap, visitorFunction, parent),
      m_restriction(nullptr),
      m_xsd_union(nullptr),
      m_xsd_list(nullptr)
  {
    m_finalObj = AttributeValidations::getFinalDefaultValue(getParent());
    if(haveAttribute(FINAL_TAG))
      m_finalObj = AttributeValidations::belongsToEnum<SimpleTypeFinalEnum>(getAttribute(FINAL_TAG) );
  }

  XsdSimpleType(const XsdSimpleType& other, XsdAbstractElement* parent = nullptr);
public:

  /**
   * Runs verifications on each concrete element to ensure that the XSD schema rules are verified.
   */
  virtual void validateSchemaRules(void) const override
  {
    XsdNamedElements::validateSchemaRules();

    rule2();
    rule3();
  }

  void accept(XsdAbstractElementVisitor* visitorParam) override
  {
    XsdNamedElements::accept(visitorParam);
    visitorParam->visit(static_cast<XsdSimpleType*>(this));
  }

  XsdRestriction* getRestriction(void) const
  {
    return m_restriction;
  }

  XsdUnion* getUnion(void) const
  {
    return m_xsd_union;
  }

  XsdList* getList(void) const;

  /**
   * This method obtains all the restrictions for the current {@link XsdSimpleType} element. It also joins multiple
   * restrictions with the same base attribute in the same {@link XsdRestriction} object, if a overlap doesn't occur.
   * In case of restriction overlap an exception is thrown because the information on the xsd file is contradictory.
   * @return A xsd_list of restrictions.
   */
  std::list<XsdRestriction*> getAllRestrictions(void) const;

  void setList(XsdList* xsd_list)
  {
    m_xsd_list = xsd_list;
  }

  void setUnion(XsdUnion* xsd_union)
  {
    m_xsd_union = xsd_union;
  }

  void setRestriction(XsdRestriction* restriction)
  {
    m_restriction = restriction;
  }

  std::optional<std::string> getFinalObj(void) const
  {
    return m_finalObj;
  }


private:
  /**
   * Asserts that the current object has the required name attribute when not being a direct child of the XsdSchema element.
   * Throws an exception if the required attribute is not present.
   */
  void rule2(void) const
  {
    if (dynamic_cast<XsdSchema*>(getParent()) == nullptr && getRawName())
      throw ParsingException(TAG<XsdSimpleType>::xsd + " element: The " + NAME_TAG + " should only be used when the parent of the " + TAG<XsdSimpleType>::xsd + " is the " + TAG<XsdSchema>::xsd + " element.");
  }

  /**
   * Asserts if the current has no value for its name attribute while being a direct child of the top level XsdSchema element,
   * which is required. Throws an exception if no name is present.
   */
  void rule3(void) const
  {
    if (dynamic_cast<XsdSchema*>(getParent()) != nullptr && !getRawName())
      throw ParsingException(TAG<XsdSimpleType>::xsd + " element: The " + NAME_TAG + " should is required the parent of the " + TAG<XsdSimpleType>::xsd + " is the " + TAG<XsdSchema>::xsd + " element.");
  }

private:
  /**
   * A {@link XsdRestriction} instance that is present in the {@link XsdSimpleType} instance.
   */
  XsdRestriction* m_restriction;

  /**
   * A {@link XsdUnion} instance that is present in the {@link XsdSimpleType} instance.
   */
  XsdUnion* m_xsd_union;

  /**
   * A {@link XsdList} instance that is present in the {@link XsdSimpleType} instance.
   */
  XsdList* m_xsd_list;

  /**
   * Prevents other elements to derive depending on its value.
   */
  SimpleTypeFinalEnum m_finalObj;
};
