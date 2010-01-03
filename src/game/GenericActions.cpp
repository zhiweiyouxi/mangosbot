#include "pchdef.h"
#include "GenericActions.h"
#include "PlayerbotAIFacade.h"

using namespace ai;


void FleeAction::Execute()
{
    // TODO: move away from battle
    ai->Flee();
}

//---------------------------------------------------------------------------------------------------------------------

void MeleeAction::Execute()
{
    ai->MoveToTarget();
}

//---------------------------------------------------------------------------------------------------------------------

void ReachSpellAction::Execute()
{
    ai->MoveToTarget(SPELL_DISTANCE);
}

BOOL ReachSpellAction::isUseful()
{
    return ai->GetDistanceToEnemy() > SPELL_DISTANCE;
}

//---------------------------------------------------------------------------------------------------------------------

BOOL CastLifeBloodAction::isUseful()
{
    return ai->GetHealthPercent() <= EAT_DRINK_PERCENT;
}

//---------------------------------------------------------------------------------------------------------------------

void UseHealingPotion::Execute()
{
    ai->UseHealingPotion();
}

BOOL UseHealingPotion::isAvailable()
{
    return ai->HasHealingPotion();
}

//---------------------------------------------------------------------------------------------------------------------

void UseManaPotion::Execute()
{
    ai->UseManaPotion();
}

BOOL UseManaPotion::isAvailable()
{
    return ai->HasManaPotion();
}

//---------------------------------------------------------------------------------------------------------------------

void UsePanicPotion::Execute()
{
    ai->UsePanicPotion();
}

BOOL UsePanicPotion::isAvailable()
{
    return ai->HasPanicPotion();
}

//---------------------------------------------------------------------------------------------------------------------

void HealPartyMemberAction::Execute()
{
    ai->CastSpell(spell, ai->GetPartyMinHealthPlayer());
}

BOOL HealPartyMemberAction::isUseful()
{
    return ai->GetPartyMinHealthPercent() < EAT_DRINK_PERCENT;
}

//---------------------------------------------------------------------------------------------------------------------

void BuffOnPartyAction::Execute()
{
    ai->CastSpell(spell, ai->GetPartyMemberWithoutAura(spell));
}

BOOL BuffOnPartyAction::isUseful()
{
    return !ai->IsAllPartyHasAura(spell);
}
