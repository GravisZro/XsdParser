#pragma once

#include <xsdelements/XsdAnnotatedElements.h>
#include <xsdelements/elementswrapper/NamedConcreteElement.h>

class ReferenceBase;
class XsdAll;
class XsdChoice;
class XsdSequence;
class XsdElement;

/**
 * A class that serves as a base class to three classes that share similarities, {@link XsdAll}, {@link XsdChoice} and
 * {@link XsdSequence}. Those three classes share {@link XsdMultipleElements#elements} which is a list of
 * {@link XsdAbstractElement} objects contained in each of these types. The types of the instances present in the
 * {@link XsdMultipleElements#elements} list depends on the concrete type, {@link XsdAll}, {@link XsdChoice} or
 * {@link XsdSequence}.
 */
class XsdMultipleElements : public XsdAnnotatedElements
{
public:
  using XsdAnnotatedElements::clone;

protected:
    /**
     * A list of elements that are contained in the concrete implementation of the {@link XsdMultipleElements} instance.
     */
  std::list<std::shared_ptr<ReferenceBase>> m_elements;

public: // ctors
  XsdMultipleElements(std::shared_ptr<XsdParserCore> parser,
                      StringMap attributesMap,
                      VisitorFunctionType visitorFunction,
                      std::shared_ptr<XsdAbstractElement> parent)
    : XsdAnnotatedElements(parser, attributesMap, visitorFunction, parent) { }

public:
  virtual void initialize(void) override
  {
    XsdAnnotatedElements::initialize();
    m_elements.clear();
  }
    /**
     * Replaces possible {@link UnsolvedReference} objects in the {@link XsdMultipleElements#elements} if any of their
     * {@link UnsolvedReference#ref} field matches the {@link NamedConcreteElement#name} field.
     * @param elementWrapper A {@link NamedConcreteElement} with a name that will replace an {@link UnsolvedReference}
     *                       object, if a match between the {@link NamedConcreteElement#name} attribute and the
     *                       {@link UnsolvedReference#ref} attribute.
     */
  void replaceUnsolvedElements(std::shared_ptr<NamedConcreteElement> elementWrapper);

    /**
     * @return All the elements received in the parsing process.
     */
  virtual std::list<std::shared_ptr<ReferenceBase>> getElements(void) override;

    /**
     * @return The elements that are fully resolved. The {@link UnsolvedReference} objects aren't returned.
     */
  virtual std::list<std::shared_ptr<XsdAbstractElement>> getXsdElements(void) override;

    /**
     * @return The children elements that are of the type {@link XsdElement}.
     */
    
  std::list<std::shared_ptr<XsdElement>> getChildrenElements(void);

  void addElement(std::shared_ptr<XsdAbstractElement> element);

  static std::shared_ptr<XsdAll> getChildAsAll(std::shared_ptr<XsdMultipleElements> element);
  static std::shared_ptr<XsdChoice> getChildAsChoice(std::shared_ptr<XsdMultipleElements> element);
  static std::shared_ptr<XsdSequence> getChildAsSequence(std::shared_ptr<XsdMultipleElements> element);
};
