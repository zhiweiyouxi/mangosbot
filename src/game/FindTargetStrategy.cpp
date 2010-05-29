#include "pchdef.h"
#include "PlayerbotMgr.h"
#include "PlayerbotAI.h"
#include "FindTargetStrategy.h"
#include "AiStatsManager.h"
#include "Spell.h"
#include "SpellAuras.h"
#include "SpellMgr.h"
#include "AiManagerRegistry.h"
#include "WorldPacket.h"
#include "AiStrategyManager.h"

using namespace ai;
using namespace std;

void FindTargetStrategy::CheckAttackers(Player* bot, Player* player)
{
	for (HostileReference* ref = player->getHostileRefManager().getFirst(); ref; ref = ref->next())
	{
		CheckAttacker(bot, player, ref->getSource());
	}
}

void FindTargetStrategy::GetPlayerCount(Player* bot, Unit* creature, int* tankCount, int* dpsCount)
{
	tankCount = 0;
	dpsCount = 0;

    for (set<Unit*>::const_iterator i = creature->getAttackers().begin(); i != creature->getAttackers().end(); i++)
    {
		Unit* attacker = *i;
		if (!attacker || !attacker->isAlive() || !bot->IsWithinLOSInMap(attacker) || attacker == bot)
			continue;

        Player* player = dynamic_cast<Player*>(attacker);
        if (!player)
            continue;

		if (aiRegistry->GetStatsManager()->IsTank(player))
			tankCount++;
		
		if (aiRegistry->GetStatsManager()->IsDps(player))
			dpsCount++;
	}
}

void FindTargetForTankStrategy::CheckAttacker(Player* bot, Player* player, ThreatManager* threatManager)
{
	float threat = threatManager->getThreat(bot);
	Unit* creature = threatManager->getOwner();
	int tankCount, dpsCount;
	GetPlayerCount(bot, creature, &tankCount, &dpsCount);

	if (!result || 
        (bot->GetSelection() != creature->GetGUID() && minThreat >= threat && 
            (minTankCount >= tankCount || maxDpsCount <= dpsCount)))
	{
		minThreat = threat;
		minTankCount = tankCount;
		maxDpsCount = dpsCount;
		result = creature;
	}
}

void FindTargetForDpsStrategy::CheckAttacker(Player* bot, Player* player, ThreatManager* threatManager)
{
	float threat = threatManager->getThreat(bot);
	Unit* creature = threatManager->getOwner();
	int tankCount, dpsCount;
	GetPlayerCount(bot, creature, &tankCount, &dpsCount);

	if (!result || 
		minThreat >= threat && (maxTankCount <= tankCount || minDpsCount >= dpsCount))
	{
		minThreat = threat;
		maxTankCount = tankCount;
		minDpsCount = dpsCount;
		result = creature;
	}
}
