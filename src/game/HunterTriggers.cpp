#include "pchdef.h"
#include "HunterTriggers.h"
#include "HunterActions.h"

using namespace ai;

bool HunterNoStingsActiveTrigger::IsActive()
{
    return ai->GetTargetHealthPercent() > 40 &&
        !ai->TargetHasAura("serpent sting") && 
        !ai->TargetHasAura("scorpid sting") &&
        !ai->TargetHasAura("viper sting");
}



bool HuntersPetDeadTrigger::IsActive()
{
    return ai->HasPet() && ai->IsPetDead() && !ai->IsMounted();
}


bool HuntersPetLowHealthTrigger::IsActive()
{
    return ai->HasPet() && ai->GetPetHealthPercent() < EAT_DRINK_PERCENT && !ai->IsMounted();
}
