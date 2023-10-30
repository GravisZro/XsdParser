#ifndef COMMONTYPES_H
#define COMMONTYPES_H

#include <pugixml.hpp>
#include <string>
#include <string_view>
#include <map>
#include <list>

#include <memory>
#include <optional>

#include "TagLookup.h"

//#include "NonDeletedPtr.h"

struct XsdAbstractElementVisitor;
class XsdAbstractElement;
class ReferenceBase;

using StringMap = std::map<std::string, std::string>;

using VisitorFunctionType = XsdAbstractElementVisitor* (*) (XsdAbstractElement*);
using ParserFunctionType = ReferenceBase* (*)(pugi::xml_node,
                                                              VisitorFunctionType,
                                                              XsdAbstractElement*);

using namespace std::string_literals;
using namespace std::string_view_literals;

#endif // COMMONTYPES_H
