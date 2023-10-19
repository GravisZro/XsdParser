#include "XsdRestrictionVisitor.h"



#include <xsdelements/xsdrestrictions/XsdEnumeration.h>
#include <xsdelements/xsdrestrictions/XsdFractionDigits.h>
#include <xsdelements/xsdrestrictions/XsdIntegerRestrictions.h>
#include <xsdelements/xsdrestrictions/XsdLength.h>
#include <xsdelements/xsdrestrictions/XsdMaxExclusive.h>
#include <xsdelements/xsdrestrictions/XsdMaxInclusive.h>
#include <xsdelements/xsdrestrictions/XsdMaxLength.h>
#include <xsdelements/xsdrestrictions/XsdMinExclusive.h>
#include <xsdelements/xsdrestrictions/XsdMinInclusive.h>
#include <xsdelements/xsdrestrictions/XsdMinLength.h>
#include <xsdelements/xsdrestrictions/XsdPattern.h>
#include <xsdelements/xsdrestrictions/XsdStringRestrictions.h>
#include <xsdelements/xsdrestrictions/XsdTotalDigits.h>
#include <xsdelements/xsdrestrictions/XsdWhiteSpace.h>
#include <xsdelements/XsdAll.h>
#include <xsdelements/XsdChoice.h>
#include <xsdelements/XsdSequence.h>
#include <xsdelements/XsdGroup.h>

#include <xsdelements/XsdRestriction.h>

XsdRestrictionVisitor::XsdRestrictionVisitor(std::shared_ptr<XsdRestriction> owner)
      : AttributesVisitor(std::static_pointer_cast<XsdAnnotatedElements>(owner)),
        m_owner(owner) { }

void XsdRestrictionVisitor::visit(std::shared_ptr<XsdEnumeration> element)
  {
      AttributesVisitor::visit(element);
      m_owner->add(element);
  }

void XsdRestrictionVisitor::visit(std::shared_ptr<XsdFractionDigits> element)
  {
      AttributesVisitor::visit(element);
      m_owner->setFractionDigits(element);
  }

void XsdRestrictionVisitor::visit(std::shared_ptr<XsdLength> element)
  {
      AttributesVisitor::visit(element);
      m_owner->setLength(element);
  }

void XsdRestrictionVisitor::visit(std::shared_ptr<XsdMaxExclusive> element)
  {
      AttributesVisitor::visit(element);
      m_owner->setMaxExclusive(element);
  }

void XsdRestrictionVisitor::visit(std::shared_ptr<XsdMaxInclusive> element)
  {
      AttributesVisitor::visit(element);
      m_owner->setMaxInclusive(element);
  }

void XsdRestrictionVisitor::visit(std::shared_ptr<XsdMaxLength> element)
  {
      AttributesVisitor::visit(element);
      m_owner->setMaxLength(element);
  }

void XsdRestrictionVisitor::visit(std::shared_ptr<XsdMinExclusive> element)
  {
      AttributesVisitor::visit(element);
      m_owner->setMinExclusive(element);
  }

void XsdRestrictionVisitor::visit(std::shared_ptr<XsdMinInclusive> element)
  {
      AttributesVisitor::visit(element);
      m_owner->setMinInclusive(element);
  }

void XsdRestrictionVisitor::visit(std::shared_ptr<XsdMinLength> element)
  {
      AttributesVisitor::visit(element);
      m_owner->setMinLength(element);
  }

void XsdRestrictionVisitor::visit(std::shared_ptr<XsdPattern> element)
  {
      AttributesVisitor::visit(element);
      m_owner->setPattern(element);
  }

void XsdRestrictionVisitor::visit(std::shared_ptr<XsdTotalDigits> element)
  {
      AttributesVisitor::visit(element);
      m_owner->setTotalDigits(element);
  }

void XsdRestrictionVisitor::visit(std::shared_ptr<XsdWhiteSpace> element)
  {
      AttributesVisitor::visit(element);
      m_owner->setWhiteSpace(element);
  }

void XsdRestrictionVisitor::visit(std::shared_ptr<XsdAll> element)
  {
      AttributesVisitor::visit(element);
      m_owner->setAll(element);
  }

void XsdRestrictionVisitor::visit(std::shared_ptr<XsdChoice> element)
  {
      AttributesVisitor::visit(element);
      m_owner->setChoice(element);
  }

void XsdRestrictionVisitor::visit(std::shared_ptr<XsdSequence> element)
  {
      AttributesVisitor::visit(element);
      m_owner->setSequence(element);
  }

void XsdRestrictionVisitor::XsdRestrictionVisitor::visit(std::shared_ptr<XsdGroup> element)
  {
      AttributesVisitor::visit(element);
      m_owner->setGroup(ReferenceBase::createFromXsd(element));
  }
