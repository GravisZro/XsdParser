#pragma once

#include <xsdelements/enums/XsdEnum.h>

/**
 * An {@link Enum} with all the possible values for the usage attribute.
 */
class UsageEnum : public XsdEnum
{
public:
  using XsdEnum::operator=;

  constexpr static const std::string_view REQUIRED = "required";
  constexpr static const std::string_view PROHIBITED = "prohibited";
  constexpr static const std::string_view OPTIONAL = "optional";

  static std::string_view getVariableName(void)
    { return "use"; }

  static std::list<std::string_view> getValues(void)
  {
    return { REQUIRED, PROHIBITED, OPTIONAL };
  }
};
