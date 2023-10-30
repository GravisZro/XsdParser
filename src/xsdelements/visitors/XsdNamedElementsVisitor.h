#ifndef XSDNAMEDELEMENTSVISITOR_H
#define XSDNAMEDELEMENTSVISITOR_H

#include <xsdelements/elementswrapper/ReferenceBase.h>
#include <xsdelements/elementswrapper/UnsolvedReference.h>
#include <xsdelements/XsdNamedElements.h>
#include <xsdelements/visitors/XsdAnnotatedElementsVisitor.h>
#include <core/XsdParserCore.h>


struct XsdNamedElementsVisitor : XsdAnnotatedElementsVisitor
{
  virtual void visit(XsdAbstractElement* element) override
  {
    if (dynamic_cast<XsdNamedElements*>(element) != nullptr)
    {
      ReferenceBase* referenceBase = ReferenceBase::createFromXsd(element);
      if (dynamic_cast<UnsolvedReference*>(referenceBase) != nullptr)
        getParser()->addUnsolvedReference(static_cast<UnsolvedReference*>(referenceBase));
    }
    static_cast<XsdAnnotatedElements*>(getOwner())->setAnnotation(
          static_cast<XsdAnnotation*>(element));
  }
};


#endif // XSDNAMEDELEMENTSVISITOR_H
