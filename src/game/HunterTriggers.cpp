#include "pchdef.h"
#include "HunterTriggers.h"
#include "HunterActions.h"

using namespace ai;

bool HunterNoStingsActiveTrigger::IsActive()
{
	Unit* target = targetManager->GetCurrentTarget();
    return target && statsManager->GetHealthPercent(target) > 40 &&
        !spellManager->HasAura("serpent sting", target) && 
        !spellManager->HasAura("scorpid sting", target) &&
        !spellManager->HasAura("viper sting", target);
}

bool HuntersPetDeadTrigger::IsActive()
{
    return ai->HasPet() && ai->IsPetDead() && !ai->IsMounted();
}


bool HuntersPetLowHealthTrigger::IsActive()
{
    return ai->HasPet() && ai->GetPetHealthPercent() < EAT_DRINK_PERCENT && !ai->IsMounted();
}
