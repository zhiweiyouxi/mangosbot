#include "pchdef.h"
#include "GenericActions.h"
#include "PlayerbotAIFacade.h"

using namespace ai;

void FleeAction::Execute()
{
    // TODO: move away from battle
    ai->MoveToMaster();
}

void MeleeAction::Execute()
{
    ai->MoveToTarget();
}
