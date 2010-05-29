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

void FindTargetStrategy::CheckAttackers(Player* player)
{
	for (HostileReference* ref = player->getHostileRefManager().getFirst(); ref; ref = ref->next())
	{
		CheckAttacker(player, ref->getSource());
	}
}

void FindTargetStrategy::GetPlayerCount(Player* player, Unit* creature, int* tankCount, int* dpsCount)
{
	tankCount = 0;
	dpsCount = 0;

	Group* group = player->GetGroup();
	if (!group)
		return;

	for (GroupReference *gref = group->GetFirstMember(); gref; gref = gref->next()) 
	{
		Player* member = gref->getSource();
		if (!member || !member->isAlive() || !member->IsWithinLOSInMap(member) || member == player)
			continue;

		if (aiRegistry->GetStatsManager()->IsTank(member))
			tankCount++;
		
		if (aiRegistry->GetStatsManager()->IsDps(member))
			dpsCount++;
	}
}

void FindTargetForTankStrategy::CheckAttacker(Player* player, ThreatManager* threatManager)
{
	float threat = threatManager->getThreat(player);
	Unit* creature = threatManager->getOwner();
	int tankCount, dpsCount;
	GetPlayerCount(player, creature, &tankCount, &dpsCount);

	if (!result || 
		minThreat >= threat && (minTankCount >= tankCount || maxDpsCount <= dpsCount))
	{
		minThreat = threat;
		minTankCount = tankCount;
		maxDpsCount = dpsCount;
		result = creature;
	}
}

void FindTargetForDpsStrategy::CheckAttacker(Player* player, ThreatManager* threatManager)
{
	float threat = threatManager->getThreat(player);
	Unit* creature = threatManager->getOwner();
	int tankCount, dpsCount;
	GetPlayerCount(player, creature, &tankCount, &dpsCount);

	if (!result || 
		minThreat >= threat && (maxTankCount <= tankCount || minDpsCount >= dpsCount))
	{
		minThreat = threat;
		maxTankCount = tankCount;
		minDpsCount = dpsCount;
		result = creature;
	}
}
