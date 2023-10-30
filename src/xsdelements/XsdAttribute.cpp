#include "XsdAttribute.h"

#include "AttributeValidations.h"
#include <core/XsdParserCore.h>
#include <xsdelements/XsdSchema.h>
#include <xsdelements/XsdElement.h>
#include <xsdelements/XsdSimpleType.h>
#include <xsdelements/elementswrapper/UnsolvedReference.h>
#include <xsdelements/elementswrapper/NamedConcreteElement.h>
#include <xsdelements/visitors/XsdAbstractElementVisitor.h>
#include <xsdelements/visitors/XsdSimpleTypeVisitor.h>

XsdAbstractElementVisitor* XsdAttributeVisitorFunction(XsdAbstractElement* element)
{
  return static_cast<XsdAbstractElementVisitor*>(
            new XsdSimpleTypeVisitor(
              static_cast<XsdSimpleType*>(element)));
}

XsdAttribute::XsdAttribute(StringMap attributesMap,
                           VisitorFunctionType visitorFunction,
                           XsdAbstractElement* parent)
  : XsdNamedElements(attributesMap, visitorFunction, parent),
    m_simpleType(nullptr),
    m_form(getFormDefaultValue(parent)),
    m_use(UsageEnum::OPTIONAL)
{
  if(haveAttribute(DEFAULT_ELEMENT_TAG))
    m_defaultElement = getAttribute(DEFAULT_ELEMENT_TAG);

  if(haveAttribute(FIXED_TAG))
    m_fixed = getAttribute(FIXED_TAG);

  if(haveAttribute(TYPE_TAG))
    m_type = getAttribute(TYPE_TAG);

  if(haveAttribute(FORM_TAG))
    m_form = AttributeValidations::belongsToEnum<FormEnum>(getAttribute(FORM_TAG));

  if(haveAttribute(USE_TAG))
    m_use = AttributeValidations::belongsToEnum<UsageEnum>(getAttribute(USE_TAG));

  if (m_type && !XsdParserCore::getXsdTypesToCpp().contains(m_type.value()))
  {
    m_simpleType = new UnsolvedReference(
                     m_type.value(),
                     static_cast<XsdNamedElements*>(
                       new XsdSimpleType(StringMap{},
                                         XsdAttributeVisitorFunction,
                                         nullptr)));
    getParser()->addUnsolvedReference(static_cast<UnsolvedReference*>(m_simpleType));
  }
}


std::optional<std::string> XsdAttribute::getFormDefaultValue(XsdAbstractElement* parent)
{
  if (parent == nullptr)
    return {};

  if(auto x = dynamic_cast<XsdElement*>(parent); x != nullptr)
    return x->getForm();

  if(auto x = dynamic_cast<XsdSchema*>(parent); x != nullptr)
    return x->getAttributeFormDefault();

  return getFormDefaultValue(parent->getParent());
}

void XsdAttribute::accept(XsdAbstractElementVisitor* visitorParam)
{
  XsdNamedElements::accept(visitorParam);
  visitorParam->visit(static_cast<XsdAttribute*>(this));
}

/**
 * Performs a copy of the current object for replacing purposes. The cloned objects are used to replace
 * {@link UnsolvedReference} objects in the reference solving process.
 * @param placeHolderAttributes The additional attributes to add to the clone.
 * @return A copy of the object from which is called upon.
 */

XsdAttribute::XsdAttribute(const XsdAttribute& other)
  : XsdAttribute(other.getAttributesMap(), other.m_visitorFunction, nullptr)
{
  removeAttribute(TYPE_TAG);
  removeAttribute(REF_TAG);

  m_simpleType = new ReferenceBase(other.m_simpleType, this);
  m_type = other.m_type;
  setCloneOf(&other);
}

/**
 * Receives a {@link NamedConcreteElement} that should be the one requested earlier.
 *  * In the {@link XsdAttribute} constructor:
 *      m_simpleType = new UnsolvedReference(type, placeHolder);
 *      XsdParser.getInstance().addUnsolvedReference((UnsolvedReference) m_simpleType);
 * This implies that the object being received is the object that is being referred with the {@link XsdAttribute#type}
 * std::string.
 * @param elementWrapper The object that should be wrapping the requested {@link XsdSimpleType} object.
 */
void XsdAttribute::replaceUnsolvedElements(NamedConcreteElement* elementWrapper)
{
  XsdNamedElements::replaceUnsolvedElements(elementWrapper);
  if (dynamic_cast<XsdSimpleType*>(elementWrapper->getElement()) != nullptr &&
      m_simpleType != nullptr &&
      compareReference(elementWrapper, m_type))
    m_simpleType = elementWrapper;
}

XsdSimpleType* XsdAttribute::getXsdSimpleType(void) const
{
  if (dynamic_cast<ConcreteElement*>(m_simpleType) != nullptr)
    return dynamic_cast<XsdSimpleType*>(m_simpleType->getElement());
  return nullptr;
}

std::list<XsdRestriction*> XsdAttribute::getAllRestrictions(void) const
{
  XsdSimpleType* simpleTypeObj = getXsdSimpleType();
  if (simpleTypeObj != nullptr)
    return simpleTypeObj->getAllRestrictions();
  return {};
}

