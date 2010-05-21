#include "pchdef.h"
#include "HunterActions.h"
#include "GenericActions.h"

using namespace ai;

bool CastSerpentStingAction::isUseful()
{
    return statsManager->GetHealthPercent(GetTarget()) > 50;
}

bool CastViperStingAction::isUseful()
{
    return ai->GetManaPercent() < 50 && ai->GetTargetManaPercent() >= 30;
}

bool CastArcaneShotAction::isUseful()
{
    return statsManager->GetHealthPercent(GetTarget()) >= 5 && ai->GetManaPercent() >= 30;
}

bool CastExplosiveShotAction::isUseful()
{
    return statsManager->GetHealthPercent(GetTarget()) >= 25 && ai->GetManaPercent() >= 30;
}

bool CastAimedShotAction::isUseful()
{
    return statsManager->GetHealthPercent(GetTarget()) >= 5 && ai->GetManaPercent() >= 30;
}

Unit* CastMendPetAction::GetTarget()
{
	return targetManager->GetSelf();
}

bool CastAspectOfTheCheetahAction::isUseful() {
    return !spellManager->HasAnyAuraOf(GetTarget(), "aspect of the cheetah", "aspect of the pack");
}

bool CastAspectOfTheViperAction::isUseful() {
	return CastBuffSpellAction::isUseful() && ai->GetManaPercent() < 50;
}
