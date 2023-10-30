#pragma once

#include <xsdelements/elementswrapper/UnsolvedReference.h>

/**
 * Represents an instance of an {@link UnsolvedReference} that the {@link XsdParser} wasn't able to solve. It contains
 * the respective {@link UnsolvedReference} object and a list of elements that contained this {@link UnsolvedReference}
 * object. This allows the user to assert which references are missing and where are they used, which may be useful to
 * correct the problems in the XSD file.
 */
class UnsolvedReferenceItem
{
private:
    /**
     * A {@link UnsolvedReference} object that wasn't solved in the parsing process. This happened because its referred
     * element isn't present in the files that were parsed.
     */
    UnsolvedReference* m_unsolvedReference;

    /**
     * A list of parents which indicate all the places where the {@link UnsolvedReference} object was used, which cause
     * every element present in this list to not be fully correct.
     */
    std::list<XsdAbstractElement*> m_parents;
public:
  UnsolvedReferenceItem(UnsolvedReference* unsolvedReference)
    : m_unsolvedReference(unsolvedReference)
  {
    m_parents.push_back(unsolvedReference->getParent());
  }

  virtual ~UnsolvedReferenceItem(void) = default;

  UnsolvedReference* getUnsolvedReference(void)
  {
    return m_unsolvedReference;
  }

  std::list<XsdAbstractElement*> getParents(void)
  {
    return m_parents;
  }

  std::list<XsdAbstractElement*> getParentsExcludingClones(void)
  {
    std::list<XsdAbstractElement*> rval;
    for(auto& parent : m_parents)
      if(parent->getCloneOf() == nullptr)
        rval.push_back(parent);
    rval.unique();
    return rval;
  }

  std::list<XsdAbstractElement*> getParentsWithClones(void)
  {
    std::list<XsdAbstractElement*> rval;
    for(auto& parent : m_parents)
      if(parent->getCloneOf())
        rval.push_back(parent);
    rval.unique();
    return rval;
  }
};
