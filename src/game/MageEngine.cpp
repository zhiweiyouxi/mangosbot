#include "pchdef.h"
#include "Action.h"
#include "Queue.h"
#include "MageEngine.h"
#include "MageActions.h"
#include "MageTriggers.h"

using namespace ai;

void MageEngine::InitTriggers()
{
    triggers.push_back(new MageEnemyTooCloseTrigger(ai));
}

void MageEngine::InitQueue()
{
    queue.Push(new ActionBasket(new CastFrostBoltAction(ai), 1.0f));
}