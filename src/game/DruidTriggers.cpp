#include "pchdef.h"
#include "DruidTriggers.h"
#include "DruidActions.h"

using namespace ai;

bool BearTankDruidLoseAggroTrigger::IsActive() 
{
    return LoseAggroTrigger::IsActive() && (ai->HasAura("bear form") || ai->HasAura("dire bear form"));
}

