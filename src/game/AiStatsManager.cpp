#include "pchdef.h"
#include "AiStatsManager.h"
#include "Spell.h"

using namespace ai;
using namespace std;

uint8 AiStatsManager::GetHealthPercent(const Unit& target)
{
	return (static_cast<float> (target.GetHealth()) / target.GetMaxHealth()) * 100;
}
