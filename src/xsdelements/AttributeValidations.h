#pragma once

#include <xsdelements/XsdAbstractElement.h>
#include <xsdelements/enums/XsdEnum.h>
#include <xsdelements/exceptions/ParsingException.h>

#include <algorithm>

class AttributeValidations
{
private:
  AttributeValidations(void) = delete;

public:
    /**
     * Verifies if a given value is present in a given {@link Enum} type.
     * @param instance An instance of the concrete {@link Enum} type that is expected to contain the {@code value} received.
     * @param value The value that is expected to be present in the received {@link Enum} type.
     * @param <T> The concrete type of the {@link Enum} type.
     * @return The instance of the concrete {@link Enum} type that represents {@code value} in the respective {@link Enum}.
     */
  template<typename T>
  static T belongsToEnum(std::string value)
  {
        if (value.empty())
          return {};

        T enumValue;
        for(auto& val : T::getValues())
          enumValue = val;

        if(enumValue)
          return enumValue;

        std::string possibleValues;
        for(auto& val : T::getValues())
          possibleValues += val + ",  ";

      throw new ParsingException("The attribute " + *T::getVariableName() + " doesn't support the value \"" + value + "\".\n" +
                                 "The possible values for the " + *T::getVariableName() + " attribute are:\n" +
                                 possibleValues.substr(0, possibleValues.length() - 2));
    }

    /**
     * Checks if the maxOccurs attribute is unbounded or an {@link int} value.
     * @param value The possible maxOccurs value.
     * @param elementName The name of the element containing the maxOccurs attribute.
     * @return The validated maxOccurs value.
     */
    static std::string maxOccursValidation(std::string elementName, std::string value);

    /**
     * Validates if a given std::string is a non negative {@link int}. Throws an exception if the {@link std::string} isn't a non
     * negative {@link int}.
     * @param elementName The element name containing the field with the {@link int} value.
     * @param attributeName The name of the attribute with the {@link int}.
     * @param value The value to be parsed to a {@link int} object.
     * @return The parsed {@link int} value.
     */
    static int validateNonNegativeInteger(std::string elementName, std::string attributeName, std::string value);

    /**
     * Validates if a given std::string is a non negative {@link int}. Throws an exception if the {@link std::string} isn't a
     * non negative {@link int}.
     * @param elementName The element name containing the field with the {@link int} value.
     * @param attributeName The name of the attribute with the {@link int}.
     * @param value The value to be parsed to a {@link int} object.
     * @return The parsed {@link int} value.
     */
  static int validateRequiredNonNegativeInteger(std::string elementName, std::string attributeName, std::optional<std::string> value)
  {
    if(!value)
      throw new ParsingException(attributeMissingMessage(elementName, attributeName));
    return validateNonNegativeInteger(elementName, attributeName, value.value());
  }

private:
    /**
     * Validates if a given std::string is a positive {@link int}. Throws an exception if the {@link std::string} isn't a
     * positive {@link int}.
     * @param elementName The element name containing the field with the {@link int} value.
     * @param attributeName The name of the attribute with the {@link int} type.
     * @param value The value to be parsed to a {@link int} object.
     * @return The parsed {@link int} value.
     */
  static int validatePositiveInteger(std::string elementName, std::string attributeName, std::string value);
public:
    /**
     * Validates if a given std::string is a positive {@link int}. Throws an exception if the {@link std::string} isn't a
     * positive {@link int}.
     * @param elementName The element name containing the field with the {@link int} value.
     * @param attributeName The name of the attribute with the {@link int} type.
     * @param value The value to be parsed to a {@link int} object.
     * @return The parsed {@link int} value.
     */
  static int validateRequiredPositiveInteger(std::string elementName, std::string attributeName, std::string value)
  {
    if (value.empty())
      throw new ParsingException(attributeMissingMessage(elementName, attributeName));

        return validatePositiveInteger(elementName, attributeName, value);
    }

  static bool validateBoolean(std::string value)
  {
    std::transform(std::begin(value), std::end(value), std::begin(value), ::tolower);
    return value == "true";
  }

  private:
    /**
     * Validates if a given {@link std::string} is a {@link double}. Throws an exception if the {@link std::string} isn't a
     * {@link double}.
     * @param elementName The element name containing the field with the {@link double} value.
     * @param attributeName The name of the attribute with the type {@link double}.
     * @param value The value to be parsed to a {@link double} object.
     * @return The parsed {@link double} value.
     */
  static double validateDouble(std::string elementName, std::string attributeName, std::string value);
public:
    /**
     * Validates if a given {@link std::string} is a {@link double}. Throws an exception if the {@link std::string} isn't a {@link double}.
     * @param elementName The element name containing the field with the {@link double} value.
     * @param attributeName The name of the attribute with the type {@link double}.
     * @param value The value to be parsed to a {@link double} object.
     * @return The parsed {@link double} value.
     */
  static double validateRequiredDouble(std::string elementName, std::string attributeName, std::string value)
  {
    if (value.empty())
      throw new ParsingException(attributeMissingMessage(elementName, attributeName));
    return validateDouble(elementName, attributeName, value);
  }

    /**
     * Obtains the default value of the {@link XsdSchema#attributeFormDefault} attribute by iterating in the  element tree
     * by going from {@link XsdAbstractElement#parent} to {@link XsdAbstractElement#parent} until reaching the top level
     * element.
     * @param parent The parent of the element requesting the default form value.
     * @return The default value for the form attribute.
     */
    static std::string getFormDefaultValue(std::shared_ptr<XsdAbstractElement> parent);
    /**
     * Obtains the default value of the {@link XsdSchema#finalDefault} attribute by iterating in the element tree by
     * going from {@link XsdAbstractElement#parent} to {@link XsdAbstractElement#parent} until reaching the top level
     * element.
     * @param parent The parent of the element requesting the default final value.
     * @return The default value for the final attribute.
     */
    static std::string getFinalDefaultValue(std::shared_ptr<XsdAbstractElement> parent);

    /**
     * Obtains the default value of the {@link XsdSchema#blockDefault} attribute by iterating in the element tree by
     * going from {@link XsdAbstractElement#parent} to {@link XsdAbstractElement#parent} until reaching the top level
     * element.
     * @param parent The parent of the element requesting the default block value.
     * @return The default value for the block attribute.
     */
    static std::string getBlockDefaultValue(std::shared_ptr<XsdAbstractElement> parent);

private:
    static std::string attributeMissingMessage(std::string elementName, std::string attributeName){
        return "The " + elementName + " " + attributeName + " is required to have a value attribute.";
    }
};
