#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "MageActions.h"

using namespace ai;

Unit* CastPolymorphAction::GetTarget()
{
    return ai->GetTargetManager()->FindCcTarget(name);
}
