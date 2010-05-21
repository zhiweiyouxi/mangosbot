#include "pchdef.h"
#include "DBCStructure.h"
#include "Spell.h"
#include "Group.h"
#include "Creature.h"
#include "Unit.h"
#include "SpellAuras.h"
#include "PlayerbotAIFacade.h"
#include "FleeManager.h"
#include "PlayerbotAIBase.h"

using namespace ai;

void PlayerbotAIFacade::Melee() 
{ 
	Unit* target = ai->GetCurrentTarget();
	ai->Attack(target); 

	Player* bot = ai->GetPlayerBot();
	if (!bot->isInFrontInMap(target, 5.0f))
		bot->SetInFront(target);
}

bool PlayerbotAIFacade::HasAggro()
{
    Unit* currentTarget = ai->GetCurrentTarget();
    if (currentTarget)
    {
        HostileReference *ref = ai->GetPlayerBot()->getHostileRefManager().getFirst();
        if (!ref)
            return TRUE; // simulate as target is not atacking anybody yet
        while( ref )
        {
            ThreatManager *target = ref->getSource();
            Unit *attacker = target->getOwner();
            Unit *victim = attacker->getVictim();
            if (victim == ai->GetPlayerBot() && currentTarget == attacker)
                return TRUE;
            ref = ref->next();
        }
    }
    return FALSE;
}

bool PlayerbotAIFacade::FindAndUse(bool predicate(const ItemPrototype*, const void*), const void* param, uint8 ignore_time)
{
    Item* item = ai->FindUsableItem(predicate, param);
    if (item)
    {
        ai->UseItem(*item);
        if (ignore_time)
            ai->SetNextCheckDelay(ignore_time);
        return TRUE;
    }
    return FALSE;
}

void PlayerbotAIFacade::UseFood() 
{
    if (!FindAndUse(isFood, NULL, 30))
        ai->TellMaster("I need some food");
}

void PlayerbotAIFacade::UseDrink() 
{
    if (!FindAndUse(isDrink, NULL, 30))
        ai->TellMaster("I need some water");
}


bool PlayerbotAIFacade::isPanicPotion(const ItemPrototype* pItemProto, const void* param)
{
    return FALSE; //(pItemProto->Class == ITEM_CLASS_CONSUMABLE && pItemProto->SubClass == ITEM_SUBCLASS_POTION;
}

bool PlayerbotAIFacade::isHealingPotion(const ItemPrototype* pItemProto, const void* param)
{
    return pItemProto->Class == ITEM_CLASS_CONSUMABLE && pItemProto->SubClass == ITEM_SUBCLASS_POTION &&    
        pItemProto->Spells[0].SpellCategory == 4 && pItemProto->Spells[0].SpellId == 441;
}

bool PlayerbotAIFacade::isManaPotion(const ItemPrototype* pItemProto, const void* param)
{
    return pItemProto->Class == ITEM_CLASS_CONSUMABLE && pItemProto->SubClass == ITEM_SUBCLASS_POTION &&    
        pItemProto->Spells[0].SpellCategory == 4 && pItemProto->Spells[0].SpellId == 438;
}

bool PlayerbotAIFacade::isFood(const ItemPrototype* pItemProto, const void* param)
{
    return (pItemProto->Class == ITEM_CLASS_CONSUMABLE && pItemProto->SubClass == ITEM_SUBCLASS_FOOD && 
        pItemProto->Spells[0].SpellCategory == 11);
}

bool PlayerbotAIFacade::isDrink(const ItemPrototype* pItemProto, const void* param)
{
    return (pItemProto->Class == ITEM_CLASS_CONSUMABLE && pItemProto->SubClass == ITEM_SUBCLASS_FOOD && 
        pItemProto->Spells[0].SpellCategory == 59);
}


char * __cdecl strstri (
					   const char * str1,
					   const char * str2
					   )
{
	char *cp = (char *) str1;
	char *s1, *s2;

	if ( !*str2 )
		return((char *)str1);

	while (*cp)
	{
		s1 = cp;
		s2 = (char *) str2;

		while ( *s1 && *s2 && !(tolower(*s1)-tolower(*s2)) )
			s1++, s2++;

		if (!*s2)
			return(cp);

		cp++;
	}

	return(NULL);

}

bool PlayerbotAIFacade::isTheSameName(const ItemPrototype* pItemProto, const void* param)
{
	const char* name = (const char*)param;
	return pItemProto && pItemProto->Name1 && strstri(pItemProto->Name1, name);
}

int PlayerbotAIFacade::GetAttackerCount(float distance)
{
    std::list<ThreatManager*> attackers;
    findAllAttackers(attackers);
    
    Player* bot = ai->GetPlayerBot();
    int count = 0;
    for (std::list<ThreatManager*>::iterator i = attackers.begin(); i != attackers.end(); i++) {
        ThreatManager *cur = *i;
        if (bot->GetDistance(cur->getOwner()) <= distance) 
            count++;
    }
    return count;
}


int PlayerbotAIFacade::GetMyAttackerCount()
{
	Player* bot = ai->GetPlayerBot();
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

void PlayerbotAIFacade::findAllAttackers(HostileReference *ref, std::list<ThreatManager*> &out)
{
    Player* bot = ai->GetPlayerBot();
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

void PlayerbotAIFacade::findAllAttackers(std::list<ThreatManager*> &out)
{
    Player* bot = ai->GetPlayerBot();
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

void PlayerbotAIFacade::AttackLeastThreat()
{
    std::list<ThreatManager*> attackers;
    findAllAttackers(attackers);

    float minThreat = 1e8;
    Unit* target = NULL;
    for (std::list<ThreatManager*>::iterator i = attackers.begin(); i!=attackers.end(); i++)
    {  
        ThreatManager* attacker = *i;
        float threat = attacker->getThreat(ai->GetPlayerBot());
        if (!target || threat < minThreat)
        {
            minThreat = threat;
            target = attacker->getOwner();
        }
    }
    if (target)
        ai->Attack(target);
}

void PlayerbotAIFacade::AttackBiggerThreat()
{
    std::list<ThreatManager*> attackers;
    findAllAttackers(attackers);

    float maxThreat = -1;
    Unit* target = NULL;
    for (std::list<ThreatManager*>::iterator i = attackers.begin(); i!=attackers.end(); i++)
    {  
        ThreatManager* attacker = *i;
        float threat = attacker->getThreat(ai->GetPlayerBot());
        if (!target || threat > maxThreat)
        {
            maxThreat = threat;
            target = attacker->getOwner();
        }
    }
    if (target)
        ai->Attack(target);
}

bool PlayerbotAIFacade::IsMounted()
{
    return ai->GetPlayerBot()->IsMounted();
}

void PlayerbotAIFacade::Emote(uint32 emote)
{
    ai->GetPlayerBot()->HandleEmoteCommand(emote);
}



float PlayerbotAIFacade::GetBalancePercent()
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
            if( !player || !player->isAlive() || player == ai->GetPlayerBot())
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

