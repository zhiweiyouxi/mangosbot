#include "pch.h"
#include "aitest.h"
#include "MockAiTargetManager.h"
#include "MockedTargets.h"
#include "MockAiStatsManager.h"

using namespace std;
using namespace ai;

Unit* MockAiTargetManager::GetPartyMemberWithoutAura(const char* spell)
{
	Unit* target = MockedTargets::GetPartyMember();
	return aiRegistry->GetSpellManager()->HasAura(spell, target) ? NULL : target;
}

Unit* MockAiTargetManager::GetPartyMinHealthPlayer()
{
	Unit* target = MockedTargets::GetPartyMember();
	return aiRegistry->GetStatsManager()->GetHealthPercent(target) < 100.0f ? target : NULL;
}

Unit* MockAiTargetManager::GetDeadPartyMember()
{
	return deadPartyMember ? MockedTargets::GetPartyMember() : NULL;
}

Unit* MockAiTargetManager::GetPartyMemberToDispell(uint32 dispelType)
{
	Unit* target = MockedTargets::GetPartyMember();
	return aiRegistry->GetSpellManager()->HasAuraToDispel(target, dispelType) ? target : NULL;
}

Unit* MockAiTargetManager::FindTargetForTank()
{
    return MockedTargets::GetTargetForTank();
}
Unit* MockAiTargetManager::FindTargetForDps()
{
    return MockedTargets::GetTargetForDps();
}

Unit* MockAiTargetManager::GetCurrentTarget()
{
	return haveTarget ? MockedTargets::GetCurrentTarget() : NULL;
}

Player* MockAiTargetManager::GetSelf()
{
	return MockedTargets::GetSelf();
}

Player* MockAiTargetManager::GetMaster()
{
	return MockedTargets::GetMaster();
}

Unit* MockAiTargetManager::GetPet()
{
	return hasPet ? MockedTargets::GetPet() : NULL;
}
