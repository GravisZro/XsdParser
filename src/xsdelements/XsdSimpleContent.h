#pragma once

#include <xsdelements/elementswrapper/ConcreteElement.h>
#include <xsdelements/elementswrapper/ReferenceBase.h>
#include <xsdelements/visitors/XsdAbstractElementVisitor.h>

#include <xsdelements/XsdAnnotatedElements.h>
#include <xsdelements/XsdRestriction.h>
#include <xsdelements/XsdExtension.h>


/**
 * A class representing the xsd:simpleContent element.
 *
 * @see <a href="https://www.w3schools.com/xml/el_simpleContent.asp">xsd:simpleContent description and usage at w3c</a>
 */
class XsdSimpleContent : public XsdAnnotatedElements
{
public:
  XsdSimpleContent(StringMap attributesMap,
                   VisitorFunctionType visitorFunction,
                   XsdAbstractElement* parent)
    : XsdAnnotatedElements(attributesMap, visitorFunction, parent),
      m_restriction(nullptr),
      m_extension(nullptr)
  {
  }

  /**
   * Performs a copy of the current object for replacing purposes. The cloned objects are used to replace
   * {@link UnsolvedReference} objects in the reference solving process.
   * @param placeHolderAttributes The additional attributes to add to the clone.
   * @return A copy of the object from which is called upon.
   */
  XsdSimpleContent(const XsdSimpleContent& other, XsdAbstractElement* parent = nullptr)
    : XsdSimpleContent(other.getAttributesMap(), other.m_visitorFunction, parent)
  {
    m_restriction = new ReferenceBase(other.m_restriction, this);
    m_extension = new ReferenceBase(other.m_extension, this);
    setCloneOf(&other);
  }

  ~XsdSimpleContent(void)
  {
    if(m_restriction != nullptr)
      delete m_restriction, m_restriction = nullptr;

    if(m_extension != nullptr)
      delete m_extension, m_extension = nullptr;
  }

public:
  void accept(XsdAbstractElementVisitor* visitorParam) override
  {
    XsdAnnotatedElements::accept(visitorParam);
    visitorParam->visit(static_cast<XsdSimpleContent*>(this));
  }


  XsdExtension* getXsdExtension(void) const
  {
    if(auto x = dynamic_cast<ConcreteElement*>(m_extension); x != nullptr)
      return static_cast<XsdExtension*>(x->getElement());
    return nullptr;
  }

  XsdRestriction* getXsdRestriction(void) const
  {
    if(auto x = dynamic_cast<ConcreteElement*>(m_restriction); x != nullptr)
      return static_cast<XsdRestriction*>(x->getElement());
    return nullptr;
  }

  void setRestriction(ReferenceBase* restriction)
  {
    m_restriction = restriction;
  }

  void setExtension(ReferenceBase* extension)
  {
    m_extension = extension;
  }

private:
  /**
   * The {@link XsdRestriction} instance that should be applied to the {@link XsdSimpleContent} instance.
   */
  ReferenceBase* m_restriction;

  /**
   * The {@link XsdExtension} instance that is present in the {@link XsdSimpleContent} instance.
   */
  ReferenceBase* m_extension;
};
