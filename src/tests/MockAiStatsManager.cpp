#include "pch.h"
#include "MockAiStatsManager.h"
#include "MockedTargets.h"

using namespace std;
using namespace ai;

uint8 MockAiStatsManager::GetHealthPercent(Unit* target)
{
	return health[target];
}

uint8 MockAiStatsManager::GetRage(Unit* target)
{
	return rage[target];
}

uint8 MockAiStatsManager::GetEnergy(Unit* target)
{
	return energy[target];
}

uint8 MockAiStatsManager::GetManaPercent(Unit* target)
{
	return mana[target];
}

bool MockAiStatsManager::HasMana(Unit* target)
{
	return GetManaPercent(target) > 0;
}

bool MockAiStatsManager::IsDead(Unit* target)
{
	return !GetHealthPercent(target);
}

uint8 MockAiStatsManager::GetComboPoints(Player* target)
{
	return comboPoints[target];
}