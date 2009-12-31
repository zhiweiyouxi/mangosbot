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

BOOL EnemyOutOfMeleeTrigger::IsActive()
{
    float distance = ai->GetDistanceToEnemy();
    return distance > ATTACK_DISTANCE;
}

BOOL RageAvailable::IsActive()
{
    return ai->GetRage() >= amount;
}

BOOL LowHealthTrigger::IsActive()
{
    return ai->GetHealthPercent() < 25;
}

BOOL LowManaTrigger::IsActive()
{
    return ai->GetManaPercent() < 25;
}

BOOL LoseAggroTrigger::IsActive()
{
    return !ai->HasAggro();
}

BOOL AttackerCountTrigger::IsActive()
{
    return ai->GetAttackerCount() >= amount;
}
