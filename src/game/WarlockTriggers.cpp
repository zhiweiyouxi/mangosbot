#include "pchdef.h"
#include "WarlockTriggers.h"
#include "WarlockActions.h"

using namespace ai;

bool DemonArmorTrigger::IsActive() 
{
	return ai->GetManaPercent() > 30 && 
		!ai->HasAura("demon skin") &&
		!ai->HasAura("demon armor");
}