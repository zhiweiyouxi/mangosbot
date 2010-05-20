#include "pchdef.h"
#include "WarlockTriggers.h"
#include "WarlockActions.h"

using namespace ai;

bool DemonArmorTrigger::IsActive() 
{
	Unit* target = GetTarget();
	return ai->GetManaPercent() > 30 && 
		!spellManager->HasAura("demon skin", target) &&
		!spellManager->HasAura("demon armor", target);
}