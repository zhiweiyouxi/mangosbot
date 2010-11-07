#include "../../pchdef.h"
#include "../playerbot.h"
#include "FindTargetStrategy.h"

using namespace ai;
using namespace std;

void FindTargetStrategy::CheckAttackers(Player* bot, Player* player)
{
	for (HostileReference* ref = player->getHostileRefManager().getFirst(); ref; ref = ref->next())
	{
        ThreatManager* threatManager = ref->getSource();
        Unit *attacker = threatManager->getOwner();
        if (attacker && alreadyChecked.find(attacker) == alreadyChecked.end() &&
            !attacker->isDead() && 
            !attacker->IsPolymorphed() && 
            !attacker->isFrozen() && 
            !attacker->IsFriendlyTo(bot) && 
            bot->IsWithinLOSInMap(attacker))
        {
		    CheckAttacker(bot, player, threatManager);
            alreadyChecked.insert(attacker);
            if (alreadyChecked.size() > 5)
                break;
        }
	}
}

void FindTargetStrategy::GetPlayerCount(Player* bot, Unit* creature, int* tankCount, int* dpsCount)
{
    if (tankCountCache.find(creature) != tankCountCache.end())
    {
        *tankCount = tankCountCache[creature];
        *dpsCount = dpsCountCache[creature];
        return;
    }

	*tankCount = 0;
	*dpsCount = 0;

    for (set<Unit*>::const_iterator i = creature->getAttackers().begin(); i != creature->getAttackers().end(); i++)
    {
		Unit* attacker = *i;
		if (!attacker || !attacker->isAlive() || attacker == bot)
			continue;

        Player* player = dynamic_cast<Player*>(attacker);
        if (!player)
            continue;

		if (aiRegistry->GetStatsManager()->IsTank(player))
			(*tankCount)++;
		
		if (aiRegistry->GetStatsManager()->IsDps(player))
			(*dpsCount)++;
	}

    tankCountCache[creature] = *tankCount;
    dpsCountCache[creature] = *dpsCount;
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


void FindTargetForCcStrategy::CheckAttacker(Player* bot, Player* player, ThreatManager* threatManager)
{
    float threat = threatManager->getThreat(bot);
    Unit* creature = threatManager->getOwner();
    
    uint8 health = aiRegistry->GetStatsManager()->GetHealthPercent(creature);
    if (health < 75)
        return;

    int tankCount, dpsCount;
    GetPlayerCount(bot, creature, &tankCount, &dpsCount);

    if (tankCount || dpsCount || !aiRegistry->GetSpellManager()->CanCastSpell(spell, creature))
        return;

    float minDistance = BOT_REACT_DISTANCE;
    Group* group = bot->GetGroup();
    if (group)
    {
        Group::MemberSlotList const& groupSlot = group->GetMemberSlots();
        for (Group::member_citerator itr = groupSlot.begin(); itr != groupSlot.end(); itr++)
        {
            Player *member = sObjectMgr.GetPlayer(uint64 (itr->guid));
            if( !member || !member->isAlive() || member == bot)
                continue;

            if (!aiRegistry->GetStatsManager()->IsTank(member))
                continue;

            float distance = member->GetDistance(creature);
            if (distance < minDistance)
                minDistance = distance;
        }
    }

    if (minDistance < 20.0f)
        return;

    if (!result || minDistance > maxDistance)
    {
        result = creature;
        maxDistance = minDistance;
    }
}

void FindCurrentCcTargetStrategy::CheckAttacker(Player* bot, Player* player, ThreatManager* threatManager)
{
    float threat = threatManager->getThreat(bot);
    Unit* creature = threatManager->getOwner();
    if (aiRegistry->GetSpellManager()->HasAura(spell, creature))
        result = creature;
}
