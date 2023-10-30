#include "XsdRestrictionVisitor.h"

#include <xsdelements/elementswrapper/ReferenceBase.h>
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

void XsdRestrictionVisitor::visit(XsdAbstractElement* element)
{
  AttributesVisitor::visit(element);

  if(dynamic_cast<XsdEnumeration*>(element) != nullptr)
    owner->add(static_cast<XsdEnumeration*>(element));
  else if(dynamic_cast<XsdFractionDigits*>(element) != nullptr)
    owner->setFractionDigits(static_cast<XsdFractionDigits*>(element));
  else if(dynamic_cast<XsdLength*>(element) != nullptr)
    owner->setLength(static_cast<XsdLength*>(element));
  else if(dynamic_cast<XsdMaxExclusive*>(element) != nullptr)
    owner->setMaxExclusive(static_cast<XsdMaxExclusive*>(element));
  else if(dynamic_cast<XsdMaxInclusive*>(element) != nullptr)
    owner->setMaxInclusive(static_cast<XsdMaxInclusive*>(element));
  else if(dynamic_cast<XsdMaxLength*>(element) != nullptr)
    owner->setMaxLength(static_cast<XsdMaxLength*>(element));
  else if(dynamic_cast<XsdMinExclusive*>(element) != nullptr)
    owner->setMinExclusive(static_cast<XsdMinExclusive*>(element));
  else if(dynamic_cast<XsdMinInclusive*>(element) != nullptr)
    owner->setMinInclusive(static_cast<XsdMinInclusive*>(element));
  else if(dynamic_cast<XsdMinLength*>(element) != nullptr)
    owner->setMinLength(static_cast<XsdMinLength*>(element));
  else if(dynamic_cast<XsdPattern*>(element) != nullptr)
    owner->setPattern(static_cast<XsdPattern*>(element));
  else if(dynamic_cast<XsdTotalDigits*>(element) != nullptr)
    owner->setTotalDigits(static_cast<XsdTotalDigits*>(element));
  else if(dynamic_cast<XsdWhiteSpace*>(element) != nullptr)
    owner->setWhiteSpace(static_cast<XsdWhiteSpace*>(element));
  else if(dynamic_cast<XsdAll*>(element) != nullptr)
    owner->setAll(static_cast<XsdAll*>(element));
  else if(dynamic_cast<XsdChoice*>(element) != nullptr)
    owner->setChoice(static_cast<XsdChoice*>(element));
  else if(dynamic_cast<XsdSequence*>(element) != nullptr)
    owner->setSequence(static_cast<XsdSequence*>(element));
  else if(dynamic_cast<XsdGroup*>(element) != nullptr)
    owner->setGroup(ReferenceBase::createFromXsd(element));
}
