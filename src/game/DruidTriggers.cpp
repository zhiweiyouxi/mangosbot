#include "pchdef.h"
#include "DruidTriggers.h"
#include "DruidActions.h"

using namespace ai;

BOOL BearTankDruidLoseAggroTrigger::IsActive() 
{
    return LoseAggroTrigger::IsActive() && (ai->HasAura("bear form") || ai->HasAura("dire bear form"));
}

