#include "pch.h"
#include "MockAiTargetManager.h"
#include "MockedTargets.h"
#include "MockAiStatsManager.h"

using namespace std;
using namespace ai;

Unit* MockAiTargetManager::GetPartyMemberWithoutAura(const char* spell)
{
	Unit* target = MockedTargets::GetPartyMember();
	return spellManager->HasAura(spell, target) ? NULL : target;
}

Unit* MockAiTargetManager::GetPartyMinHealthPlayer()
{
	Unit* target = MockedTargets::GetPartyMember();
	return statsManager->GetHealthPercent(target) < 100.0f ? target : NULL;
}

Unit* MockAiTargetManager::GetDeadPartyMember()
{
	return deadPartyMember ? MockedTargets::GetPartyMember() : NULL;
}

Unit* MockAiTargetManager::GetPartyMemberToDispell(uint32 dispelType)
{
	Unit* target = MockedTargets::GetPartyMember();
	return spellManager->HasAuraToDispel(target, dispelType) ? target : NULL;
}

Unit* MockAiTargetManager::FindBiggerThreat()
{
    return MockedTargets::GetBiggerThreat();
}
Unit* MockAiTargetManager::FindLeastThreat()
{
    return MockedTargets::GetLeastThreat();
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
