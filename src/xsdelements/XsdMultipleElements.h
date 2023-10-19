#pragma once


//#include <xsdelements/elementswrapper/ConcreteElement.h>
//#include <xsdelements/elementswrapper/ReferenceBase.h>
//#include <xsdelements/elementswrapper/UnsolvedReference.h>
//#include <xsdelements/visitors/XsdAbstractElementVisitor.h>


#include <xsdelements/XsdAnnotatedElements.h>
#include <xsdelements/elementswrapper/NamedConcreteElement.h>


class ReferenceBase;
class XsdAbstractElementVisitor;
class XsdAbstractElement;
class XsdParserCore;

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

public:
    XsdMultipleElements(std::shared_ptr<XsdParserCore> parser,
                        StringMap elementFieldsMapParam,
                        VisitorFunctionReference visitorFunction);

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
  std::list<std::shared_ptr<ReferenceBase>> getElements(void);

    /**
     * @return The elements that are fully resolved. The {@link UnsolvedReference} objects aren't returned.
     */
  std::list<std::shared_ptr<XsdAbstractElement>> getXsdElements(void);

    /**
     * @return The children elements that are of the type {@link XsdElement}.
     */
    // @SuppressWarnings("unused")
  std::list<std::shared_ptr<XsdElement>> getChildrenElements(void);

  void addElement(std::shared_ptr<XsdAbstractElement> element);

  static std::shared_ptr<XsdAll> getChildAsAll(std::shared_ptr<XsdMultipleElements> element);
  static std::shared_ptr<XsdChoice> getChildAsChoice(std::shared_ptr<XsdMultipleElements> element);
  static std::shared_ptr<XsdSequence> getChildAsSequence(std::shared_ptr<XsdMultipleElements> element);
};
