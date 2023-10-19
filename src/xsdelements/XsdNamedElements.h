#pragma once

#include <regex>
#include <xsdelements/XsdAnnotatedElements.h>
#include <core/utils/CommonOperations.h>

/**
 * This class serves as a base to concrete {@link XsdAbstractElement} classes that can have a name attribute. This is
 * helpful in resolving the references present at the end of the parsing process.
 */
class XsdNamedElements : public XsdAnnotatedElements
{
public:
  using XsdAnnotatedElements::clone;
    /**
     * The name of the element.
     */
    std::optional<std::string> m_name;

    XsdNamedElements(std::shared_ptr<XsdParserCore> parser,
                     StringMap attributesMap,
                     VisitorFunctionReference visitorFunction);

    /**
     * Runs verifications on each concrete element to ensure that the XSD schema rules are verified.
     */
  void validateSchemaRules(void)
    {
        rule1();
    }

    /**
     * Asserts that the current element doesn't have both ref and name attributes at the same time. Throws an exception
     * if they are both present.
     */
private:
  void rule1(void)
  {
        if (!m_name && m_attributesMap.contains(*REF_TAG))
        {
          throw new ParsingException(*NAME_TAG + " and " + REF_TAG + " attributes cannot both be present at the same time.");
        }

    }

public:
    /**
     * @return The name of the element, with all the special characters replaced with the '_' char.
     */
  std::optional<std::string> getName(void)
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

  std::optional<std::string> getRawName(void)
  {
        return m_name;
  }

  void setName(std::string name) {
        m_name = name;
    }
};
