#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "MageTriggers.h"
#include "MageActions.h"

using namespace ai;

bool MageArmorTrigger::IsActive()
{
    Unit* target = GetTarget();
    return statsManager->GetManaPercent(targetManager->GetSelf()) > 30 && 
        !spellManager->HasAura("ice armor", target) &&
        !spellManager->HasAura("frost armor", target) &&
        !spellManager->HasAura("mage armor", target);
}