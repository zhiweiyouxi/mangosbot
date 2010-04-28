#include "pchdef.h"
#include "PaladinTriggers.h"
#include "PaladinActions.h"

using namespace ai;

BOOL SealTrigger::IsActive() 
{
	return ai->GetManaPercent() > 30 && 
		!ai->HasAura("seal of justice") &&
		!ai->HasAura("seal of righteousness") &&
		!ai->HasAura("seal of light") &&
		!ai->HasAura("seal of wisdom");
}