#include "XsdAbstractElement.h"

#include <core/XsdParserCore.h>

#include <xsdelements/visitors/XsdAbstractElementVisitor.h>
#include <xsdelements/elementswrapper/ReferenceBase.h>
#include <xsdelements/elementswrapper/ConcreteElement.h>
#include <xsdelements/elementswrapper/NamedConcreteElement.h>
#include <xsdelements/elementswrapper/UnsolvedReference.h>

#include <xsdelements/XsdSchema.h>

#include <algorithm>

/**
 * Base method for all accept methods. It serves as a way to guarantee that every accept call assigns the parent
 * field.
 * @param xsdAbstractElementVisitor The visitor that is visiting the current instance.
 */
void XsdAbstractElement::accept(XsdAbstractElementVisitor* xsdAbstractElementVisitor)
{
  assert(xsdAbstractElementVisitor);
  setParent(xsdAbstractElementVisitor->getOwner());
}

/**
 * The base code for parsing any {@link XsdAbstractElement}. All the concrete implementations of this class should
 * call this method in order to parse its children.
 * @param node The node from where the element will be parsed.
 * @param element The concrete element that will be populated and returned.
 * @return A wrapper object that contains the parsed XSD object.
 */
ReferenceBase* XsdAbstractElement::xsdParseSkeleton(pugi::xml_node node,
                                                    XsdAbstractElement* element)
{
  auto parse_mappers = XsdParserCore::getParseMappers();

  for(pugi::xml_node child = node.first_child(); child; child = child.next_sibling())
  {
    if (child.type() == pugi::node_element)
    {
      std::string nodeName = child.name();
      if(parse_mappers.contains(nodeName))
        if(auto configEntryData = parse_mappers.at(nodeName); configEntryData.parserFunction)
        {
          auto rval = configEntryData.parserFunction(child, configEntryData.visitorFunction, nullptr);
          auto childElement = rval->getElement();
          childElement->setElementName(nodeName);
          if(element->getVisitor())
            childElement->accept(element->getVisitor());
          childElement->validateSchemaRules();
        }
    }
  }

  auto wrappedElement = ReferenceBase::createFromXsd(element);
  getParser()->addParsedElement(wrappedElement);
  return wrappedElement;
}

/**
 * This method iterates on the current element children and replaces any {@link UnsolvedReference} object that has a
 * ref attribute that matches the receiving {@link NamedConcreteElement} name attribute.
 * @param element A fully parsed element with a name that will replace an {@link UnsolvedReference} object, if a
 *                match between the {@link NamedConcreteElement} name attribute and the {@link UnsolvedReference}
 *                ref attribute.
 */
void XsdAbstractElement::replaceUnsolvedElements(NamedConcreteElement* elementWrapper)
{
  std::list<ReferenceBase*> element_list = getElements();
  std::list<UnsolvedReference*> unsolved_refs;
  for(auto element : element_list)
    if(auto unsolved = dynamic_cast<UnsolvedReference*>(element);
       unsolved && compareReference(elementWrapper, unsolved))
      unsolved_refs.push_back(unsolved);

  if(!unsolved_refs.empty())
  {
    auto oldElement = unsolved_refs.front();
    auto iter = std::find(std::begin(element_list),
                          std::end(element_list),
                          static_cast<ReferenceBase*>(oldElement));
    assert(iter != std::end(element_list));
    **iter = *new ReferenceBase(static_cast<ReferenceBase*>(elementWrapper), oldElement->getParent());
  }
}


bool XsdAbstractElement::compareReference(NamedConcreteElement* element, UnsolvedReference* reference)
{
  return compareReference(element, reference->getRef());
}

bool XsdAbstractElement::compareReference(NamedConcreteElement* element, std::optional<std::string> unsolvedRef)
{
  if (unsolvedRef && unsolvedRef->contains(':'))
    unsolvedRef = unsolvedRef->substr(unsolvedRef->find_first_of(':') + 1);
  return unsolvedRef && element->getName() == unsolvedRef.value();
}

/**
 * @return All the {@link ConcreteElement} objects present in the concrete implementation of the
 * {@link XsdAbstractElement} class. It doesn't return the {@link UnsolvedReference} objects.
 */
std::list<XsdAbstractElement*> XsdAbstractElement::getXsdElements(void) const
{
  std::list<XsdAbstractElement*> xsd_elements;
  for(const auto& element : getElements())
    if(dynamic_cast<ConcreteElement*>(element) != nullptr)
      xsd_elements.push_back(element->getElement());
  return xsd_elements;
}

XsdSchema* XsdAbstractElement::getXsdSchema(void)
{
  XsdSchema* schema;
  try { schema = getXsdSchema(this, {}); }
  catch (...) { return nullptr; }

  if(schema == nullptr)
    throw ParsingException("The parent is null while searching for the XsdSchema. Please submit an issue with the xsd file being parsed to the project page.");
  return schema;
}

XsdSchema* XsdAbstractElement::getXsdSchema(XsdAbstractElement* element,
                                            std::list<XsdAbstractElement*> hierarchy)
{
  if (element == nullptr)
    return nullptr;

  for(auto& x : hierarchy)
    if(x == element)
      throw ParsingException("There is a circular reference in the Xsd Element tree. Please submit an issue with the xsd file being parsed to the project page.");

  if (auto schema = dynamic_cast<XsdSchema*>(element); schema != nullptr)
    return schema;

  hierarchy.push_back(element);
  return getXsdSchema(element->getParent(true), hierarchy);
}
