#pragma once

#include "ReferenceBase.h"

#include <string>

class XsdNamedElements;

/**
 * UnsolvedReference is a wrapper class for all objects which should be resolved in the parsing process, if possible.
 */
class UnsolvedReference : public ReferenceBase
{
private:
  std::string m_ref;
  bool m_isTypeRef;

public:
  UnsolvedReference(std::shared_ptr<XsdNamedElements> element);
  UnsolvedReference(std::string refType, std::shared_ptr<XsdNamedElements> element);

  constexpr std::string getRef(void) const { return m_ref; }

  constexpr bool isTypeRef(void) const { return m_isTypeRef; }

  std::shared_ptr<XsdAbstractElement> getParent(void) const;

  std::shared_ptr<XsdNamedElements> getElement(void);
};
