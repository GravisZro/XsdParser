#include <xsdelements/XsdMultipleElements.h>
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
    assert(child);
    auto child_node = node.append_child(child->getElementName().c_str());
    assign_attributes(child_node, child->getAttributesMap());
    std::list<std::shared_ptr<XsdAbstractElement>> child_list;
    if(auto x = std::dynamic_pointer_cast<XsdMultipleElements>(child); x)
      child_list = x->getXsdElements();
    else
      child_list = child->getXsdElements();
    parse_children(child_node, child_list);
  }
}


int main(void)
{
  //std::filesystem::current_path("/home/gravis/project/XsdParser");

  //std::filesystem::path location = "../../human/resources/../issues.xsd";
  //std::cout << std::filesystem::relative(std::filesystem::weakly_canonical(location), "/home/gravis/project/XsdParser") << std::endl;
/*
  SchemaLocation location;
  location.setParentPaths({"/home/gravis/project/XsdParser/"});
  location.insert("test/resources/issues.xsd");


  for(const std::string& filePath : location.data())
    std::cout << filePath << std::endl;

  return 0;
*/
  pugi::xml_document output;
  auto core = create<XsdParser>();

  core->parse("/home/gravis/project/XsdParser/test/resources/issues.xsd");
  //core->parse("/home/gravis/project/exicodegen/schema/V2G_CI_MsgDef.xsd");

  parse_children(output, core->getResultXsdElements());

  output.print(std::cout);
  return 0;
}
