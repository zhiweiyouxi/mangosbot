#include "pchdef.h"
#include "GenericTriggers.h"
#include "Unit.h"
#include "PlayerbotAIFacade.h"

using namespace ai;

BOOL EnemyTooCloseTrigger::IsActive()
{
    float distance = ai->GetDistanceToEnemy();
    return distance <= ATTACK_DISTANCE;
}
