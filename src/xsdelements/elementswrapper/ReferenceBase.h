#pragma once

#include <xsdelements/XsdAbstractElement.h>

class XsdParserCore;

/**
 * An abstract class that is meant to wrap all the {@link XsdAbstractElement} objects. Its hierarchy is meant to help
 * in the reference solving process.
 */
class ReferenceBase
{
public:
  std::shared_ptr<XsdAbstractElement> m_element;
public: // ctors
    ReferenceBase(std::shared_ptr<XsdAbstractElement> element);
    virtual ~ReferenceBase(void) = default;
    virtual void initialize(void) { }

  std::shared_ptr<XsdAbstractElement> getElement(void);

    /**
     * This method creates a ReferenceBase object that serves as a wrapper to {@link XsdAbstractElement} objects.
     * If a {@link XsdAbstractElement} has a ref attribute it results in a {@link UnsolvedReference} object. If it
     * doesn't have a ref attribute and has a name attribute it's a {@link NamedConcreteElement}. If it isn't a
     * {@link UnsolvedReference} or a {@link NamedConcreteElement} then it's a {@link ConcreteElement}.
     * @param element The element which will be "wrapped".
     * @return A wrapper object for the element received.
     */
  static std::shared_ptr<ReferenceBase> createFromXsd(std::shared_ptr<XsdAbstractElement> element);

  static std::shared_ptr<ReferenceBase> clone(std::shared_ptr<XsdParserCore> parser,
                                              std::shared_ptr<ReferenceBase> originalReference,
                                              std::shared_ptr<XsdAbstractElement> parent);

  static std::optional<std::string> getRef(std::shared_ptr<XsdAbstractElement> element);

private:
  static std::optional<std::string> getName(std::shared_ptr<XsdAbstractElement> element);

  static std::optional<std::string> getNodeValue(std::shared_ptr<XsdAbstractElement> element, std::string nodeName);
};
