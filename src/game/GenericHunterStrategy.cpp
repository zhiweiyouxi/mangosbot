#include "pchdef.h"
#include "HunterTriggers.h"
#include "GenericHunterStrategy.h"

using namespace ai;

void GenericHunterStrategy::InitTriggers(std::list<Trigger*> &triggers)
{
    triggers.push_back(new HunterEnemyTooCloseTrigger(ai));
}
