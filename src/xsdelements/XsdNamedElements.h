#pragma once

#include <regex>
#include <xsdelements/XsdAnnotatedElements.h>
#include <core/utils/StringOperations.h>

/**
 * This class serves as a base to concrete {@link XsdAbstractElement} classes that can have a name attribute. This is
 * helpful in resolving the references present at the end of the parsing process.
 */
class XsdNamedElements : public XsdAnnotatedElements
{
public: // ctors
  XsdNamedElements(StringMap attributesMap,
                   VisitorFunctionType visitorFunction,
                   XsdAbstractElement* parent)
    : XsdAnnotatedElements(attributesMap, visitorFunction, parent)
  {    
    if(haveAttribute(XsdAbstractElement::NAME_TAG))
      m_name = getAttribute(XsdAbstractElement::NAME_TAG);
  }

public:
  /**
   * Runs verifications on each concrete element to ensure that the XSD schema rules are verified.
   */
  virtual void validateSchemaRules(void) const override
  {
    rule1();
  }

  /**
   * @return The name of the element, with all the special characters replaced with the '_' char.
   */
  std::optional<std::string> getName(void) const
  {
    if(m_name)
    {
      static std::regex non_alphanum("[^a-zA-Z0-9]");
      std::string rval;
      std::regex_replace(std::begin(rval),
                         std::begin(*m_name),
                         std::end(*m_name),
                         non_alphanum, "_");
      return rval;
    }
    return std::nullopt;
  }

  std::optional<std::string> getRawName(void) const
  {
    return m_name;
  }

  void setName(std::string name)
  {
    m_name = name;
  }

private:
  /**
   * Asserts that the current element doesn't have both ref and name attributes at the same time. Throws an exception
   * if they are both present.
   */
  void rule1(void) const
  {
    if (m_name && haveAttribute(REF_TAG))
      throw ParsingException(*NAME_TAG + " and " + REF_TAG + " attributes cannot both be present at the same time.");
  }

private:
  /**
   * The name of the element.
   */
  std::optional<std::string> m_name;
};
