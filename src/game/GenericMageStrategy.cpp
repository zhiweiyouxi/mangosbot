#include "pchdef.h"
#include "MageTriggers.h"
#include "GenericMageStrategy.h"

using namespace ai;

void GenericMageStrategy::InitTriggers(std::list<Trigger*> &triggers)
{
    triggers.push_back(new MageEnemyTooCloseTrigger(ai));
}
