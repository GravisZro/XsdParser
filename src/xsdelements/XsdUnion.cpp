#include "XsdUnion.h"

/**
 * Performs a copy of the current object for replacing purposes. The cloned objects are used to replace
 * {@link UnsolvedReference} objects in the reference solving process.
 * @param placeHolderAttributes The additional attributes to add to the clone.
 * @return A copy of the object from which is called upon.
 */
XsdUnion::XsdUnion(const XsdUnion& other, XsdAbstractElement* parent)
    : XsdUnion(other.getAttributesMap(), other.m_visitorFunction, parent)
{
  if (other.m_simpleTypeList.empty())
  {
    for(auto& simpleType : m_simpleTypeList)
      m_simpleTypeList.push_back(new XsdSimpleType(*simpleType, this));
  }
}

std::list<std::string> XsdUnion::getMemberTypesList(void)
{
  std::list<std::string> rval;
  std::size_t new_pos = 0, pos = 0;
  do
  {
    new_pos = m_memberTypes.find(' ', pos);
    std::string str = m_memberTypes.substr(pos, new_pos - pos);
    if(!str.empty())
      rval.push_back(str);
  } while(pos = new_pos + 1, pos);
  return rval;
}
