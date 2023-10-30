#pragma once

#include <xsdelements/elementswrapper/ConcreteElement.h>
#include <xsdelements/elementswrapper/ReferenceBase.h>
#include <xsdelements/visitors/XsdAbstractElementVisitor.h>

#include <xsdelements/XsdAnnotatedElements.h>
#include <xsdelements/AttributeValidations.h>

class XsdExtension;
class XsdRestriction;

/**
 * A class representing the xsd:complexContent element.
 *
 * @see <a href="https://www.w3schools.com/xml/el_complexcontent.asp">xsd:complexContent element description and usage at w3c</a>
 */
class XsdComplexContent : public XsdAnnotatedElements
{
public: // ctors
  XsdComplexContent(StringMap attributesMap,
                    VisitorFunctionType visitorFunction,
                    XsdAbstractElement* parent)
    : XsdAnnotatedElements(attributesMap, visitorFunction, parent),
      m_restriction(nullptr),
      m_extension(nullptr),
      m_mixed(false)
  {
    if(haveAttribute(MIXED_TAG))
      m_mixed = AttributeValidations::validateBoolean(getAttribute(MIXED_TAG));
  }

  XsdComplexContent(const XsdComplexContent& other, XsdAbstractElement* parent = nullptr);

public:
  void accept(XsdAbstractElementVisitor* visitorParam) override
  {
    XsdAnnotatedElements::accept(visitorParam);
    visitorParam->visit(static_cast<XsdComplexContent*>(this));
  }

  bool isMixed(void) const
  {
    return m_mixed;
  }

  XsdExtension* getXsdExtension(void) const;
  XsdRestriction* getXsdRestriction(void) const;


  void setExtension(ReferenceBase* extension)
  {
    m_extension = extension;
  }

  void setRestriction(ReferenceBase* restriction)
  {
    m_restriction = restriction;
  }

private:
  /**
     * A {@link XsdRestriction} object wrapped in a {@link ReferenceBase} object.
     */
  ReferenceBase* m_restriction;

  /**
     * A {@link XsdExtension} object wrapped in a {@link ReferenceBase} object.
     */
  ReferenceBase* m_extension;

  /**
     * Specifies whether character data is allowed to appear between the child elements of this element.
     */
  bool m_mixed;
};
