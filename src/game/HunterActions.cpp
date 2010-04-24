#include "pchdef.h"
#include "HunterActions.h"
#include "GenericActions.h"

using namespace ai;

BOOL CastSerpentStingAction::isUseful()
{
    return ai->GetTargetHealthPercent() > 50;
}

BOOL CastViperStingAction::isUseful()
{
    return ai->GetManaPercent() < 50;
}

BOOL CastArcaneShotAction::isUseful()
{
    return ai->GetTargetHealthPercent() >= 5 && ai->GetManaPercent() >= 30;
}

BOOL CastAimedShotAction::isUseful()
{
    return ai->GetTargetHealthPercent() >= 5 && ai->GetManaPercent() >= 30;
}

BOOL CastMendPetAction::isUseful()
{
    return !ai->PetHasAura(spell) && !ai->IsMounted();
}

BOOL CastAspectOfThePackAction::isUseful() {
    return !ai->HasAura("aspect of the pack");
}

BOOL CastAspectOfTheHawkAction::isUseful() {
    return !ai->HasAura("aspect of the hawk");
}

BOOL CastAspectOfTheCheetahAction::isUseful() {
    return !ai->HasAura("aspect of the cheetah") && !ai->HasAura("aspect of the pack");
}

BOOL CastAspectOfTheViperAction::isUseful() {
    return !ai->HasAura("aspect of the viper") && ai->GetManaPercent() < 50;
}
