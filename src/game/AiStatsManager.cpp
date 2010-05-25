#include "pchdef.h"
#include "AiStatsManager.h"
#include "Spell.h"

using namespace ai;
using namespace std;

void AiStatsManager::findAllAttackers(HostileReference *ref, std::list<ThreatManager*> &out)
{
	while( ref )
	{
		ThreatManager *source = ref->getSource();
		Unit *attacker = source->getOwner();
		if (attacker && 
			!attacker->isDead() && 
			!attacker->IsPolymorphed() && 
			!attacker->isFrozen() && 
			!attacker->IsFriendlyTo(bot) && 
			bot->IsWithinLOSInMap(attacker))
		{
			bool found = FALSE;
			for (std::list<ThreatManager*>::iterator i = out.begin(); i != out.end(); i++)
			{
				ThreatManager *cur = *i;
				if (cur->getOwner() == attacker)
				{
					found = TRUE;
					break;
				}
			}
			if (!found)
				out.push_back(source);
		}
		ref = ref->next();
	}
}

void AiStatsManager::findAllAttackers(std::list<ThreatManager*> &out)
{
	if (bot->GetGroup())
	{
		GroupReference *gref = bot->GetGroup()->GetFirstMember();
		while( gref )
		{
			HostileReference *ref = gref->getSource()->getHostileRefManager().getFirst();
			findAllAttackers(ref, out);
			gref = gref->next();
		}
	}
}


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

int AiStatsManager::GetAttackerCount(float distance)
{
	std::list<ThreatManager*> attackers;
	findAllAttackers(attackers);

	int count = 0;
	for (std::list<ThreatManager*>::iterator i = attackers.begin(); i != attackers.end(); i++) {
		ThreatManager *cur = *i;
		if (bot->GetDistance(cur->getOwner()) <= distance) 
			count++;
	}
	return count;
}

int AiStatsManager::GetMyAttackerCount()
{
	int count = 0;

	HostileReference *ref = bot->getHostileRefManager().getFirst();
	while( ref )
	{
		ThreatManager *target = ref->getSource();
		Unit *attacker = target->getOwner();
		if (attacker && !attacker->isDead() && attacker->getVictim() == bot)
			count++;
		ref = ref->next();
	}
	return count;
}

float AiStatsManager::GetBalancePercent()
{
	uint32 playerLevel = 0,
		attackerLevel = 0;

	Group* group = ai->GetMaster()->GetGroup();
	if (group)
	{
		Group::MemberSlotList const& groupSlot = group->GetMemberSlots();
		for (Group::member_citerator itr = groupSlot.begin(); itr != groupSlot.end(); itr++)
		{
			Player *player = sObjectMgr.GetPlayer(uint64 (itr->guid));
			if( !player || !player->isAlive() || player == bot)
				continue;

			playerLevel += player->getLevel();
		}
	}

	std::list<ThreatManager*> attackers;
	findAllAttackers(attackers);
	for (std::list<ThreatManager*>::iterator i = attackers.begin(); i!=attackers.end(); i++)
	{  
		Unit* unit = (*i)->getOwner();
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

bool AiStatsManager::HasAggro(Unit* target)
{
	if (!target)
		return true;

	HostileReference *ref = bot->getHostileRefManager().getFirst();
	if (!ref)
		return true; // simulate as target is not atacking anybody yet

	while( ref )
	{
		ThreatManager *threatManager = ref->getSource();
		Unit *attacker = threatManager->getOwner();
		Unit *victim = attacker->getVictim();
		if (victim == bot && target == attacker)
			return true;
		ref = ref->next();
	}
	return false;
}


bool AiStatsManager::IsMounted()
{
	return bot->IsMounted();
}
