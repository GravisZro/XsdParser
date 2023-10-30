#pragma once

#include <xsdelements/XsdAbstractElement.h>

/**
 * An abstract class that is meant to wrap all the {@link XsdAbstractElement} objects. Its hierarchy is meant to help
 * in the reference solving process.
 */
class ReferenceBase
{
public:
  XsdAbstractElement* m_element;
public: // ctors
    ReferenceBase(XsdAbstractElement* element)
      : m_element(element) { }

    ReferenceBase(ReferenceBase* other, XsdAbstractElement* parent);

    virtual ~ReferenceBase(void) = default;

  XsdAbstractElement* getElement(void) const { return m_element; }

    /**
     * This method creates a ReferenceBase object that serves as a wrapper to {@link XsdAbstractElement} objects.
     * If a {@link XsdAbstractElement} has a ref attribute it results in a {@link UnsolvedReference} object. If it
     * doesn't have a ref attribute and has a name attribute it's a {@link NamedConcreteElement}. If it isn't a
     * {@link UnsolvedReference} or a {@link NamedConcreteElement} then it's a {@link ConcreteElement}.
     * @param element The element which will be "wrapped".
     * @return A wrapper object for the element received.
     */
  static ReferenceBase* createFromXsd(XsdAbstractElement* element);

  static std::optional<std::string> getRef(XsdAbstractElement* element);

private:
  static std::optional<std::string> getName(XsdAbstractElement* element);
  static std::optional<std::string> getNodeValue(XsdAbstractElement* element, std::string nodeName);
};
