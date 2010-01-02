#include "pchdef.h"
#include "DruidTriggers.h"
#include "GenericDruidStrategy.h"

using namespace ai;

void GenericDruidStrategy::InitTriggers(std::list<Trigger*> &triggers)
{
    CombatStrategy::InitTriggers(triggers);
    triggers.push_back(new DruidLowHealthTrigger(ai));
}
