#include "pchdef.h"
#include "HunterTriggers.h"
#include "HunterActions.h"

using namespace ai;

BOOL HunterNoStingsActiveTrigger::IsActive()
{
    return ai->GetTargetHealthPercent() > 40 &&
        !ai->TargetHasAura("serpent sting") && 
        !ai->TargetHasAura("scorpid sting") &&
        !ai->TargetHasAura("viper sting");
}



BOOL HuntersPetDeadTrigger::IsActive()
{
    return ai->HasPet() && ai->IsPetDead() && !ai->IsMounted();
}


BOOL HuntersPetLowHealthTrigger::IsActive()
{
    return ai->HasPet() && ai->GetPetHealthPercent() < EAT_DRINK_PERCENT && !ai->IsMounted();
}

