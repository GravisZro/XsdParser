#pragma once

#include <xsdelements/XsdSimpleType.h>
#include <xsdelements/visitors/XsdAbstractElementVisitor.h>

#include <xsdelements/XsdAnnotatedElements.h>


/**
 * A class representing the xsd:list element.
 *
 * @see <a href="https://www.w3schools.com/xml/el_list.asp">xsd:list description and usage at w3c</a>
 */
class XsdList : public XsdAnnotatedElements
{
public: // ctors
  XsdList(StringMap attributesMap,
          VisitorFunctionType visitorFunction,
          XsdAbstractElement* parent)
    : XsdAnnotatedElements(attributesMap, visitorFunction, parent),
      m_simpleType(nullptr)
  {
    if(hasAttribute(ITEM_TYPE_TAG))
      m_itemType = getAttribute(ITEM_TYPE_TAG);
  }

  /**
   * Performs a copy of the current object for replacing purposes. The cloned objects are used to replace
   * {@link UnsolvedReference} objects in the reference solving process.
   * @param placeHolderAttributes The additional attributes to add to the clone.
   * @return A copy of the object from which is called upon.
   */
  XsdList(const XsdList& other, XsdAbstractElement* parent = nullptr)
    : XsdList(other.getAttributesMap(), other.m_visitorFunction, parent)
  {
    if (other.m_simpleType != nullptr)
      m_simpleType = new XsdSimpleType(*other.m_simpleType, this);
  }

  ~XsdList(void)
  {
    if(m_simpleType != nullptr)
      delete m_simpleType, m_simpleType = nullptr;
  }

public:
  void accept(XsdAbstractElementVisitor* visitorParam) override
  {
    XsdAnnotatedElements::accept(visitorParam);
    visitorParam->visit(static_cast<XsdList*>(this));
  }

  XsdSimpleType* getXsdSimpleType(void) const
  {
    return m_simpleType;
  }

  std::optional<std::string> getItemType(void) const
  {
    return m_itemType;
  }

  void setSimpleType(XsdSimpleType* simpleType)
  {
    m_simpleType = simpleType;
  }

private:
  /**
   * The {@link XsdSimpleType} instance that states the type of the elements that belong to this {@link XsdList}
   * instance. This value shouldn't be present if there is a {@link XsdList#itemType} present.
   */
  XsdSimpleType* m_simpleType;

  /**
   * The itemType defines the built-it type or the name of a present {@link XsdSimpleType} instance that represent
   * the type of the elements that belong to this {@link XsdList}. This value shouldn't be present if there is a
   * {@link XsdList#simpleType} is present.
   */
  std::optional<std::string> m_itemType;
};
