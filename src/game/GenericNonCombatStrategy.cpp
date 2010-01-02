#include "pchdef.h"
#include "GenericTriggers.h"
#include "GenericNonCombatStrategy.h"

using namespace ai;

void GenericNonCombatStrategy::InitTriggers(std::list<Trigger*> &triggers)
{
    Strategy::InitTriggers(triggers);
    triggers.push_back(new LowHealthTrigger(ai));
    triggers.push_back(new LowManaTrigger(ai));
}

