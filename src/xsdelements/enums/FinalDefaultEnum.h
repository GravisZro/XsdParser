#pragma once

#include <xsdelements/enums/XsdEnum.h>

/**
 * An {@link Enum} with all the possible values for the finalDefault attribute of {@link XsdSchema}.
 */
class FinalDefaultEnum : public XsdEnum
{
public:
  using XsdEnum::operator=;
  constexpr static const std::string_view DEFAULT = "";
  constexpr static const std::string_view EXTENSION = "extension";
  constexpr static const std::string_view RESTRICTION = "restriction";
  constexpr static const std::string_view LIST = "list";
  constexpr static const std::string_view UNION = "union";
  constexpr static const std::string_view ALL = "#all";

//  static final FinalDefaultEnum instance = FinalDefaultEnum::DEFAULT;

  static std::string_view getVariableName(void)
    { return "finalDefault"; }

  static std::list<std::string_view> getValues(void)
  {
    return { DEFAULT, EXTENSION, RESTRICTION, LIST, UNION, ALL };
  }
};
