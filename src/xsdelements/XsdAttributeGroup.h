#pragma once

#include <xsdelements/visitors/XsdAbstractElementVisitor.h>
#include <xsdelements/elementswrapper/NamedConcreteElement.h>
#include <xsdelements/elementswrapper/ReferenceBase.h>
#include <xsdelements/elementswrapper/UnsolvedReference.h>

#include <xsdelements/XsdNamedElements.h>

class XsdAttribute;

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
  using XsdNamedElements::clone;

private:
    /**
     * A list of {@link XsdAttributeGroup} children instances.
     */
    //This list is populated by the replaceUnsolvedElements and never directly (such as a Visitor method like all else).
    //The UnsolvedReference is placed in the XsdParser queue by the default implementation of the Visitor#visit(std::enable_shared_from_this<XsdAttributeGroup>::create element)
    //The reference solving process then sends the XsdAttributeGroup to this class.
    std::list<std::shared_ptr<ReferenceBase>> m_attributeGroups;

    /**
     * A list of {@link XsdAttribute} children instances.
     */
    std::list<std::shared_ptr<ReferenceBase>> m_attributes;
public:
  XsdAttributeGroup(std::shared_ptr<XsdParserCore> parser,
                    StringMap attributesMap,
                    VisitorFunctionType visitorFunction,
                    std::shared_ptr<XsdAbstractElement> parent)
    : XsdNamedElements(parser, attributesMap, visitorFunction, parent) { }

public:
  virtual void initialize(void) override
  {
    XsdNamedElements::initialize();
    m_attributeGroups.clear();
    m_attributes.clear();
  }


  void accept(std::shared_ptr<XsdAbstractElementVisitor> visitorParam) override
    {
        XsdNamedElements::accept(visitorParam);
        visitorParam->visit(std::static_pointer_cast<XsdAttributeGroup>(shared_from_this()));
    }

  virtual std::list<std::shared_ptr<ReferenceBase>> getElements(void) override;
  std::shared_ptr<XsdNamedElements> clone(StringMap placeHolderAttributes);
  void replaceUnsolvedElements(std::shared_ptr<NamedConcreteElement> element);
  std::list<std::shared_ptr<XsdAttributeGroup>> getXsdAttributeGroups(void);
  std::list<std::shared_ptr<XsdAttributeGroup>> getAllXsdAttributeGroups(void);
  std::list<std::shared_ptr<XsdAttribute>> getXsdAttributes(void);

  void addAttribute(std::shared_ptr<ReferenceBase> attribute)
  {
    m_attributes.push_back(attribute);
  }

  void addAttributeGroup(std::shared_ptr<ReferenceBase> attributeGroup)
  {
    m_attributeGroups.push_back(attributeGroup);
  }
};
