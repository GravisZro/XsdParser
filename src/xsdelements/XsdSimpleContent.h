#pragma once


//#include <core/XsdParserCore.h>
#include <core/utils/ParseData.h>
#include <xsdelements/elementswrapper/ConcreteElement.h>
#include <xsdelements/elementswrapper/ReferenceBase.h>
#include <xsdelements/elementswrapper/UnsolvedReference.h>
#include <xsdelements/visitors/XsdAbstractElementVisitor.h>

#include <xsdelements/XsdAnnotatedElements.h>

#include <map>
#include <functional>

/**
 * A class representing the xsd:simpleContent element.
 *
 * @see <a href="https://www.w3schools.com/xml/el_simpleContent.asp">xsd:simpleContent description and usage at w3c</a>
 */
class XsdSimpleContent : public XsdAnnotatedElements
{
public:
  using XsdAnnotatedElements::clone;
    constexpr static const std::string_view XSD_TAG = "xsd:simpleContent";
    constexpr static const std::string_view XS_TAG = "xs:simpleContent";
    constexpr static const std::string_view TAG = "simpleContent";

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
    XsdSimpleContent(std::shared_ptr<XsdParserCore> parser, StringMap elementFieldsMapParam, VisitorFunctionReference visitorFunction)
        : XsdAnnotatedElements(parser, elementFieldsMapParam, visitorFunction) { }
public:
  void accept(std::shared_ptr<XsdAbstractElementVisitor> visitorParam)
    {
        XsdAnnotatedElements::accept(visitorParam);
        visitorParam->visit(std::shared_ptr<XsdSimpleContent>(this));
    }

    /**
     * Performs a copy of the current object for replacing purposes. The cloned objects are used to replace
     * {@link UnsolvedReference} objects in the reference solving process.
     * @param placeHolderAttributes The additional attributes to add to the clone.
     * @return A copy of the object from which is called upon.
     */
  std::shared_ptr<XsdSimpleContent> clone(StringMap placeHolderAttributes)
    {
        placeHolderAttributes.merge(m_attributesMap);

        auto elementCopy = std::make_shared<XsdSimpleContent>(m_parser, placeHolderAttributes, m_visitorFunction);

        elementCopy->m_restriction = ReferenceBase::clone(m_parser, m_restriction, elementCopy);
        elementCopy->m_extension = ReferenceBase::clone(m_parser, m_extension, elementCopy);
        elementCopy->m_cloneOf = std::shared_ptr<XsdAbstractElement>(this);
        elementCopy->m_parent = nullptr;

        return elementCopy;
    }

  std::shared_ptr<XsdExtension> getXsdExtension(void)
  {
    if(auto e = std::dynamic_pointer_cast<ConcreteElement>(m_extension))
      return std::static_pointer_cast<XsdExtension>(e->getElement());
    return nullptr;
  }

  std::shared_ptr<XsdRestriction> getXsdRestriction(void)
  {
    if(auto r = std::dynamic_pointer_cast<ConcreteElement>(m_restriction))
      return std::static_pointer_cast<XsdRestriction>(r->getElement());
    return nullptr;
  }

  static std::shared_ptr<ReferenceBase> parse(ParseData parseData)
  {
        return xsdParseSkeleton(parseData.node, std::static_pointer_cast<XsdAbstractElement>(std::make_shared<XsdSimpleContent>(parseData.parserInstance, XsdAbstractElement::getAttributesMap(parseData.node), parseData.visitorFunction)));
    }

  void setRestriction(std::shared_ptr<ReferenceBase> restriction) {
        m_restriction = restriction;
    }

  void setExtension(std::shared_ptr<ReferenceBase> extension) {
        m_extension = extension;
    }
};
