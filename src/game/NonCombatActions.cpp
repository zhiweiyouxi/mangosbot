#include "pchdef.h"
#include "NonCombatActions.h"
#include "PlayerbotAIFacade.h"

using namespace ai;

BOOL FollowAction::Execute()
{
    ai->FollowMaster();
    return TRUE;
}

//---------------------------------------------------------------------------------------------------------------------

BOOL StayAction::Execute()
{
    ai->Stay();
    return TRUE;
}

//---------------------------------------------------------------------------------------------------------------------

BOOL DrinkAction::Execute()
{
    ai->UseDrink();
    return TRUE;
}

BOOL DrinkAction::isUseful()
{
    return ai->GetManaPercent() < EAT_DRINK_PERCENT && !ai->HasAura("drink");
}

//---------------------------------------------------------------------------------------------------------------------

BOOL EatAction::Execute()
{
    ai->UseFood();
    return TRUE;
}

BOOL EatAction::isUseful()
{
    return ai->GetHealthPercent() < EAT_DRINK_PERCENT && !ai->HasAura("eat");
}
