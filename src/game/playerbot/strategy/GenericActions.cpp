#include "../../pchdef.h"
#include "../playerbot.h"
#include "GenericActions.h"

using namespace ai;

ChangeCombatStrategyAction::ChangeCombatStrategyAction(AiManagerRegistry* const ai, const char* name) : Action(ai, "change strategy")
{
    this->name = name;
}

void ChangeCombatStrategyAction::Execute()
{
    ai->GetStrategyManager()->ChangeCombatStrategy(name.c_str());
}
