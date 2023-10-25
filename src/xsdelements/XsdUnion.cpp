#include "XsdUnion.h"

#include <ranges>

/**
 * Performs a copy of the current object for replacing purposes. The cloned objects are used to replace
 * {@link UnsolvedReference} objects in the reference solving process.
 * @param placeHolderAttributes The additional attributes to add to the clone.
 * @return A copy of the object from which is called upon.
 */
std::shared_ptr<XsdAbstractElement> XsdUnion::clone(StringMap placeHolderAttributes)
{
    placeHolderAttributes.merge(getAttributesMap());

    auto elementCopy = create<XsdUnion>(getParser(),
                                        placeHolderAttributes,
                                        m_visitorFunction,
                                        nullptr);

    if (m_simpleTypeList.empty())
    {
      for(auto& simpleType : m_simpleTypeList)
        elementCopy->m_simpleTypeList.push_back(
            std::static_pointer_cast<XsdSimpleType>(
                simpleType->XsdAbstractElement::clone(simpleType->getAttributesMap(), elementCopy)));
    }

    return elementCopy;
}

std::list<std::string> XsdUnion::getMemberTypesList(void)
{
  std::list<std::string> rval; // TODO
  for(auto val : std::ranges::views::split(m_memberTypes, " "))
    rval.push_back(val.data());
  rval.unique();
  rval.remove_if([](const std::string& val){ return val.empty(); });
  return rval;
}
