#pragma once

#include <core/utils/CommonTypes.h>
#include <core/utils/StringOperations.h>

/**
 * A shared interface for all the {@link Enum} classes of this solution.
 * @param <T> The concrete type of the {@link Enum}.
 */
class XsdEnum
{
private:
  std::optional<std::string> m_value;
public:
  XsdEnum(void) = default;

  XsdEnum(std::string_view value)
    : m_value(std::string(value)) { }
  XsdEnum(std::optional<std::string> value)
    : m_value(value) { }

  void operator =(const std::string_view& value) { m_value = value; }
  void operator =(const std::string& value) { m_value = value; }
  void operator =(const std::optional<std::string>& value) { m_value = value; }
  operator bool (void) const { return m_value.has_value(); }

  void reset(void) { m_value.reset(); }

  /**
   * @return The concrete value of the current instance.
   */
  std::optional<std::string> getValue(void) const { return m_value; }

  /**
   * @return The name of the attribute that the {@link Enum} represents.
   */
//  virtual static std::string_view getVariableName(void) = 0;

  /**
   * @return The values that the attribute can have.
   */
//  virtual static std::list<std::string_view> getValues(void) = 0;
};
