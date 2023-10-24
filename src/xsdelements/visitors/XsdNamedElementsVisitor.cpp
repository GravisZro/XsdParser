#include "XsdNamedElementsVisitor.h"

#include <xsdelements/elementswrapper/ReferenceBase.h>
#include <xsdelements/elementswrapper/UnsolvedReference.h>
#include <xsdelements/XsdNamedElements.h>
#include <core/XsdParserCore.h>

void XsdNamedElementsVisitor::visit(std::shared_ptr<XsdAbstractElement> element)
{
  if (std::dynamic_pointer_cast<XsdNamedElements>(element))
  {
    std::shared_ptr<ReferenceBase> referenceBase = ReferenceBase::createFromXsd(element);
    if (std::dynamic_pointer_cast<UnsolvedReference>(referenceBase))
      element->getParser()->addUnsolvedReference(std::static_pointer_cast<UnsolvedReference>(referenceBase));
  }
  std::static_pointer_cast<XsdAnnotatedElements>(getOwner())->setAnnotation(
        std::static_pointer_cast<XsdAnnotation>(element));
}
