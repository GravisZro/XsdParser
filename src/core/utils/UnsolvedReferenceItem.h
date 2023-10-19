#pragma once

//#include <xsdelements/XsdAbstractElement.h>
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
    std::shared_ptr<UnsolvedReference> m_unsolvedReference;

    /**
     * A list of parents which indicate all the places where the {@link UnsolvedReference} object was used, which cause
     * every element present in this list to not be fully correct.
     */
    std::list<std::shared_ptr<XsdAbstractElement>> m_parents;
public:
  UnsolvedReferenceItem(std::shared_ptr<UnsolvedReference> unsolvedReference)
    : m_unsolvedReference(unsolvedReference)
  {
    m_parents.push_back(unsolvedReference->getParent());
  }

  std::shared_ptr<UnsolvedReference> getUnsolvedReference(void)
  {
    return m_unsolvedReference;
  }

  std::list<std::shared_ptr<XsdAbstractElement>> getParents(void)
  {
    return m_parents;
  }

  std::list<std::shared_ptr<XsdAbstractElement>> getParentsExcludingClones(void)
  {
    std::list<std::shared_ptr<XsdAbstractElement>> rval;
    for(auto& parent : m_parents)
      if(parent->getCloneOf() == nullptr)
        rval.push_back(parent);
    rval.unique();
    return rval;
  }

  std::list<std::shared_ptr<XsdAbstractElement>> getParentsWithClones(void)
  {
    std::list<std::shared_ptr<XsdAbstractElement>> rval;
    for(auto& parent : m_parents)
      if(parent->getCloneOf())
        rval.push_back(parent);
    rval.unique();
    return rval;
  }
};
