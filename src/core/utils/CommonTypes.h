#ifndef COMMONTYPES_H
#define COMMONTYPES_H

#include <string>
#include <map>
#include <list>
#include <functional>
#include <memory>
#include <optional>

#include "SchemaLocation.h"

class XsdAbstractElementVisitor;
class XsdAbstractElement;

using StringMap = std::map<std::string, std::string>;
using VisitorFunctionReference = std::function<std::shared_ptr<XsdAbstractElementVisitor>(std::shared_ptr<XsdAbstractElement>)>;

#endif // COMMONTYPES_H
