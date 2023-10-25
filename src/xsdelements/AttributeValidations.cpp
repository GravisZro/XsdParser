#include "AttributeValidations.h"

#include <xsdelements/XsdSchema.h>


#include <algorithm>


namespace AttributeValidations
{
  std::string attributeMissingMessage(std::string_view elementName, std::string_view attributeName)
  {
    return "The "s + elementName + " " + attributeName + " is required to have a value attribute."sv;
  }

  /**
   * Checks if the maxOccurs attribute is unbounded or an {@link int} value.
   * @param value The possible maxOccurs value.
   * @param elementName The name of the element containing the maxOccurs attribute.
   * @return The validated maxOccurs value.
   */
  std::string maxOccursValidation(std::string elementName, std::string value)
  {
    if (value == "unbounded")
      return value;

    validateNonNegativeInteger(elementName, *XsdAbstractElement::MAX_OCCURS_TAG, value);
    return value;
  }

  /**
   * Validates if a given std::string is a non negative {@link int}. Throws an exception if the {@link std::string} isn't a non
   * negative {@link int}.
   * @param elementName The element name containing the field with the {@link int} value.
   * @param attributeName The name of the attribute with the {@link int}.
   * @param value The value to be parsed to a {@link int} object.
   * @return The parsed {@link int} value.
   */
  int validateNonNegativeInteger(std::string elementName, std::string attributeName, std::string value)
  {
    try
    {
      int intValue = std::stoi(value.c_str());
      if (intValue < 0)
        throw ParsingException("The " + elementName + " " + attributeName + " attribute should be a non negative integer. (greater or equal than 0)");
      return intValue;
    } catch (...)
    {
      throw ParsingException("The " + elementName + " " + attributeName + "  attribute should be a non negative integer.");
    }
  }


  /**
   * Validates if a given std::string is a non negative {@link int}. Throws an exception if the {@link std::string} isn't a
   * non negative {@link int}.
   * @param elementName The element name containing the field with the {@link int} value.
   * @param attributeName The name of the attribute with the {@link int}.
   * @param value The value to be parsed to a {@link int} object.
   * @return The parsed {@link int} value.
   */
  int validateRequiredNonNegativeInteger(std::string elementName, std::string attributeName, std::optional<std::string> value)
  {
    if(!value)
      throw ParsingException(attributeMissingMessage(elementName, attributeName));
    return validateNonNegativeInteger(elementName, attributeName, value.value());
  }

  /**
   * Validates if a given std::string is a positive {@link int}. Throws an exception if the {@link std::string} isn't a
   * positive {@link int}.
   * @param elementName The element name containing the field with the {@link int} value.
   * @param attributeName The name of the attribute with the {@link int} type.
   * @param value The value to be parsed to a {@link int} object.
   * @return The parsed {@link int} value.
   */
  int validatePositiveInteger(std::string elementName, std::string attributeName, std::string value)
  {
    try
    {
      int intValue = std::stoi(value.c_str());
      if (intValue <= 0)
        throw ParsingException("The " + elementName + " " + attributeName + " attribute should be a positive integer. (greater than 0)");
      return intValue;
    }
    catch (...)
    {
      throw ParsingException("The " + elementName + " " + attributeName + " attribute should be a positive integer.");
    }
  }


  /**
   * Validates if a given std::string is a positive {@link int}. Throws an exception if the {@link std::string} isn't a
   * positive {@link int}.
   * @param elementName The element name containing the field with the {@link int} value.
   * @param attributeName The name of the attribute with the {@link int} type.
   * @param value The value to be parsed to a {@link int} object.
   * @return The parsed {@link int} value.
   */
  int validateRequiredPositiveInteger(std::string elementName, std::string attributeName, std::string value)
  {
    if (value.empty())
      throw ParsingException(attributeMissingMessage(elementName, attributeName));
    return validatePositiveInteger(elementName, attributeName, value);
  }

  bool validateBoolean(std::string value)
  {
    std::transform(std::begin(value), std::end(value), std::begin(value), ::tolower);
    return value == "true";
  }

  /**
   * Validates if a given {@link std::string} is a {@link double}. Throws an exception if the {@link std::string} isn't a
   * {@link double}.
   * @param elementName The element name containing the field with the {@link double} value.
   * @param attributeName The name of the attribute with the type {@link double}.
   * @param value The value to be parsed to a {@link double} object.
   * @return The parsed {@link double} value.
   */
  double validateDouble(std::string elementName, std::string attributeName, std::string value)
  {
    try
    {
      return std::stod(value.c_str());
    } catch (...)
    {
      throw ParsingException("The " + elementName + " " + attributeName + " attribute should be a numeric value.");
    }
  }

  /**
   * Validates if a given {@link std::string} is a {@link double}. Throws an exception if the {@link std::string} isn't a {@link double}.
   * @param elementName The element name containing the field with the {@link double} value.
   * @param attributeName The name of the attribute with the type {@link double}.
   * @param value The value to be parsed to a {@link double} object.
   * @return The parsed {@link double} value.
   */
  double validateRequiredDouble(std::string elementName, std::string attributeName, std::string value)
  {
    if (value.empty())
      throw ParsingException(attributeMissingMessage(elementName, attributeName));
    return validateDouble(elementName, attributeName, value);
  }

  /**
   * Obtains the default value of the {@link XsdSchema#attributeFormDefault} attribute by iterating in the  element tree
   * by going from {@link XsdAbstractElement#parent} to {@link XsdAbstractElement#parent} until reaching the top level
   * element.
   * @param parent The parent of the element requesting the default form value.
   * @return The default value for the form attribute.
   */
  std::string getFormDefaultValue(std::shared_ptr<XsdAbstractElement> parent)
  {
    if (parent == nullptr)
      return {};

    if (auto x = std::dynamic_pointer_cast<XsdSchema>(parent); x)
      return x->getElementFormDefault().value();
    return getFormDefaultValue(parent->getParent());
  }

  /**
   * Obtains the default value of the {@link XsdSchema#finalDefault} attribute by iterating in the element tree by
   * going from {@link XsdAbstractElement#parent} to {@link XsdAbstractElement#parent} until reaching the top level
   * element.
   * @param parent The parent of the element requesting the default final value.
   * @return The default value for the final attribute.
   */
  std::string getFinalDefaultValue(std::shared_ptr<XsdAbstractElement> parent)
  {
    if (parent == nullptr)
      return {};

    if (auto x = std::dynamic_pointer_cast<XsdSchema>(parent); x)
      return x->getFinalDefault().value();
    return getFinalDefaultValue(parent->getParent());
  }

  /**
   * Obtains the default value of the {@link XsdSchema#blockDefault} attribute by iterating in the element tree by
   * going from {@link XsdAbstractElement#parent} to {@link XsdAbstractElement#parent} until reaching the top level
   * element.
   * @param parent The parent of the element requesting the default block value.
   * @return The default value for the block attribute.
   */
  std::string getBlockDefaultValue(std::shared_ptr<XsdAbstractElement> parent)
  {
    if (parent == nullptr)
      return {};

    if (auto x = std::dynamic_pointer_cast<XsdSchema>(parent); x)
      return x->getBlockDefault().value();
    return getBlockDefaultValue(parent->getParent());
  }
}
