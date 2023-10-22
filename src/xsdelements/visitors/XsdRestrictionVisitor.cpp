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

void XsdRestrictionVisitor::visit(std::shared_ptr<XsdAbstractElement> element)
{
  AttributesVisitor::visit(element);

  if(std::dynamic_pointer_cast<XsdEnumeration>(element))
    owner->add(std::static_pointer_cast<XsdEnumeration>(element));
  else if(std::dynamic_pointer_cast<XsdFractionDigits>(element))
    owner->setFractionDigits(std::static_pointer_cast<XsdFractionDigits>(element));
  else if(std::dynamic_pointer_cast<XsdLength>(element))
    owner->setLength(std::static_pointer_cast<XsdLength>(element));
  else if(std::dynamic_pointer_cast<XsdMaxExclusive>(element))
    owner->setMaxExclusive(std::static_pointer_cast<XsdMaxExclusive>(element));
  else if(std::dynamic_pointer_cast<XsdMaxInclusive>(element))
    owner->setMaxInclusive(std::static_pointer_cast<XsdMaxInclusive>(element));
  else if(std::dynamic_pointer_cast<XsdMaxLength>(element))
    owner->setMaxLength(std::static_pointer_cast<XsdMaxLength>(element));
  else if(std::dynamic_pointer_cast<XsdMinExclusive>(element))
    owner->setMinExclusive(std::static_pointer_cast<XsdMinExclusive>(element));
  else if(std::dynamic_pointer_cast<XsdMinInclusive>(element))
    owner->setMinInclusive(std::static_pointer_cast<XsdMinInclusive>(element));
  else if(std::dynamic_pointer_cast<XsdMinLength>(element))
    owner->setMinLength(std::static_pointer_cast<XsdMinLength>(element));
  else if(std::dynamic_pointer_cast<XsdPattern>(element))
    owner->setPattern(std::static_pointer_cast<XsdPattern>(element));
  else if(std::dynamic_pointer_cast<XsdTotalDigits>(element))
    owner->setTotalDigits(std::static_pointer_cast<XsdTotalDigits>(element));
  else if(std::dynamic_pointer_cast<XsdWhiteSpace>(element))
    owner->setWhiteSpace(std::static_pointer_cast<XsdWhiteSpace>(element));
  else if(std::dynamic_pointer_cast<XsdAll>(element))
    owner->setAll(std::static_pointer_cast<XsdAll>(element));
  else if(std::dynamic_pointer_cast<XsdChoice>(element))
    owner->setChoice(std::static_pointer_cast<XsdChoice>(element));
  else if(std::dynamic_pointer_cast<XsdSequence>(element))
    owner->setSequence(std::static_pointer_cast<XsdSequence>(element));
  else if(std::dynamic_pointer_cast<XsdGroup>(element))
    owner->setGroup(ReferenceBase::createFromXsd(element));
  else
    assert(false);
}
