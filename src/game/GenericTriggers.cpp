#include "pchdef.h"
#include "GenericTriggers.h"
#include "Unit.h"
#include "PlayerbotAIFacade.h"
#include <math.h>

using namespace ai;

BOOL EnemyTooCloseTrigger::IsActive()
{
    float distance = ai->GetDistanceToEnemy(ATTACK_DISTANCE + 1);
    return distance <= ATTACK_DISTANCE;
}

BOOL EnemyOutOfMeleeTrigger::IsActive()
{
    float distance = ai->GetDistanceToEnemy();
    return distance > ATTACK_DISTANCE;
}

BOOL EnemyOutOfSpellRangeTrigger::IsActive()
{
    float distance = ai->GetDistanceToEnemy();
    return distance > SPELL_DISTANCE; // TODO: externalize
}

BOOL RageAvailable::IsActive()
{
    return ai->GetRage() >= amount;
}

BOOL ComboPointsAvailable::IsActive()
{
    return ai->GetComboPoints() >= amount;
}

BOOL LowHealthTrigger::IsActive()
{
    return ai->GetHealthPercent() < value;
}

BOOL PartyMemberLowHealthTrigger::IsActive()
{
    return ai->GetPartyMinHealthPercent() < value;
}

BOOL NeedCureTrigger::IsActive()
{
    return ai->HasAuraToDispel(dispelType) && ai->HasSpell(spell);
}

BOOL PartyMemberNeedCureTrigger::IsActive()
{
    return ai->GetPartyMemberToDispell(dispelType) && ai->HasSpell(spell);
}

BOOL LowManaTrigger::IsActive()
{
    return ai->GetManaPercent() != 0 && ai->GetManaPercent() < EAT_DRINK_PERCENT;
}

BOOL LoseAggroTrigger::IsActive()
{
    return !ai->HasAggro();
}

BOOL AttackerCountTrigger::IsActive()
{
    return ai->GetAttackerCount() >= amount;
}


BOOL PanicTrigger::IsActive()
{
    return ai->GetHealthPercent() < 25 && ai->GetManaPercent() != 0 && ai->GetManaPercent() < 25;
}

BOOL BuffTrigger::IsActive()
{
    return !ai->HasAura(spell) && ai->HasSpell(spell);
}


BOOL BuffOnPartyTrigger::IsActive()
{
    return !ai->IsAllPartyHasAura(spell) && ai->HasSpell(spell);
}

BOOL NoAttackersTrigger::IsActive()
{
    return !ai->HaveTarget() && (ai->GetAttackerCount() > 0 && ai->GetMyAttackerCount() == 0);
}

BOOL DebuffTrigger::IsActive()
{
    return !ai->TargetHasAura(spell) && ai->canCastSpell(spell) && ai->GetTargetHealthPercent() > 30;
}

BOOL SpellAvailableTrigger::IsActive()
{
    return ai->canCastSpell(spell);
}

BOOL LootAvailableTrigger::IsActive()
{   
    return ai->CanLoot();
}

BOOL RandomTrigger::IsActive()
{
    int vl  = rand() % probability;
    return vl == 0;
}
