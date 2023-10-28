#pragma once

#include <xsdelements/elementswrapper/ConcreteElement.h>
#include <xsdelements/elementswrapper/ReferenceBase.h>
#include <xsdelements/visitors/XsdAbstractElementVisitor.h>

#include <xsdelements/XsdAnnotatedElements.h>
#include <xsdelements/XsdRestriction.h>
#include <xsdelements/XsdExtension.h>


/**
 * A class representing the xsd:simpleContent element.
 *
 * @see <a href="https://www.w3schools.com/xml/el_simpleContent.asp">xsd:simpleContent description and usage at w3c</a>
 */
class XsdSimpleContent : public XsdAnnotatedElements
{
private:
  /**
   * The {@link XsdRestriction} instance that should be applied to the {@link XsdSimpleContent} instance.
   */
  std::shared_ptr<ReferenceBase> m_restriction;

  /**
   * The {@link XsdExtension} instance that is present in the {@link XsdSimpleContent} instance.
   */
  std::shared_ptr<ReferenceBase> m_extension;
public:
  XsdSimpleContent(std::shared_ptr<XsdParserCore> parser,
                   StringMap attributesMap,
                   VisitorFunctionType visitorFunction,
                   std::shared_ptr<XsdAbstractElement> parent)
    : XsdAnnotatedElements(parser, attributesMap, visitorFunction, parent) { }
public:
    void accept(std::shared_ptr<XsdAbstractElementVisitor> visitorParam) override
    {
      XsdAnnotatedElements::accept(visitorParam);
      visitorParam->visit(std::static_pointer_cast<XsdSimpleContent>(shared_from_this()));
    }

  /**
   * Performs a copy of the current object for replacing purposes. The cloned objects are used to replace
   * {@link UnsolvedReference} objects in the reference solving process.
   * @param placeHolderAttributes The additional attributes to add to the clone.
   * @return A copy of the object from which is called upon.
   */
  virtual std::shared_ptr<XsdAbstractElement> clone(StringMap placeHolderAttributes) override
  {
    placeHolderAttributes.merge(getAttributesMap());

    auto elementCopy = create<XsdSimpleContent>(getParser(),
                                                placeHolderAttributes,
                                                m_visitorFunction,
                                                nullptr);

    elementCopy->m_restriction = ReferenceBase::clone(getParser(), m_restriction, elementCopy);
    elementCopy->m_extension = ReferenceBase::clone(getParser(), m_extension, elementCopy);
    elementCopy->setCloneOf(shared_from_this());

    return elementCopy;
  }

  std::shared_ptr<XsdExtension> getXsdExtension(void) const
  {
    if(auto x = std::dynamic_pointer_cast<ConcreteElement>(m_extension); x)
      return std::static_pointer_cast<XsdExtension>(x->getElement());
    return nullptr;
  }

  std::shared_ptr<XsdRestriction> getXsdRestriction(void) const
  {
    if(auto x = std::dynamic_pointer_cast<ConcreteElement>(m_restriction); x)
      return std::static_pointer_cast<XsdRestriction>(x->getElement());
    return nullptr;
  }

  void setRestriction(std::shared_ptr<ReferenceBase> restriction)
  {
    m_restriction = restriction;
  }

  void setExtension(std::shared_ptr<ReferenceBase> extension)
  {
    m_extension = extension;
  }
};
