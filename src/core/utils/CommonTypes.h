#ifndef COMMONTYPES_H
#define COMMONTYPES_H

#include <string>
#include <map>
#include <list>

#include <memory>
#include <optional>

#include "NonDeletedPtr.h"

class XsdAbstractElementVisitor;
class XsdAbstractElement;
class ReferenceBase;
struct ParseData;

using StringMap = std::map<std::string, std::string>;
//using VisitorFunctionType = std::function<std::shared_ptr<XsdAbstractElementVisitor>(std::shared_ptr<XsdAbstractElement>)>;

using ParserFunctionType = std::shared_ptr<ReferenceBase> (*)(const ParseData&);
using VisitorFunctionType = std::shared_ptr<XsdAbstractElementVisitor> (*) (std::shared_ptr<XsdAbstractElement>);

#endif // COMMONTYPES_H
