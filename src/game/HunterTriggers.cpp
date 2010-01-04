#include "pchdef.h"
#include "HunterTriggers.h"
#include "HunterActions.h"

using namespace ai;

BOOL HunterEnemyTooCloseTrigger::IsActive() { return EnemyTooCloseTrigger::IsActive(); }

BOOL HunterNoStingsActiveTrigger::IsActive()
{
    return !ai->TargetHasAura("serpent sting") && !ai->TargetHasAura("scorpid sting");
}

BOOL HunterHasNoPetTrigger::IsActive()
{
    return !ai->HasPet();
}

BOOL HuntersPetDeadTrigger::IsActive()
{
    return ai->HasPet() && ai->IsPetDead();
}


BOOL HuntersPetLowHealthTrigger::IsActive()
{
    return ai->HasPet() && ai->GetPetHealthPercent() < EAT_DRINK_PERCENT;
}

