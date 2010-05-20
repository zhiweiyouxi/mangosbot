#include "pchdef.h"
#include "HealthTriggers.h"

using namespace ai;

float HealthInRangeTrigger::GetValue()
{
	Unit* target = GetTarget();
	return target ? statsManager->GetHealthPercent(target) : 100.0f;
}

Unit* LowHealthTrigger::GetTarget()
{
	return targetManager->GetSelf();
}

Unit* PartyMemberLowHealthTrigger::GetTarget()
{
	return targetManager->GetPartyMinHealthPlayer();
}

Unit* TargetLowHealthTrigger::GetTarget()
{
	return targetManager->GetCurrentTarget();
}

bool PartyMemberDeadTrigger::IsActive()
{
	return targetManager->GetDeadPartyMember();
}
