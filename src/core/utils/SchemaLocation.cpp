#include "SchemaLocation.h"

#include <algorithm>

/**
 * @return true if any string from either set matches.
 * Will merge in unknown alises if there is a match
 */
bool SchemaLocation::operator ==(const SchemaLocation& other)
{
  if(std::any_of(std::begin(other),
                     std::end(other),
                     [this](const std::string& entry){ return contains(entry); } ))
  {
    merge(static_cast<std::set<std::string>>(other));
    return true;
  }
  return false;
}
