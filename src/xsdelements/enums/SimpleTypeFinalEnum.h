#pragma once

#include <xsdelements/enums/XsdEnum.h>

/**
 * An {@link Enum} with all the possible values for the final attribute of {@link XsdSimpleType}.
 */
class SimpleTypeFinalEnum : public XsdEnum
{
public:
  using XsdEnum::operator=;
  constexpr static const std::string_view LIST = "list";
  constexpr static const std::string_view UNION = "union";
  constexpr static const std::string_view RESTRICTION = "restriction";
  constexpr static const std::string_view ALL = "#all";

  static std::string_view getVariableName(void)
    { return "final"; }

  static std::list<std::string_view> getValues(void)
  {
    return { RESTRICTION, LIST, UNION, ALL };
  }
};
