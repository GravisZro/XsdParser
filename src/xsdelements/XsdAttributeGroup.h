#pragma once

#include <xsdelements/visitors/XsdAbstractElementVisitor.h>
#include <xsdelements/elementswrapper/ReferenceBase.h>

#include <xsdelements/XsdNamedElements.h>

class XsdAttribute;
class NamedConcreteElement;

/**
 * A class is representing xsd:attributeGroup elements. It can have a ref attribute and therefore extends from
 * {@link XsdNamedElements}, which serves as a base to every element type that can have a ref attribute. For more
 * information check {@link XsdNamedElements}.
 *
 * @see <a href="https://www.w3schools.com/xml/el_attributegroup.asp">xsd:attributeGroup element description and usage at w3c</a>
 */
class XsdAttributeGroup : public XsdNamedElements
{
public:
  XsdAttributeGroup(StringMap attributesMap,
                    VisitorFunctionType visitorFunction,
                    XsdAbstractElement* parent)
    : XsdNamedElements(attributesMap, visitorFunction, parent)
  {
  }

  XsdAttributeGroup(const XsdAttributeGroup& other, XsdAbstractElement* parent = nullptr);

public:
  void accept(XsdAbstractElementVisitor* visitorParam) override
  {
    XsdNamedElements::accept(visitorParam);
    visitorParam->visit(static_cast<XsdAttributeGroup*>(this));
  }

  virtual void replaceUnsolvedElements(NamedConcreteElement* elementWrapper) override;

  virtual std::list<ReferenceBase*> getElements(void) const override;
  std::list<XsdAttributeGroup*> getXsdAttributeGroups(void) const;
  std::list<XsdAttributeGroup*> getAllXsdAttributeGroups(void) const;
  std::list<XsdAttribute*> getXsdAttributes(void) const;

  void addAttribute(ReferenceBase* attribute)
  {
    m_attributes.push_back(attribute);
  }

  void addAttributeGroup(ReferenceBase* attributeGroup)
  {
    m_attributeGroups.push_back(attributeGroup);
  }

private:
  /**
   * A list of {@link XsdAttributeGroup} children instances.
   */
  //This list is populated by the replaceUnsolvedElements and never directly (such as a Visitor method like all else).
  //The UnsolvedReference is placed in the XsdParser queue by the default implementation of the Visitor#visit
  //The reference solving process then sends the XsdAttributeGroup to this class.
  std::list<ReferenceBase*> m_attributeGroups;

  /**
   * A list of {@link XsdAttribute} children instances.
   */
  std::list<ReferenceBase*> m_attributes;
};
