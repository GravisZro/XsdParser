#pragma once

#include <xsdelements/XsdAnnotatedElements.h>

class ReferenceBase;
class XsdAll;
class XsdChoice;
class XsdSequence;
class XsdElement;
class NamedConcreteElement;

/**
 * A class that serves as a base class to three classes that share similarities, {@link XsdAll}, {@link XsdChoice} and
 * {@link XsdSequence}. Those three classes share {@link XsdMultipleElements#elements} which is a list of
 * {@link XsdAbstractElement} objects contained in each of these types. The types of the instances present in the
 * {@link XsdMultipleElements#elements} list depends on the concrete type, {@link XsdAll}, {@link XsdChoice} or
 * {@link XsdSequence}.
 */
class XsdMultipleElements : public XsdAnnotatedElements
{
public: // ctors
  XsdMultipleElements(StringMap attributesMap,
                      VisitorFunctionType visitorFunction,
                      XsdAbstractElement* parent)
    : XsdAnnotatedElements(attributesMap, visitorFunction, parent)
  {
  }
public:
  /**
   * Replaces possible {@link UnsolvedReference} objects in the {@link XsdMultipleElements#elements} if any of their
   * {@link UnsolvedReference#ref} field matches the {@link NamedConcreteElement#name} field.
   * @param elementWrapper A {@link NamedConcreteElement} with a name that will replace an {@link UnsolvedReference}
   *                       object, if a match between the {@link NamedConcreteElement#name} attribute and the
   *                       {@link UnsolvedReference#ref} attribute.
   */
  virtual void replaceUnsolvedElements(NamedConcreteElement* elementWrapper) override;

  /**
     * @return All the elements received in the parsing process.
     */
  std::list<ReferenceBase*> getElements(void) const override
  {
    return m_elements;
  }

  /**
   * @return The elements that are fully resolved. The {@link UnsolvedReference} objects aren't returned.
   */
  std::list<XsdAbstractElement*> getXsdElements(void) const override;

  /**
   * @tparam One of the following classes:
   *      * {@link XsdElement}
   *      * {@link XsdChoice}
   *      * {@link XsdSequence}
   *      * {@link XsdGroup}
   * @return The children elements that are of the templated type.
   */
  template<typename T, std::enable_if_t<std::is_same_v<XsdElement , T> ||
                                        std::is_same_v<XsdChoice  , T> ||
                                        std::is_same_v<XsdSequence, T> ||
                                        std::is_same_v<XsdGroup   , T>, bool> = true>
  std::list<T*> getChildren(void) const
  {
    std::list<T*> targets;
    for(auto& element : getXsdElements())
      if(auto x = dynamic_cast<T*>(element); x != nullptr)
        targets.push_back(x);
    return targets;
  }

  void addElement(XsdAbstractElement* element);
protected:
  /**
   * A list of elements that are contained in the concrete implementation of the {@link XsdMultipleElements} instance.
   */
  std::list<ReferenceBase*> m_elements;
};
