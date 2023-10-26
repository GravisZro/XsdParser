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

std::shared_ptr<XsdAbstractElementVisitor> XsdAttributeVisitorFunction(std::shared_ptr<XsdAbstractElement> element)
{
  return std::static_pointer_cast<XsdAbstractElementVisitor>(
            create<XsdSimpleTypeVisitor>(
              std::static_pointer_cast<XsdSimpleType>(element)));
}

void XsdAttribute::initialize(void)
{
  XsdNamedElements::initialize();
  m_simpleType.reset();
  m_defaultElement.reset();
  m_fixed.reset();
  m_type.reset();

  m_form = getFormDefaultValue(getParent());
  m_use = UsageEnum::OPTIONAL;

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
      m_simpleType = create<UnsolvedReference>(
                       m_type.value(),
                       std::static_pointer_cast<XsdNamedElements>(
                         create<XsdSimpleType>(getParser(),
                                               StringMap{},
                                               XsdAttributeVisitorFunction,
                                               nullptr)));
      getParser()->addUnsolvedReference(std::static_pointer_cast<UnsolvedReference>(m_simpleType));
  }
}


std::optional<std::string> XsdAttribute::getFormDefaultValue(std::shared_ptr<XsdAbstractElement> parent)
{
    if (parent == nullptr)
      return {};

    if(auto p = std::dynamic_pointer_cast<XsdElement>(parent); p)
      return p->getForm();

    if(auto p = std::dynamic_pointer_cast<XsdSchema>(parent); p)
      return p->getAttributeFormDefault();

    return getFormDefaultValue(parent->getParent());
}

void XsdAttribute::accept(std::shared_ptr<XsdAbstractElementVisitor> visitorParam)
{
  XsdNamedElements::accept(visitorParam);
  visitorParam->visit(std::static_pointer_cast<XsdAttribute>(shared_from_this()));
}



/**
 * Performs a copy of the current object for replacing purposes. The cloned objects are used to replace
 * {@link UnsolvedReference} objects in the reference solving process.
 * @param placeHolderAttributes The additional attributes to add to the clone.
 * @return A copy of the object from which is called upon.
 */

std::shared_ptr<XsdAbstractElement> XsdAttribute::clone(StringMap placeHolderAttributes)
{
    placeHolderAttributes.merge(getAttributesMap());
    placeHolderAttributes.erase(*TYPE_TAG);
    placeHolderAttributes.erase(*REF_TAG);

    auto elementCopy = create<XsdAttribute>(getParser(),
                                            placeHolderAttributes,
                                            m_visitorFunction,
                                            nullptr);

    elementCopy->m_simpleType = ReferenceBase::clone(getParser(), m_simpleType, elementCopy);
    elementCopy->m_type = m_type;
    elementCopy->setCloneOf(shared_from_this());

    return elementCopy;
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
void XsdAttribute::replaceUnsolvedElements(std::shared_ptr<NamedConcreteElement> elementWrapper)
{
    XsdNamedElements::replaceUnsolvedElements(elementWrapper);

    std::shared_ptr<XsdAbstractElement> element = elementWrapper->getElement();

    if (std::dynamic_pointer_cast<XsdSimpleType>(element) &&
        m_simpleType &&
        compareReference(elementWrapper, m_type))
    {
        m_simpleType = elementWrapper;
    }
}

std::shared_ptr<XsdSimpleType> XsdAttribute::getXsdSimpleType(void) const
{
if (std::dynamic_pointer_cast<ConcreteElement>(m_simpleType))
  return std::dynamic_pointer_cast<XsdSimpleType>(m_simpleType->getElement());
return nullptr;
}

std::list<std::shared_ptr<XsdRestriction>> XsdAttribute::getAllRestrictions(void) const
{
  auto simpleTypeObj = getXsdSimpleType();
  if (simpleTypeObj)
    return simpleTypeObj->getAllRestrictions();
  return {};
}

