#ifndef XSDNAMEDELEMENTSVISITOR_H
#define XSDNAMEDELEMENTSVISITOR_H

#include "XsdAnnotatedElementsVisitor.h"

struct XsdNamedElementsVisitor : XsdAnnotatedElementsVisitor
{
  virtual void visit(std::shared_ptr<XsdAbstractElement> element) override;
};


#endif // XSDNAMEDELEMENTSVISITOR_H
