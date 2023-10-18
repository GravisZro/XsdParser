#include <xsdelements/enums/XsdEnum.h>
#include <list>

/**
 * An {@link Enum} with all the possible values for the whiteSpace attribute.
 */
class WhiteSpaceEnum : public XsdEnum
{
public:
  using XsdEnum::operator=;
  constexpr static const std::string_view PRESERVE = "preserve";
  constexpr static const std::string_view COLLAPSE = "collapse";
  constexpr static const std::string_view REPLACE = "replace";

  static std::string_view getVariableName(void)
    { return "whitespace"; }

    static std::list<std::string_view> getValues(void)
    {
      return { PRESERVE, COLLAPSE, REPLACE };
    }
};
