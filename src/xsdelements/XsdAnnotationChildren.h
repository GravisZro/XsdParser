#pragma once

#include <core/utils/CommonOperations.h>
#include <pugixml.hpp>

#include <xsdelements/elementswrapper/ReferenceBase.h>
#include <xsdelements/exceptions/VisitorNotFoundException.h>
#include <xsdelements/XsdAbstractElement.h>

class XsdParserCore;

/**
 * This class serves as a base to both {@link XsdAppInfo} and {@link XsdDocumentation} since they share similarities.
 */
class XsdAnnotationChildren : public XsdAbstractElement
{
public:
  using XsdAbstractElement::clone;

private:
    /**
     * An URI that specifies a source for the application information.
     */
    std::optional<std::string> m_source;

    /**
     * The textual content of the current element, either {@link XsdAppInfo} or {@link XsdDocumentation}.
     */
    std::optional<std::string> m_content;
public: // ctors
    XsdAnnotationChildren(std::shared_ptr<XsdParserCore> parser,
                          StringMap attributesMap)
      : XsdAbstractElement(parser, attributesMap, nullptr, nullptr)
  {
      if(haveAttribute(SOURCE_TAG))
        m_source = getAttribute(SOURCE_TAG);
    }
public:
    /**
     * @return Always returns a {@link VisitorNotFoundException} since the descendants of this class shouldn't be
     * visited since they aren't allowed to have children.
     */
  XsdAbstractElementVisitor getVisitor(void)
    {
        throw VisitorNotFoundException("AppInfo/Documentation can't have children.");
    }

  std::optional<std::string> getSource(void) {
        return m_source;
    }

  std::optional<std::string> getContent(void) {
        return m_content;
    }

    /**
     * This method is used to parse {@link XsdAnnotationChildren} instances.
     * @param node The node containing the information to parse.
     * @param annotationChildren An instance of {@link XsdAnnotationChildren} (either {@link XsdAppInfo} or
     *                           {@link XsdDocumentation}).
     * @return The annotationChildren wrapped in the correct {@link ReferenceBase} wrapper.
     */
    static std::shared_ptr<ReferenceBase> xsdAnnotationChildrenParse(pugi::xml_node node,
                                                                     std::shared_ptr<XsdAnnotationChildren> annotationChildren)
    {
        annotationChildren->m_content = xsdRawContentParse(node);

        return ReferenceBase::createFromXsd(annotationChildren);
    }

};
