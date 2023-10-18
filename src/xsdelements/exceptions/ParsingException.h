#pragma once
#include <stdexcept>
#include <string>
/**
 * An exception that is thrown whenever the parsing process encounters a error in the values present in the XSD file.
 * The exception message contains valuable information to find and correct the error in the file.
 */
class ParsingException : public std::runtime_error
{
public:
  ParsingException(std::string message)
    : std::runtime_error(message) { }
};
