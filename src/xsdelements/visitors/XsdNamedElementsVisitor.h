#ifndef XSDNAMEDELEMENTSVISITOR_H
#define XSDNAMEDELEMENTSVISITOR_H

#include <xsdelements/elementswrapper/ReferenceBase.h>
#include <xsdelements/elementswrapper/UnsolvedReference.h>
#include <xsdelements/XsdNamedElements.h>
#include <xsdelements/visitors/XsdAnnotatedElementsVisitor.h>
#include <core/XsdParserCore.h>


struct XsdNamedElementsVisitor : XsdAnnotatedElementsVisitor
{
  virtual void visit(std::shared_ptr<XsdAbstractElement> element) override
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
};


#endif // XSDNAMEDELEMENTSVISITOR_H
