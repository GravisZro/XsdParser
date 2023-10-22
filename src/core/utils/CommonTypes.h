#ifndef COMMONTYPES_H
#define COMMONTYPES_H

#include <pugixml.hpp>
#include <string>
#include <map>
#include <list>

#include <memory>
#include <optional>

#include "NonDeletedPtr.h"

struct XsdAbstractElementVisitor;
class XsdAbstractElement;
class ReferenceBase;
class XsdParserCore;

using StringMap = std::map<std::string, std::string>;

using VisitorFunctionType = std::shared_ptr<XsdAbstractElementVisitor> (*) (std::shared_ptr<XsdAbstractElement>);
using ParserFunctionType = std::shared_ptr<ReferenceBase> (*)(std::shared_ptr<XsdParserCore>,
                                                              pugi::xml_node,
                                                              VisitorFunctionType,
                                                              std::shared_ptr<XsdAbstractElement>);


#endif // COMMONTYPES_H
