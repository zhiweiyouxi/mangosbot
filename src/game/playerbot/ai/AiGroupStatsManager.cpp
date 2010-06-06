#include "../../pchdef.h"
#include "../playerbot.h"


using namespace ai;
using namespace std;

AiGroupStatsManager::AiGroupStatsManager(Player* master)
{
    this->master = master;
    attackerMapProvider = new AttackerMapProvider(master);
    balancePercent = new LazyCalculatedValue<float, AiGroupStatsManager>(this, &AiGroupStatsManager::CalculateBalancePercent);
}

AiGroupStatsManager::~AiGroupStatsManager()
{
    if (attackerMapProvider)
        delete attackerMapProvider;
    if (balancePercent)
        delete balancePercent;
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

    AttackerMap &v = attackerMapProvider->GetAttackers();

	for (AttackerMapIterator i = v.begin(); i!=v.end(); i++)
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
    attackerMapProvider->Reset();
    balancePercent->Reset();
}

