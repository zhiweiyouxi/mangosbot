#include "pchdef.h"
#include "WarriorTriggers.h"
#include "GenericWarriorStrategy.h"

using namespace ai;

void GenericWarriorStrategy::InitTriggers(std::list<Trigger*> &triggers)
{
    triggers.push_back(new RevengeAvailableTrigger(ai));
    triggers.push_back(new RendDebuffTrigger(ai));
    triggers.push_back(new DisarmDebuffTrigger(ai));
    triggers.push_back(new SunderArmorDebuffTrigger(ai));
}
