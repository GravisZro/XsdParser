#include <xsdelements/XsdMultipleElements.h>
#include <xsdelements/XsdComplexType.h>
#include <xsdelements/XsdExtension.h>
#include <xsdelements/XsdGroup.h>

#include <core/XsdParser.h>
#include <pugixml.hpp>
#include <iostream>
#include <filesystem>

#include <core/utils/SchemaLocation.h>

void assign_attributes(pugi::xml_node target, const StringMap& attributes)
{
  for(auto& attribute : attributes)
    target.append_attribute(attribute.first.c_str()).set_value(attribute.second.c_str());
}

void parse_children(pugi::xml_node node, const std::list<std::shared_ptr<XsdAbstractElement>>& children)
{
  for(auto& child : children)
  {
    if(!child)
      continue;
    //assert(child);
    auto child_node = node.append_child(child->getElementName().c_str());
    assign_attributes(child_node, child->getAttributesMap());
    std::list<std::shared_ptr<XsdAbstractElement>> child_list;
    if(auto x = std::dynamic_pointer_cast<XsdMultipleElements>(child); x)
      child_list = x->getXsdElements();
    else
      child_list = child->getXsdElements();
    if(child_list.empty())
    {
      if(auto x = std::dynamic_pointer_cast<XsdComplexType>(child); x)
        child_list.push_back(x->getXsdChildElement());
      else if(auto x = std::dynamic_pointer_cast<XsdExtension>(child); x)
        child_list.push_back(x->getChildAs<XsdAbstractElement>());
      else if(auto x = std::dynamic_pointer_cast<XsdGroup>(child); x)
        child_list.push_back(x->getChildElement());
    }

    parse_children(child_node, child_list);
  }
}

int main(void)
{
  pugi::xml_document output;
  auto core = create<XsdParser>();

  //core->parse("/home/gravis/project/XsdParser/test/resources/issues.xsd");
  core->parse("/home/gravis/project/exicodegen/schema/V2G_CI_MsgDef.xsd");

  parse_children(output, core->getResultXsdElements());

  output.print(std::cout);
  return 0;
}
