#include "pchdef.h"
#include "GenericActions.h"
#include "PlayerbotAIFacade.h"
#include <math.h>

using namespace ai;

BOOL FleeAction::Execute()
{
    // TODO: move away from battle
    ai->Flee();
    return TRUE;
}

//---------------------------------------------------------------------------------------------------------------------

BOOL ReachMeleeAction::Execute()
{
    ai->MoveToTarget();
    return TRUE;
}

BOOL MeleeAction::Execute()
{
    ai->Melee();
    return TRUE;
}

BOOL ReachMeleeAction::isUseful()
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

BOOL LootAction::Execute()
{
    ai->Loot();
    return TRUE;
}

BOOL EmoteAction::Execute()
{
    if (!name)
    {
        name = rand() % 450;
    }
    ai->Emote(name);

    return TRUE;
}