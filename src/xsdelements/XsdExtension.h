#pragma once

#include <core/utils/CommonTypes.h>

#include <xsdelements/XsdAnnotatedElements.h>
#include <xsdelements/visitors/XsdAbstractElementVisitor.h>
#include <xsdelements/elementswrapper/ReferenceBase.h>
#include <xsdelements/elementswrapper/NamedConcreteElement.h>

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
public: // ctors
  XsdExtension(StringMap attributesMap,
               VisitorFunctionType visitorFunction,
               XsdAbstractElement* parent);

  XsdExtension(const XsdExtension& other);

public:
  virtual void replaceUnsolvedElements(NamedConcreteElement* elementWrapper) override;

  void accept(XsdAbstractElementVisitor* visitorParam) override
  {
    XsdAnnotatedElements::accept(visitorParam);
    visitorParam->visit(static_cast<XsdExtension*>(this));
  }

  virtual std::list<ReferenceBase*> getElements(void) const override;


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
  T* getBaseAs(void) const
  {
    if(dynamic_cast<NamedConcreteElement*>(m_base) != nullptr)
      if(auto x = dynamic_cast<T*>(m_base->getElement()); x != nullptr)
        return x;
    return nullptr;
  }

  std::list<XsdAttribute*> getXsdAttributes(void) const;
  std::list<XsdAttributeGroup*> getXsdAttributeGroup(void) const;
  XsdAbstractElement* getXsdChildElement(void) const;

  void setChildElement(ReferenceBase* childElement)
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
  T* getChildAs(void) const
  {
    if (m_childElement != nullptr)
      return dynamic_cast<T*>(m_childElement->getElement());
    return nullptr;
  }

private:
  /**
   * The child element of the {@link XsdExtension} instance. Either a {@link XsdGroup}, {@link XsdAll},
   * {@link XsdSequence} or a {@link XsdChoice} instance wrapped in a {@link ReferenceBase} object.
   */
  ReferenceBase* m_childElement;

  /**
   * A {@link XsdElement} instance wrapped in a {@link ReferenceBase} object from which this {@link XsdExtension}
   * instance extends.
   */
  ReferenceBase* m_base;
};
