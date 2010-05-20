#include "pchdef.h"
#include "GenericTriggers.h"
#include "CureTriggers.h"

using namespace ai;

Unit* NeedCureTrigger::GetTarget()
{
	return targetManager->GetSelf();
}

bool NeedCureTrigger::IsActive() 
{
	Unit* target = GetTarget();
	return target && spellManager->HasAuraToDispel(target, dispelType) && spellManager->CanCastSpell(spell, target);
}

Unit* TargetAuraDispelTrigger::GetTarget()
{
	return targetManager->GetCurrentTarget();
}

Unit* PartyMemberNeedCureTrigger::GetTarget()
{
	return targetManager->GetPartyMemberToDispell(dispelType);
}
