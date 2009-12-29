#include "pchdef.h"
#include "WarriorTriggers.h"
#include "GenericWarriorStrategy.h"

using namespace ai;

void GenericWarriorStrategy::InitTriggers(std::list<Trigger*> &triggers)
{
    triggers.push_back(new WarriorEnemyTooCloseTrigger(ai));
}
