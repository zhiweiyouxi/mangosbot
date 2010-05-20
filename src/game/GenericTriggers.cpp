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

bool EnergyAvailable::IsActive()
{
	return ai->GetEnergy() >= amount;
}

bool ComboPointsAvailable::IsActive()
{
    return ai->GetComboPoints() >= amount;
}

bool LoseAggroTrigger::IsActive()
{
    return !ai->HasAggro();
}

bool PanicTrigger::IsActive()
{
    return ai->GetStatsManager()->GetHealthPercent(ai->GetTargetManager()->GetSelf()) < 25 && 
		ai->GetManaPercent() != 0 && 
		ai->GetManaPercent() < 25;
}

Unit* BuffTrigger::GetTarget()
{
	return targetManager->GetSelf();
}

bool BuffTrigger::IsActive()
{
	return SpellTrigger::IsActive() && 
		!spellManager->HasAura(spell, GetTarget()) && 
        (ai->GetManaPercent() > 40 || !ai->GetManaPercent());
}

Unit* BuffOnPartyTrigger::GetTarget()
{
	return targetManager->GetPartyMemberWithoutAura(spell);
}

bool NoAttackersTrigger::IsActive()
{
    return !ai->HaveTarget() && ai->GetAttackerCount() > 0;
}

bool MyAttackerCountTrigger::IsActive()
{
    return ai->GetMyAttackerCount() >= amount;
}

Unit* DebuffTrigger::GetTarget()
{
	return targetManager->GetCurrentTarget();
}

bool DebuffTrigger::IsActive()
{
	return BuffTrigger::IsActive() && statsManager->GetHealthPercent(GetTarget()) > 25;
}

Unit* SpellTrigger::GetTarget()
{
	return targetManager->GetCurrentTarget();
}

bool SpellTrigger::IsActive()
{
	return GetTarget();
}

bool SpellCanBeCastTrigger::IsActive()
{
	Unit* target = GetTarget();
	return target && spellManager->CanCastSpell(spell, target);
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
	Unit* target = GetTarget();
	return target && !spellManager->HasAura(spell, target) && ai->GetBalancePercent() <= balance;
}

bool SnareTargetTrigger::IsActive()
{
	Unit* target = GetTarget();
	return DebuffTrigger::IsActive() && ai->IsTargetMoving() && !spellManager->HasAura(spell, target);
}

bool ItemCountTrigger::IsActive()
{
	return ai->GetItemCount(item) < count;
}

Unit* InterruptSpellTrigger::GetTarget()
{
	return targetManager->GetCurrentTarget();
}

bool InterruptSpellTrigger::IsActive() 
{
	return SpellTrigger::IsActive() && spellManager->IsSpellCasting(GetTarget());
}

Unit* HasAuraTrigger::GetTarget()
{
	return targetManager->GetSelf();
}

bool HasAuraTrigger::IsActive()
{
	return spellManager->HasAura(spell, GetTarget());
}
