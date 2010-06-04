#include "pchdef.h"
#include "PlayerbotMgr.h"
#include "PlayerbotAI.h"
#include "AiGroupStatsManager.h"
#include "AiSocialManager.h"
#include "AiStrategyManager.h"
#include "AiManagerRegistry.h"
#include "Spell.h"
#include "WorldPacket.h"

using namespace ai;
using namespace std;

void AiGroupStatsManager::findAllAttackers(Player *player, map<Unit*, ThreatManager*> &out)
{
    HostileReference *ref = player->getHostileRefManager().getFirst();
	while( ref )
	{
		ThreatManager *source = ref->getSource();
		Unit *attacker = source->getOwner();
		if (attacker && 
			!attacker->isDead() && 
			!attacker->IsPolymorphed() && 
			!attacker->isFrozen() && 
			!attacker->IsFriendlyTo(master))
		{
            out[attacker] = source;
		}
		ref = ref->next();
	}
}

void AiGroupStatsManager::findAllAttackers(map<Unit*, ThreatManager*> &out)
{
    Group* group = master->GetGroup();
    if (!group)
        return;
    
    for (GroupReference *gref = group->GetFirstMember(); gref; gref = gref->next()) 
    {
        Player* player = gref->getSource();
		findAllAttackers(player, out);
	}
}

int AiGroupStatsManager::GetAttackerCount(float distance)
{
    return attackers.size();
}

float AiGroupStatsManager::CalculateBalancePercent()
{
	uint32 playerLevel = 0,
		attackerLevel = 0;

	Group* group = master->GetGroup();
	if (group)
	{
		Group::MemberSlotList const& groupSlot = group->GetMemberSlots();
		for (Group::member_citerator itr = groupSlot.begin(); itr != groupSlot.end(); itr++)
		{
			Player *player = sObjectMgr.GetPlayer(uint64 (itr->guid));
			if( !player || !player->isAlive() || player == master)
				continue;

			playerLevel += player->getLevel();
		}
	}

	for (map<Unit*, ThreatManager*>::iterator i = attackers.begin(); i!=attackers.end(); i++)
	{  
		Unit* unit = i->first;
		if (unit || !unit->isAlive())
			continue;

		uint32 level = unit->getLevel();

		Creature* creature = dynamic_cast<Creature*>(unit);
		if (creature)
		{
			switch (creature->GetCreatureInfo()->rank) {
			case CREATURE_ELITE_RARE:
				level *= 2;
				break;
			case CREATURE_ELITE_ELITE:
				level *= 3;
				break;
			case CREATURE_ELITE_RAREELITE:
				level *= 5;
				break;
			case CREATURE_ELITE_WORLDBOSS:
				level *= 10;
				break;
			}
		}
		attackerLevel += level;
	}

	return !attackerLevel ? 100 : playerLevel * 100 / attackerLevel;

}

void AiGroupStatsManager::Update()
{
    attackers.clear();
    findAllAttackers(attackers);

    balancePercent = CalculateBalancePercent();
}

