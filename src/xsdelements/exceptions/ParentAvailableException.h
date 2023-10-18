#pragma once
#include <stdexcept>
#include <string>

class ParentAvailableException : public std::runtime_error
{
public:
  ParentAvailableException(std::string message)
    : std::runtime_error(message) { }
};
