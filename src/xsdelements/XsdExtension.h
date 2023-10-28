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


  /**
   * @tparam One of the following classes:
   *      * {@link XsdNamedElements}
   *      * {@link XsdComplexType}
   *      * {@link XsdSimpleType}
   *      * {@link XsdBuiltInDataType}
   * @return the base from which this extension extends or null if the {@link XsdParserCore} wasn't able to
   * replace the {@link UnsolvedReference} created by the base attribute value.
   */
  template<typename T, std::enable_if_t<std::is_same_v<XsdNamedElements  , T> ||
                                        std::is_same_v<XsdComplexType    , T> ||
                                        std::is_same_v<XsdSimpleType     , T> ||
                                        std::is_same_v<XsdBuiltInDataType, T>, bool> = true>
  std::shared_ptr<T> getBaseAs(void) const
  {
    if(std::dynamic_pointer_cast<NamedConcreteElement>(m_base))
      if(auto x = std::dynamic_pointer_cast<T>(m_base->getElement()); x)
        return x;
    return nullptr;
  }

  std::list<std::shared_ptr<XsdAttribute>> getXsdAttributes(void) const;
  std::list<std::shared_ptr<XsdAttributeGroup>> getXsdAttributeGroup(void) const;
  std::shared_ptr<XsdAbstractElement> getXsdChildElement(void) const;

  void setChildElement(std::shared_ptr<ReferenceBase> childElement)
  {
    m_childElement = childElement;
  }

  /**
   * @tparam One of the following classes:
   *      * {@link XsdAbstractElement}
   *      * {@link XsdMultipleElements}
   *      * {@link XsdGroup}
   *      * {@link XsdAll}
   *      * {@link XsdChoice}
   *      * {@link XsdSequence}
   *      * {@link XsdElement}
   * @return The children element that are of the templated type or null if the template type doesn't
   * match the object's type.
   */
  template<typename T, std::enable_if_t<std::is_same_v<XsdAbstractElement , T> ||
                                        std::is_same_v<XsdMultipleElements, T> ||
                                        std::is_same_v<XsdGroup           , T> ||
                                        std::is_same_v<XsdAll             , T> ||
                                        std::is_same_v<XsdChoice          , T> ||
                                        std::is_same_v<XsdSequence        , T> ||
                                        std::is_same_v<XsdElement         , T>, bool> = true>
  std::shared_ptr<T> getChildAs(void) const
  {
    if (m_childElement)
      return std::dynamic_pointer_cast<T>(m_childElement->getElement());
    return nullptr;
  }
};
