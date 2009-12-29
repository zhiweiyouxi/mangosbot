#include "pchdef.h"
#include "GenericTriggers.h"
#include "Unit.h"
#include "PlayerbotAIFacade.h"

using namespace ai;

BOOL EnemyTooCloseTrigger::IsActive()
{
    Unit *target = ai->GetCurrentTarget();
    if (target && !target->isDead())
    {
        float distance = ai->GetDistance(target);
        return distance <= ATTACK_DISTANCE;
    }
    return FALSE;
}
