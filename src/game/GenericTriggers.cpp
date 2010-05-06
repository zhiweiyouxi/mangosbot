#include "pchdef.h"
#include "GenericTriggers.h"
#include "Unit.h"
#include "PlayerbotAIFacade.h"
#include <math.h>

using namespace ai;

bool RageAvailable::IsActive()
{
    return ai->GetRage() >= amount;
}

bool ComboPointsAvailable::IsActive()
{
    return ai->GetComboPoints() >= amount;
}

bool LowManaTrigger::IsActive()
{
    return ai->GetManaPercent() != 0 && ai->GetManaPercent() < EAT_DRINK_PERCENT;
}

bool LoseAggroTrigger::IsActive()
{
    return !ai->HasAggro();
}

bool PanicTrigger::IsActive()
{
    return ai->GetHealthPercent() < 25 && ai->GetManaPercent() != 0 && ai->GetManaPercent() < 25;
}

bool BuffTrigger::IsActive()
{
    return !ai->HasAura(spell) && ai->canCastSpell(spell) &&
        (ai->GetManaPercent() > 30 || !ai->GetManaPercent());
}

bool BuffOnPartyTrigger::IsActive()
{
    return !ai->IsAllPartyHasAura(spell) && ai->canCastSpell(spell) && 
        (ai->GetManaPercent() > 50 || !ai->GetManaPercent());
}

bool NoAttackersTrigger::IsActive()
{
    return !ai->HaveTarget() && ai->GetAttackerCount() > 0;
}

bool MyAttackerCountTrigger::IsActive()
{
    return ai->GetMyAttackerCount() >= amount;
}

bool DebuffTrigger::IsActive()
{
    return !ai->TargetHasAura(spell) && ai->canCastSpell(spell) && ai->GetTargetHealthPercent() > 40 &&
        (ai->GetManaPercent() > 50 || !ai->GetManaPercent());
}

bool SpellAvailableTrigger::IsActive()
{
    return ai->canCastSpell(spell);
}

bool LootAvailableTrigger::IsActive()
{   
    return ai->CanLoot();
}

bool RandomTrigger::IsActive()
{
    int vl  = rand() % probability;
    return vl == 0;
}

bool AndTrigger::IsActive()
{
    return ls->IsActive() && rs->IsActive();
}

const char* AndTrigger::getName()
{
    std::string name(ls->getName());
    name = name + " and ";
    name = name + rs->getName();
    return name.c_str();
}

bool BoostTrigger::IsActive()
{
    return ai->HasSpell(spell) && !ai->HasAura(spell) && ai->GetBalancePercent() <= balance;
}


bool SnareTargetTrigger::IsActive()
{
    return ai->IsTargetMoving() && !ai->TargetHasAura(aura) && ai->HasSpell(aura);
}

bool NoPetTrigger::IsActive()
{
    return !ai->HasPet() && !ai->IsMounted();
}

bool ItemCountTrigger::IsActive()
{
	return ai->GetItemCount(item) < count;
}
