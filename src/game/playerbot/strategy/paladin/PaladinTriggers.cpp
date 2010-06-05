#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "PaladinTriggers.h"
#include "PaladinActions.h"

using namespace ai;

bool SealTrigger::IsActive() 
{
	Unit* target = GetTarget();
	return statsManager->GetManaPercent(targetManager->GetSelf()) > 30 && 
		!spellManager->HasAura("seal of justice", target) &&
		!spellManager->HasAura("seal of righteousness", target) &&
		!spellManager->HasAura("seal of light", target) &&
		!spellManager->HasAura("seal of wisdom", target);
}