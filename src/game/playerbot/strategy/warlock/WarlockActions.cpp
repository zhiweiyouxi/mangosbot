#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "WarlockActions.h"

using namespace ai;

Unit* CastBanishAction::GetTarget()
{
    return ai->GetTargetManager()->FindCcTarget(name);
}