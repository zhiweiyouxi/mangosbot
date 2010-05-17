#include "pchdef.h"
#include "HunterActions.h"
#include "GenericActions.h"

using namespace ai;

bool CastSerpentStingAction::isUseful()
{
    return ai->GetTargetHealthPercent() > 50;
}

bool CastViperStingAction::isUseful()
{
    return ai->GetManaPercent() < 50 && ai->GetTargetManaPercent() >= 30;
}

bool CastArcaneShotAction::isUseful()
{
    return ai->GetTargetHealthPercent() >= 5 && ai->GetManaPercent() >= 30;
}

bool CastExplosiveShotAction::isUseful()
{
    return ai->GetTargetHealthPercent() >= 25 && ai->GetManaPercent() >= 30;
}

bool CastAimedShotAction::isUseful()
{
    return ai->GetTargetHealthPercent() >= 5 && ai->GetManaPercent() >= 30;
}

bool CastMendPetAction::isUseful()
{
    return !ai->PetHasAura(spell) && !ai->IsMounted();
}

bool CastAspectOfThePackAction::isUseful() {
    return !ai->HasAura("aspect of the pack");
}

bool CastAspectOfTheHawkAction::isUseful() {
    return !ai->HasAura("aspect of the hawk");
}

bool CastAspectOfTheCheetahAction::isUseful() {
    return !ai->HasAura("aspect of the cheetah") && !ai->HasAura("aspect of the pack");
}

bool CastAspectOfTheViperAction::isUseful() {
    return !ai->HasAura("aspect of the viper") && ai->GetManaPercent() < 50;
}
