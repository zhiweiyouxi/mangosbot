#include "pchdef.h"
#include "AiStatsManager.h"
#include "Spell.h"

using namespace ai;
using namespace std;

uint8 AiStatsManager::GetHealthPercent(Unit* target)
{
    if (!target)
        return 100;
	return (static_cast<float> (target->GetHealth()) / target->GetMaxHealth()) * 100;
}

uint8 AiStatsManager::GetRage(Unit* target)
{
    if (!target)
        return 0;
	return (static_cast<float> (target->GetPower(POWER_RAGE)));
}

uint8 AiStatsManager::GetEnergy(Unit* target)
{
    if (!target)
        return 0;
	return (static_cast<float> (target->GetPower(POWER_ENERGY)));
}

uint8 AiStatsManager::GetManaPercent(Unit* target)
{
    if (!target)
        return 100;
	return (static_cast<float> (target->GetPower(POWER_MANA)) / target->GetMaxPower(POWER_MANA)) * 100;
}

uint8 AiStatsManager::GetComboPoints(Player* target) 
{
    if (!target)
        return 0;
	return target->GetComboPoints();
}

bool AiStatsManager::HasMana(Unit* target)
{
    if (!target)
        return false;
	// TODO: base value?
	return target->GetPower(POWER_MANA);
}

bool AiStatsManager::IsDead(Unit* target)
{
    if (!target)
        return false;
	return target->getDeathState() != ALIVE; 
}
