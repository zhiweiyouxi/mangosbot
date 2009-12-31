#include "pchdef.h"
#include "GenericActions.h"
#include "PlayerbotAIFacade.h"

using namespace ai;

void FleeAction::Execute()
{
    // TODO: move away from battle
    ai->MoveToMaster();
}

void MeleeAction::Execute()
{
    ai->MoveToTarget();
}

void ReachSpellAction::Execute()
{
    ai->MoveToTarget(SPELL_DISTANCE);
}

BOOL CastLifeBloodAction::isUseful()
{
    return ai->GetHealthPercent() <= 25;
}

BOOL ReachSpellAction::isUseful()
{
    return ai->GetDistanceToEnemy() > SPELL_DISTANCE;
}