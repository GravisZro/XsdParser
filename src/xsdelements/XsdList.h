#pragma once

#include <xsdelements/XsdSimpleType.h>
#include <xsdelements/elementswrapper/ReferenceBase.h>
#include <xsdelements/elementswrapper/UnsolvedReference.h>
#include <xsdelements/visitors/XsdAbstractElementVisitor.h>

#include <xsdelements/XsdAnnotatedElements.h>


/**
 * A class representing the xsd:list element.
 *
 * @see <a href="https://www.w3schools.com/xml/el_list.asp">xsd:list description and usage at w3c</a>
 */
class XsdList : public XsdAnnotatedElements
{
private:
    /**
     * The {@link XsdSimpleType} instance that states the type of the elements that belong to this {@link XsdList}
     * instance. This value shouldn't be present if there is a {@link XsdList#itemType} present.
     */
    std::shared_ptr<XsdSimpleType> m_simpleType;

    /**
     * The itemType defines the built-it type or the name of a present {@link XsdSimpleType} instance that represent
     * the type of the elements that belong to this {@link XsdList}. This value shouldn't be present if there is a
     * {@link XsdList#simpleType} is present.
     */
    std::optional<std::string> m_itemType;
public: // ctors
  XsdList(std::shared_ptr<XsdParserCore> parser,
          StringMap attributesMap,
          VisitorFunctionType visitorFunction,
          std::shared_ptr<XsdAbstractElement> parent)
    : XsdAnnotatedElements(parser, attributesMap, visitorFunction, parent)
  {
  }
public:
  virtual void initialize(void) override
  {
    XsdAnnotatedElements::initialize();
    m_simpleType.reset();
    m_itemType.reset();
    if(haveAttribute(ITEM_TYPE_TAG))
      m_itemType = getAttribute(ITEM_TYPE_TAG);
  }
public:
    void accept(std::shared_ptr<XsdAbstractElementVisitor> visitorParam) override
    {
        XsdAnnotatedElements::accept(visitorParam);
        visitorParam->visit(std::static_pointer_cast<XsdList>(shared_from_this()));
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

        auto elementCopy = create<XsdList>(getParser(),
                                           placeHolderAttributes,
                                           m_visitorFunction,
                                           nullptr);

        if (m_simpleType)
            elementCopy->m_simpleType = std::static_pointer_cast<XsdSimpleType>(
                                          m_simpleType->XsdAbstractElement::clone(m_simpleType->getAttributesMap(),
                                                              elementCopy));

        return elementCopy;
    }

  std::shared_ptr<XsdSimpleType> getXsdSimpleType(void) {
        return m_simpleType;
    }

  std::optional<std::string> getItemType(void) {
        return m_itemType;
    }

  void setSimpleType(std::shared_ptr<XsdSimpleType> simpleType) {
        m_simpleType = simpleType;
    }
};
