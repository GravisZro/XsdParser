#pragma once

#include <xsdelements/XsdAbstractElement.h>

/**
 * This Visitor interface serves as a base to every {@link XsdAbstractElement} class visitors. It is meant to implement
 * the restrictions between elements of the XSD language.
 */
struct XsdAbstractElementVisitor
{
  virtual ~XsdAbstractElementVisitor(void) = default;
  virtual void initialize(void) { }

  virtual void visit(std::shared_ptr<XsdAbstractElement> element) = 0;
  virtual std::shared_ptr<XsdAbstractElement> getOwner(void) = 0;
};
