#pragma once

#include <core/utils/CommonTypes.h>
#include <pugixml.hpp>

#include <core/utils/ConfigEntryData.h>
#include <xsdelements/exceptions/ParentAvailableException.h>
#include <xsdelements/exceptions/ParsingException.h>

#include <cassert>

struct XsdAbstractElementVisitor;
class XsdSchema;
class NamedConcreteElement;
class UnsolvedReference;
class ReferenceBase;

/**
 * This class serves as a base to every element class, i.e. {@link XsdElement}, {@link XsdAttribute}, etc.
 */
class XsdAbstractElement
{
public:
  constexpr static const std::string_view VALUE_TAG = "value";
  constexpr static const std::string_view ATTRIBUTE_FORM_DEFAULT = "attribtueFormDefault";
  constexpr static const std::string_view ELEMENT_FORM_DEFAULT = "elementFormDefault";
  constexpr static const std::string_view BLOCK_DEFAULT = "blockDefault";
  constexpr static const std::string_view FINAL_DEFAULT = "finalDefault";
  constexpr static const std::string_view TARGET_NAMESPACE = "targetNamespace";
  constexpr static const std::string_view VERSION = "version";
  constexpr static const std::string_view XMLNS = "xmlns";

  constexpr static const std::string_view ID_TAG = "id";
  constexpr static const std::string_view NAME_TAG = "name";
  constexpr static const std::string_view ABSTRACT_TAG = "abstract";
  constexpr static const std::string_view DEFAULT_ELEMENT_TAG = "defaultElement";
  constexpr static const std::string_view FIXED_TAG = "fixed";
  constexpr static const std::string_view TYPE_TAG = "type";
  constexpr static const std::string_view MIXED_TAG = "mixed";
  constexpr static const std::string_view BLOCK_TAG = "block";
  constexpr static const std::string_view FINAL_TAG = "final";
  constexpr static const std::string_view USE_TAG = "use";
  constexpr static const std::string_view SUBSTITUTION_GROUP_TAG = "substitutionGroup";
  constexpr static const std::string_view DEFAULT_TAG = "default";
  constexpr static const std::string_view FORM_TAG = "form";
  constexpr static const std::string_view NILLABLE_TAG = "nillable";
  constexpr static const std::string_view MIN_OCCURS_TAG = "minOccurs";
  constexpr static const std::string_view MAX_OCCURS_TAG = "maxOccurs";
  constexpr static const std::string_view ITEM_TYPE_TAG = "itemType";
  constexpr static const std::string_view BASE_TAG = "base";
  constexpr static const std::string_view SOURCE_TAG = "source";
  constexpr static const std::string_view XML_LANG_TAG = "xml:lang";
  constexpr static const std::string_view MEMBER_TYPES_TAG = "memberTypes";
  constexpr static const std::string_view SCHEMA_LOCATION = "schemaLocation";
  constexpr static const std::string_view NAMESPACE = "namespace";
  constexpr static const std::string_view REF_TAG = "ref";

public: // ctors
  XsdAbstractElement(StringMap attributesMap,
                     VisitorFunctionType visitorFunction,
                     XsdAbstractElement* parent)
    : m_visitorFunction(visitorFunction),
      m_attributesMap(attributesMap),
      m_parent(parent),
      m_visitor(nullptr),
      m_cloneOf(nullptr),
      m_parentAvailable(false)
  {
    m_parentAvailable = bool(m_parent);
    if(m_visitorFunction)
      m_visitor = m_visitorFunction(this);
  }

  /**
   * Performs a copy of the current object for replacing purposes. The cloned objects are used to replace
   * {@link UnsolvedReference} objects in the reference solving process.
   * @param placeHolderAttributes The additional attributes to add to the clone.
   * @return A copy of the object from which is called upon.
   */
  XsdAbstractElement(const XsdAbstractElement& other)
    : XsdAbstractElement(other.getAttributesMap(), other.m_visitorFunction, nullptr)
  {
    setCloneOf(&other);
  }

public:
  virtual ~XsdAbstractElement(void) = default;

  bool removeAttribute(const std::string_view& attribute)
  {
    if(hasAttribute(attribute))
      return m_attributesMap.erase(std::string(attribute));
    return false;
  }

  bool hasAttribute(const std::string_view& attribute) const
  {
    return m_attributesMap.contains(std::string(attribute));
  }

  std::string getAttribute(const std::string_view& attribute) const
  {
    return m_attributesMap.at(std::string(attribute));
  }

  StringMap getAttributesMap(void) const
  {
    return m_attributesMap;
  }


  void setElementName(const std::string& name)
  {
    m_element_name = name;
  }

  const std::string& getElementName(void) const
  {
    return m_element_name;
  }

  /**
     * Obtains the visitor of a concrete {@link XsdAbstractElement} instance.
     * @return The concrete visitor instance.
     */
  virtual XsdAbstractElementVisitor* getVisitor(void) const
  {
    return m_visitor;
  }

  /**
     * Runs verifications on each concrete element to ensure that the XSD schema rules are verified.
     */
  virtual void validateSchemaRules(void) const { }

  /**
     * Base method for all accept methods. It serves as a way to guarantee that every accept call assigns the parent
     * field.
     * @param xsdAbstractElementVisitor The visitor that is visiting the current instance.
     */
  virtual void accept(XsdAbstractElementVisitor* xsdAbstractElementVisitor);

  virtual std::list<ReferenceBase*> getElements(void) const { return {}; }

  /**
     * Performs a copy of the current object for replacing purposes. The cloned objects are used to replace
     * {@link UnsolvedReference} objects in the reference solving process.
     * @param placeHolderAttributes The additional attributes to add to the clone.
     * @return A copy of the object from which is called upon.
     */
//  template<typename T>
//  T* clone(StringMap placeHolderAttributes,
//                           XsdAbstractElement* parent)
//  {
//    XsdAbstractElement* c = clone<T>(placeHolderAttributes);
//    c->setParent(parent);
//    return c;
//  }

  /**
     * @return All the {@link ConcreteElement} objects present in the concrete implementation of the
     * {@link XsdAbstractElement} class. It doesn't return the {@link UnsolvedReference} objects.
     */
  virtual std::list<XsdAbstractElement*> getXsdElements(void) const;

  XsdSchema* getXsdSchema(void);

  static XsdSchema* getXsdSchema(XsdAbstractElement* element,
                                                 std::list<XsdAbstractElement*> hierarchy);


  static ReferenceBase* xsdParseSkeleton(pugi::xml_node node, XsdAbstractElement* element);

  /**
     * Converts a {@link DOMNamedNodeMap} to a {@link Map} object. This is meant to simplify the manipulation of the
     * information.
     * @param nodeMap The {@link DOMNamedNodeMap} to convert to a {@link Map} object.
     * @return The {@link Map} object that was generated by the conversion.
     */
  static StringMap getAttributesMap(pugi::xml_node node)
  {
    StringMap attributesMapped;
    for(auto& attr : node.attributes())
      attributesMapped.emplace(std::make_pair(attr.name(), attr.value()));
    return attributesMapped;
  }

public:
  /**
     * This method iterates on the current element children and replaces any {@link UnsolvedReference} object that has a
     * ref attribute that matches the receiving {@link NamedConcreteElement} name attribute.
     * @param element A fully parsed element with a name that will replace an {@link UnsolvedReference} object, if a
     *                match between the {@link NamedConcreteElement} name attribute and the {@link UnsolvedReference}
     *                ref attribute.
     */
  virtual void replaceUnsolvedElements(NamedConcreteElement* elementWrapper);

  static bool compareReference(NamedConcreteElement* element, UnsolvedReference* reference);
  static bool compareReference(NamedConcreteElement* element, std::optional<std::string> unsolvedRef);

  /**
     * @return The parent of the current {@link XsdAbstractElement} object.
     */
  XsdAbstractElement* getParent(void) const
  {
    return getParent(false);
  }

  /**
     * @return The parent of the current {@link XsdAbstractElement} object.
     */
  XsdAbstractElement* getParent(bool enforceParentAvailability) const
  {
    if (!m_parentAvailable)
    {
      if (enforceParentAvailability)
        throw ParentAvailableException("The parent of this element isn't available to avoid circular memory dependencies.");
      else
        return nullptr;
    }
    return m_parent;
  }

  /**
     * @return The source of the clone of the current {@link XsdAbstractElement} object.
     */
  const XsdAbstractElement* getCloneOf(void) const
  {
    return m_cloneOf;
  }

  /**
     * Sets source of the clone of the current {@link XsdAbstractElement} object.
     */
  void setCloneOf(const XsdAbstractElement* cloneOf)
  {
    m_cloneOf = cloneOf;
  }

  void setParent(XsdAbstractElement* parent)
  {
    m_parent = parent;
    m_parentAvailable = bool(m_parent);
  }

  void setParentAvailable(bool parentAvailable)
  {
    m_parentAvailable = parentAvailable;
  }

  /**
     * In special cases such as {@link XsdAppInfo} and {@link XsdDocumentation} the contents are a simple text node,
     * in which case this function is more suited than using the {@link XsdAbstractElement#xsdParseSkeleton} since
     * those types of elements can't have children nodes.
     * @param node The {@link DOMNode} containing either a {@link XsdAppInfo} or {@link XsdDocumentation}.
     * @return The textual value contained in the {@link DOMNode} parameter.
     */
  static std::string xsdRawContentParse([[maybe_unused]] pugi::xml_node node)
  {
#if 0
    StringBuilder stringBuilder = new StringBuilder();

    DOMNodeList children = node.getChildNodes();

    try {
      for (int childIndex = 0; childIndex < children.getLength(); childIndex++) {
        pugi::xml_node child = children.item(childIndex);

        StringWriter writer = new StringWriter();
        TransformerFactory factory = TransformerFactory.newInstance();
        factory.setAttribute(XMLConstants.ACCESS_EXTERNAL_DTD, "");
        factory.setAttribute(XMLConstants.ACCESS_EXTERNAL_STYLESHEET, "");

        Transformer transformer = factory.newTransformer();
        transformer.transform(new DOMSource(child), new StreamResult(writer));
        std::string output = writer.toString().trim();
        output = output.substring(output.indexOf('>') + 1).trim();
        stringBuilder.append(output);
      }
    } catch (Exception e){
      throw ParsingException(e.getMessage());
    }

    return stringBuilder.toString();
#endif
    return node.text().get();
  }

protected:
  VisitorFunctionType m_visitorFunction;

private:
  /**
   * A {@link Map} object containing the keys/values of the attributes that belong to the concrete element instance.
   */
  StringMap m_attributesMap;


  /**
     * The instance which contains the present element.
     */
  XsdAbstractElement* m_parent;

  /**
     * The visitor instance for this element.
     */
  XsdAbstractElementVisitor* m_visitor;

  /**
     * Indicates the source from this object was cloned, if applicable.
     */
  const XsdAbstractElement* m_cloneOf;

  /**
     * Indicates if this element has the Parent available. This was created as a way of indicating that the parent of the
     * current element isn't present to avoid circular memory dependencies.
     */
  bool m_parentAvailable;


  std::string m_element_name;
};
