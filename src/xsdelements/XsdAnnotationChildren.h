#pragma once

#include <core/utils/StringOperations.h>
#include <pugixml.hpp>

#include <xsdelements/elementswrapper/ReferenceBase.h>
#include <xsdelements/exceptions/VisitorNotFoundException.h>
#include <xsdelements/XsdAbstractElement.h>

/**
 * This class serves as a base to both {@link XsdAppInfo} and {@link XsdDocumentation} since they share similarities.
 */
class XsdAnnotationChildren : public XsdAbstractElement
{
public: // ctors
  XsdAnnotationChildren(StringMap attributesMap,
                        VisitorFunctionType visitorFunction,
                        XsdAbstractElement* parent)
    : XsdAbstractElement(attributesMap, visitorFunction, parent)
  {
    if(haveAttribute(SOURCE_TAG))
      m_source = getAttribute(SOURCE_TAG);
  }

public:
  /**
   * @return Always returns a {@link VisitorNotFoundException} since the descendants of this class shouldn't be
   * visited since they aren't allowed to have children.
   */
  XsdAbstractElementVisitor* getVisitor(void) const override
  {
    throw VisitorNotFoundException("AppInfo/Documentation can't have children.");
  }

  std::optional<std::string> getSource(void) const
  {
    return m_source;
  }

  std::optional<std::string> getContent(void) const
  {
    return m_content;
  }

  /**
   * This method is used to parse {@link XsdAnnotationChildren} instances.
   * @param node The node containing the information to parse.
   * @param annotationChildren An instance of {@link XsdAnnotationChildren} (either {@link XsdAppInfo} or
   *                           {@link XsdDocumentation}).
   * @return The annotationChildren wrapped in the correct {@link ReferenceBase} wrapper.
   */
  static ReferenceBase* xsdAnnotationChildrenParse(pugi::xml_node node,
                                                   XsdAnnotationChildren* annotationChildren)
  {
    annotationChildren->m_content = xsdRawContentParse(node);

    return ReferenceBase::createFromXsd(annotationChildren);
  }

private:
  /**
   * An URI that specifies a source for the application information.
   */
  std::optional<std::string> m_source;

  /**
   * The textual content of the current element, either {@link XsdAppInfo} or {@link XsdDocumentation}.
   */
  std::optional<std::string> m_content;
};
