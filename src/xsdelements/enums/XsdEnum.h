#pragma once

#include <core/utils/CommonTypes.h>
#include <core/utils/CommonOperations.h>
#include <optional>

/**
 * A shared interface for all the {@link Enum} classes of this solution.
 * @param <T> The concrete type of the {@link Enum}.
 */
class XsdEnum
{
private:
  std::optional<std::string> value;
public:
  XsdEnum(void) = default;

  XsdEnum(std::string_view value)
    : value(std::string(value)) { }
  XsdEnum(std::optional<std::string> value)
    : value(value) { }

  void operator =(const std::string_view& v) { value = v; }
  void operator =(const std::string& v) { value = v; }
  void operator =(const std::optional<std::string>& v) { value = v; }
  operator bool (void) const { return value.has_value(); }

  /**
   * @return The concrete value of the current instance.
   */
  std::optional<std::string> getValue(void) { return value; }

  /**
   * @return The name of the attribute that the {@link Enum} represents.
   */
//  virtual static std::string_view getVariableName(void) = 0;

  /**
   * @return The values that the attribute can have.
   */
//  virtual static std::list<std::string_view> getValues(void) = 0;
};
