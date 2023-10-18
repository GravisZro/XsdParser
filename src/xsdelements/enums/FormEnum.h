#pragma once

#include <xsdelements/enums/XsdEnum.h>

/**
 * An {@link Enum} with all the possible values for the form attribute.
 */
class FormEnum : public XsdEnum
{
public:
  using XsdEnum::operator=;
  constexpr static const std::string_view QUALIFIED = "qualified";
  constexpr static const std::string_view UNQUALIFIED = "unqualified";

  static std::string_view getVariableName(void)
    { return "form/elementFormDefault/attributeFormDefault"; }

  static std::list<std::string_view> getValues(void)
  {
    return { QUALIFIED, UNQUALIFIED };
  }
};
