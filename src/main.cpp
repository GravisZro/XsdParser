#include <core/XsdParser.h>
#include <pugixml.hpp>
#include <iostream>

void assign_attributes(pugi::xml_node target, const StringMap& attributes)
{
  for(auto& attribute : attributes)
    target.append_attribute(attribute.first.c_str()).set_value(attribute.second.c_str());
}

void parse_children(pugi::xml_node node, const std::list<std::shared_ptr<XsdAbstractElement>>& children)
{
  for(auto& child : children)
  {
    auto child_node = node.append_child(child->getElementName().c_str());
    assign_attributes(child_node, child->getAttributesMap());
    parse_children(child_node, child->getXsdElements());
  }
}


int main(void)
{
  pugi::xml_document output;
  auto core = create<XsdParser>();

  //core->parse("/home/gravis/project/XsdParser/test/resources/issue_23.xsd");
  core->parse("/home/gravis/project/exicodegen/schema/V2G_CI_MsgDef.xsd");

  parse_children(output, core->getResultXsdElements());

  output.print(std::cout);
  return 0;
}
