#include "pchdef.h"
#include "DruidTriggers.h"
#include "DruidMultipliers.h"
#include "GenericDruidNonCombatStrategy.h"

using namespace ai;

void GenericDruidNonCombatStrategy::InitTriggers(std::list<Trigger*> &triggers)
{
    GenericNonCombatStrategy::InitTriggers(triggers);
    
    triggers.push_back(new DruidPartyMemberLowHealthTrigger(ai));
}

