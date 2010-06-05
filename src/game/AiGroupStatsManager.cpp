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

AiGroupStatsManager::AiGroupStatsManager(Player* master)
{
    this->master = master;
    attackers = new LazyCalculatedValue<map<Unit*, ThreatManager*>, AiGroupStatsManager>(this, &AiGroupStatsManager::findAllAttackers);
    balancePercent = new LazyCalculatedValue<float, AiGroupStatsManager>(this, &AiGroupStatsManager::CalculateBalancePercent);
}

AiGroupStatsManager::~AiGroupStatsManager()
{
    if (balancePercent)
        delete balancePercent;
}

map<Unit*, ThreatManager*> AiGroupStatsManager::findAllAttackers()
{
    map<Unit*, ThreatManager*> out;

    Group* group = master->GetGroup();
    if (!group)
        return out;

    for (GroupReference *gref = group->GetFirstMember(); gref; gref = gref->next()) 
    {
        Player* player = gref->getSource();
        findAllAttackers(player, out);
    }
    
    return out;
}

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

int AiGroupStatsManager::GetAttackerCount(float distance)
{
    map<Unit*, ThreatManager*> &v = attackers->GetValue();
    return v.size();
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

    map<Unit*, ThreatManager*> &v = attackers->GetValue();

	for (map<Unit*, ThreatManager*>::iterator i = v.begin(); i!=v.end(); i++)
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
    attackers->Reset();
    balancePercent->Reset();
}

