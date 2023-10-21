#pragma once

#include <xsdelements/XsdAbstractElement.h>

class XsdNamedElements;
class XsdAll;
class XsdMultipleElements;
class XsdAttribute;
class XsdAttributeGroup;
class XsdChoice;
class XsdComplexType;
class XsdGroup;
class XsdSequence;
class XsdElement;
class XsdSimpleType;
class XsdRestriction;
class XsdList;
class XsdUnion;
class XsdEnumeration;
class XsdFractionDigits;
class XsdLength;
class XsdMaxExclusive;
class XsdMaxInclusive;
class XsdMaxLength;
class XsdMinExclusive;
class XsdMinInclusive;
class XsdMinLength;
class XsdPattern;
class XsdTotalDigits;
class XsdWhiteSpace;
class XsdExtension;
class XsdComplexContent;
class XsdSimpleContent;
class XsdDocumentation;
class XsdAppInfo;
class XsdAnnotation;
class XsdImport;
class XsdInclude;

/**
 * This Visitor interface serves as a base to every {@link XsdAbstractElement} class visitors. It is meant to implement
 * the restrictions between elements of the XSD language.
 */
class XsdAbstractElementVisitor
{
public:
  virtual ~XsdAbstractElementVisitor(void) = default;
  virtual void initialize(void) { }

  virtual void visit(std::shared_ptr<XsdAll> element);

  virtual void visit(std::shared_ptr<XsdAttribute> element);

  virtual void visit(std::shared_ptr<XsdAttributeGroup> element);

  virtual void visit(std::shared_ptr<XsdChoice> element);

  virtual void visit(std::shared_ptr<XsdComplexType> element);

  virtual void visit(std::shared_ptr<XsdElement> element);

  virtual void visit(std::shared_ptr<XsdGroup> element);

  virtual void visit(std::shared_ptr<XsdSequence> element);

  virtual void visit(std::shared_ptr<XsdNamedElements> element);

  virtual void visit(std::shared_ptr<XsdMultipleElements> element);

  virtual void visit(std::shared_ptr<XsdSimpleType> element);

  virtual void visit(std::shared_ptr<XsdRestriction> element);

  virtual void visit(std::shared_ptr<XsdList> element);

  virtual void visit(std::shared_ptr<XsdUnion> element);

  virtual void visit(std::shared_ptr<XsdEnumeration> element);

  virtual void visit(std::shared_ptr<XsdFractionDigits> element);

  virtual void visit(std::shared_ptr<XsdLength> element);

  virtual void visit(std::shared_ptr<XsdMaxExclusive> element);

  virtual void visit(std::shared_ptr<XsdMaxInclusive> element);

  virtual void visit(std::shared_ptr<XsdMaxLength> element);

  virtual void visit(std::shared_ptr<XsdMinExclusive> element);

  virtual void visit(std::shared_ptr<XsdMinInclusive> element);

  virtual void visit(std::shared_ptr<XsdMinLength> element);

  virtual void visit(std::shared_ptr<XsdPattern> element);

  virtual void visit(std::shared_ptr<XsdTotalDigits> element);

  virtual void visit(std::shared_ptr<XsdWhiteSpace> element);

  virtual void visit(std::shared_ptr<XsdExtension> element);

  virtual void visit(std::shared_ptr<XsdComplexContent> element);

  virtual void visit(std::shared_ptr<XsdSimpleContent> element);

  virtual void visit(std::shared_ptr<XsdDocumentation> element);

  virtual void visit(std::shared_ptr<XsdAppInfo> element);

  virtual void visit(std::shared_ptr<XsdAnnotation> element);

  virtual void visit(std::shared_ptr<XsdImport> element);

  virtual void visit(std::shared_ptr<XsdInclude> element);

  std::shared_ptr<XsdAbstractElement> getOwner(void) { return nullptr; }
};
