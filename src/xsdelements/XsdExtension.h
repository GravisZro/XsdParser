#pragma once

#include <core/utils/CommonTypes.h>

#include <xsdelements/XsdAnnotatedElements.h>
#include <xsdelements/elementswrapper/ReferenceBase.h>
#include <xsdelements/visitors/XsdAbstractElementVisitor.h>

class XsdBuiltInDataType;
class XsdExtension;
class XsdNamedElements;
class XsdSimpleType;
class XsdComplexType;
class XsdAttribute;
class XsdAttributeGroup;
class XsdGroup;
class XsdAll;
class XsdChoice;
class XsdSequence;
class XsdMultipleElements;
class NamedConcreteElement;

/**
 * A class representing the xsd:extension element.
 *
 * @see <a href="https://www.w3schools.com/xml/el_extension.asp">xsd:extension description and usage at w3c</a>
 */
class XsdExtension : public XsdAnnotatedElements
{
private:
    /**
     * The child element of the {@link XsdExtension} instance. Either a {@link XsdGroup}, {@link XsdAll},
     * {@link XsdSequence} or a {@link XsdChoice} instance wrapped in a {@link ReferenceBase} object.
     */
    std::shared_ptr<ReferenceBase> m_childElement;

    /**
     * A {@link XsdElement} instance wrapped in a {@link ReferenceBase} object from which this {@link XsdExtension}
     * instance extends.
     */
    std::shared_ptr<ReferenceBase> m_base;
public: // ctors
    XsdExtension(std::shared_ptr<XsdParserCore> parser,
                 StringMap attributesMap,
                 VisitorFunctionType visitorFunction,
                 std::shared_ptr<XsdAbstractElement> parent)
      : XsdAnnotatedElements(parser, attributesMap, visitorFunction, parent) { }

public:
  virtual void initialize(void) override;
  void replaceUnsolvedElements(std::shared_ptr<NamedConcreteElement> element);

  void accept(std::shared_ptr<XsdAbstractElementVisitor> visitorParam) override
    {
        XsdAnnotatedElements::accept(visitorParam);
        visitorParam->visit(std::static_pointer_cast<XsdExtension>(shared_from_this()));
    }

  virtual std::shared_ptr<XsdAbstractElement> clone(StringMap placeHolderAttributes) override;
  virtual std::list<std::shared_ptr<ReferenceBase>> getElements(void) const override;
  std::shared_ptr<XsdNamedElements> getBase(void) const;

  std::shared_ptr<XsdComplexType> getBaseAsComplexType(void) const;
  std::shared_ptr<XsdSimpleType> getBaseAsSimpleType(void) const;
  std::shared_ptr<XsdBuiltInDataType> getBaseAsBuiltInDataType(void) const;

  

  std::list<std::shared_ptr<XsdAttribute>> getXsdAttributes(void) const;
  std::list<std::shared_ptr<XsdAttributeGroup>> getXsdAttributeGroup(void) const;
  std::shared_ptr<XsdAbstractElement> getXsdChildElement(void) const;

  void setChildElement(std::shared_ptr<ReferenceBase> childElement)
  {
    m_childElement = childElement;
  }

  std::shared_ptr<XsdMultipleElements> getChildElement(void) const;
  std::shared_ptr<XsdGroup> getChildAsGroup(void) const;
  std::shared_ptr<XsdAll> getChildAsAll(void) const;
  std::shared_ptr<XsdChoice> getChildAsChoice(void) const;
  std::shared_ptr<XsdSequence> getChildAsSequence(void) const;
};
