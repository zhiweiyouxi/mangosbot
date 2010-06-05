#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "WarlockTriggers.h"
#include "WarlockActions.h"

using namespace ai;

bool DemonArmorTrigger::IsActive() 
{
	Unit* target = GetTarget();
	return statsManager->GetManaPercent(targetManager->GetSelf()) > 30 && 
		!spellManager->HasAura("demon skin", target) &&
		!spellManager->HasAura("demon armor", target);
}