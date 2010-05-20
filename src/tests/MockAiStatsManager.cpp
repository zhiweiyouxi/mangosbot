#include "pch.h"
#include "MockAiStatsManager.h"
#include "MockedTargets.h"

using namespace std;
using namespace ai;

uint8 MockAiStatsManager::GetHealthPercent(Unit* target)
{
	return health[target];
}