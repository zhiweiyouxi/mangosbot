#include "pchdef.h"
#include "NonCombatActions.h"
#include "PlayerbotAIFacade.h"

using namespace ai;

void FollowAction::Execute()
{
    ai->FollowMaster();
}

//---------------------------------------------------------------------------------------------------------------------

void StayAction::Execute()
{
    ai->Stay();
}

//---------------------------------------------------------------------------------------------------------------------

void DrinkAction::Execute()
{
    ai->UseDrink();
}

BOOL DrinkAction::isUseful()
{
    return ai->GetManaPercent() < EAT_DRINK_PERCENT && !ai->HasAura("drink");
}

//---------------------------------------------------------------------------------------------------------------------

void EatAction::Execute()
{
    ai->UseFood();
}

BOOL EatAction::isUseful()
{
    return ai->GetHealthPercent() < EAT_DRINK_PERCENT && !ai->HasAura("eat");
}
