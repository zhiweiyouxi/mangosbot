#include "pchdef.h"
#include "GenericActions.h"
#include "PlayerbotAIFacade.h"

using namespace ai;

NextAction** CastRangedSpellAction::getPrerequisites()
{
    return NextAction::merge( NextAction::array(0, new NextAction("reach spell"), NULL), CastSpellAction::getPrerequisites());
}

BOOL FleeAction::Execute()
{
    // TODO: move away from battle
    ai->Flee();
    return TRUE;
}

BOOL CastMeleeSpellAction::isPossible()
{
    return CastSpellAction::isPossible() && ai->GetDistanceToEnemy() <= ATTACK_DISTANCE;
}

//---------------------------------------------------------------------------------------------------------------------

BOOL MeleeAction::Execute()
{
    ai->MoveToTarget();
    return TRUE;
}

BOOL MeleeAction::isUseful()
{
    return ai->GetDistanceToEnemy() > ATTACK_DISTANCE;
}

//---------------------------------------------------------------------------------------------------------------------

BOOL ReachSpellAction::Execute()
{
    ai->MoveToTarget(SPELL_DISTANCE);
    return TRUE;
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

BOOL UseHealingPotion::Execute()
{
    ai->UseHealingPotion();
    return TRUE;
}

BOOL UseHealingPotion::isPossible()
{
    return ai->HasHealingPotion();
}

//---------------------------------------------------------------------------------------------------------------------

BOOL UseManaPotion::Execute()
{
    ai->UseManaPotion();
    return TRUE;
}

BOOL UseManaPotion::isPossible()
{
    return ai->HasManaPotion();
}

//---------------------------------------------------------------------------------------------------------------------

BOOL UsePanicPotion::Execute()
{
    ai->UsePanicPotion();
    return TRUE;
}

BOOL UsePanicPotion::isPossible()
{
    return ai->HasPanicPotion();
}

//---------------------------------------------------------------------------------------------------------------------

BOOL HealPartyMemberAction::Execute()
{
    ai->CastSpell(spell, ai->GetPartyMinHealthPlayer());
    return TRUE;
}

BOOL HealPartyMemberAction::isUseful()
{
    return ai->GetPartyMinHealthPercent() < EAT_DRINK_PERCENT;
}

//---------------------------------------------------------------------------------------------------------------------

BOOL BuffOnPartyAction::Execute()
{
    ai->CastSpell(spell, ai->GetPartyMemberWithoutAura(spell));
    return TRUE;
}

BOOL BuffOnPartyAction::isUseful()
{
    return !ai->IsAllPartyHasAura(spell);
}

//---------------------------------------------------------------------------------------------------------------------

BOOL AttackLeastThreatAction::Execute()
{
    ai->AttackLeastThreat();
    return TRUE;
}

//---------------------------------------------------------------------------------------------------------------------

BOOL AttackBiggerThreatAction::Execute()
{
    ai->AttackBiggerThreat();
    return TRUE;
}

//---------------------------------------------------------------------------------------------------------------------

BOOL CastDebuffSpellAction::isPossible()
{
    return CastSpellAction::isPossible() && !ai->TargetHasAura(spell);
}
