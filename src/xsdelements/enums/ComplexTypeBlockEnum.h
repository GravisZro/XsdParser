#pragma once

#include <xsdelements/enums/XsdEnum.h>

/**
 * An {@link Enum} with all the possible values for the block attribute of {@link XsdComplexType}.
 */
class ComplexTypeBlockEnum : public XsdEnum
{
public:
  using XsdEnum::operator=;
  constexpr static const std::string_view EXTENSION = "extension";
  constexpr static const std::string_view RESTRICTION = "restriction";
  constexpr static const std::string_view ALL = "#all";

  static std::string_view getVariableName(void)
    { return "block"; }

  static std::list<std::string_view> getValues(void)
  {
    return { EXTENSION, RESTRICTION, ALL };
  }
};
