#include "pchdef.h"
#include "PaladinTriggers.h"
#include "PaladinActions.h"

using namespace ai;

bool SealTrigger::IsActive() 
{
	Unit* target = GetTarget();
	return ai->GetManaPercent() > 30 && 
		!spellManager->HasAura("seal of justice", target) &&
		!spellManager->HasAura("seal of righteousness", target) &&
		!spellManager->HasAura("seal of light", target) &&
		!spellManager->HasAura("seal of wisdom", target);
}