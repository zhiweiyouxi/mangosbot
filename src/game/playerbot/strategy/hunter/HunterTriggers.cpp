#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "../GenericTriggers.h"
#include "../GenericActions.h"
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
    return targetManager->GetPet() && statsManager->IsDead(targetManager->GetPet()) && !ai->GetStatsManager()->IsMounted();
}


bool HuntersPetLowHealthTrigger::IsActive()
{
    return targetManager->GetPet() && statsManager->GetHealthPercent(targetManager->GetPet()) < EAT_DRINK_PERCENT && !ai->GetStatsManager()->IsMounted();
}
