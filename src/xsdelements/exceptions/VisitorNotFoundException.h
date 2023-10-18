#pragma once
#include <stdexcept>
#include <string>

/**
 * Exception that is thrown every time that an {@link XsdAbstractElement#accept} method is accessed when the concrete
 * element shouldn't receive visits.
 */
class VisitorNotFoundException : public std::runtime_error
{
public:
  VisitorNotFoundException(std::string message)
    : std::runtime_error(message) { }
};
