#include <core/XsdParser.h>

int main(void)
{
  auto core = create<XsdParser>();
  assert(core->shared_from_this());

  core->parse("/home/gravis/project/XsdParser/test/resources/issue_23.xsd");
  //core->parse("/home/gravis/project/exicodegen/schema/V2G_CI_MsgDef.xsd");

  return 0;
}
