#include "pchdef.h"
#include "DBCStructure.h"
#include "Spell.h"
#include "Group.h"
#include "Creature.h"
#include "Unit.h"
#include "SpellAuras.h"
#include "PlayerbotAIFacade.h"

using namespace ai;

float PlayerbotAIFacade::GetDistanceToEnemy(float ifNoTarget)
{
    Unit *target = ai->GetCurrentTarget();
    if (target && !target->isDead())
    {
        return ai->GetPlayerBot()->GetDistance(target); 
    }
    return ifNoTarget;
}

BOOL PlayerbotAIFacade::canCastSpell( const char* name )
{
    uint32 spellid = ai->getSpellId(name);
    Player* bot = ai->GetPlayerBot();

    BOOL res = bot->HasSpell(spellid) && !bot->HasSpellCooldown(spellid);
    if (!res)
        return FALSE;

    SpellEntry const *spellInfo = sSpellStore.LookupEntry(spellid );
    Spell *spell = new Spell(bot, spellInfo, false );
    res = (spell->CheckPower() == SPELL_CAST_OK);
    delete spell;

    return res;
}

uint8 PlayerbotAIFacade::GetRage()
{
    return ai->GetRagePercent();
}

BOOL PlayerbotAIFacade::HasAura(const char* spell)
{
    return ai->HasAura(spell);
}

BOOL PlayerbotAIFacade::PetHasAura(const char* spell)
{
    return ai->HasAura(spell, *ai->GetPlayerBot()->GetPet());
}

BOOL PlayerbotAIFacade::TargetHasAura(const char* spell)
{
    return ai->HasAura(spell, *ai->GetCurrentTarget());
}

Player* PlayerbotAIFacade::findPlayer(BOOL predicate(Player*, FindPlayerParam&), void* param)
{
    Group* group = ai->GetMaster()->GetGroup();
    if (group)
    {
        Group::MemberSlotList const& groupSlot = group->GetMemberSlots();
        for (Group::member_citerator itr = groupSlot.begin(); itr != groupSlot.end(); itr++)
        {
            Player *player = sObjectMgr.GetPlayer(uint64 (itr->guid));
            if( !player || !player->isAlive() || player == ai->GetPlayerBot())
                continue;

            if (ai->GetPlayerBot()->GetDistance(player) > SPELL_DISTANCE)
                continue;

            FindPlayerParam pp; pp.ai = ai; pp.param = param;
            if (predicate(player, pp))
                return player;
        }
    }
    return NULL;
}

BOOL PlayerbotAIFacade::isPlayerWithoutAura(Player* player, FindPlayerParam &param )
{
    return !param.ai->HasAura((const char*)param.param, *player);
}

void PlayerbotAIFacade::RemoveAura(const char* name)
{
    uint32 spellid = ai->getSpellId(name);
    ai->GetPlayerBot()->RemoveAurasDueToSpell(spellid);
}

BOOL PlayerbotAIFacade::HasAggro()
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

BOOL PlayerbotAIFacade::FindAndUse(BOOL predicate(const ItemPrototype*), uint8 ignore_time)
{
    Item* item = ai->FindUsableItem(predicate);
    if (item)
    {
        ai->UseItem(*item);
        if (ignore_time)
            ai->SetIgnoreUpdateTime(ignore_time);
        return TRUE;
    }
    return FALSE;
}

void PlayerbotAIFacade::UseFood() 
{
    if (!FindAndUse(isFood, 30))
        ai->TellMaster("I need some food");
}

void PlayerbotAIFacade::UseDrink() 
{
    if (!FindAndUse(isDrink, 30))
        ai->TellMaster("I need some water");
}


BOOL PlayerbotAIFacade::isPanicPotion(const ItemPrototype* pItemProto)
{
    return FALSE; //(pItemProto->Class == ITEM_CLASS_CONSUMABLE && pItemProto->SubClass == ITEM_SUBCLASS_POTION;
}

BOOL PlayerbotAIFacade::isHealingPotion(const ItemPrototype* pItemProto)
{
    return pItemProto->Class == ITEM_CLASS_CONSUMABLE && pItemProto->SubClass == ITEM_SUBCLASS_POTION &&    
        pItemProto->Spells[0].SpellCategory == 4 && pItemProto->Spells[0].SpellId == 441;
}

BOOL PlayerbotAIFacade::isManaPotion(const ItemPrototype* pItemProto)
{
    return pItemProto->Class == ITEM_CLASS_CONSUMABLE && pItemProto->SubClass == ITEM_SUBCLASS_POTION &&    
        pItemProto->Spells[0].SpellCategory == 4 && pItemProto->Spells[0].SpellId == 438;
}

BOOL PlayerbotAIFacade::isFood(const ItemPrototype* pItemProto)
{
    return (pItemProto->Class == ITEM_CLASS_CONSUMABLE && pItemProto->SubClass == ITEM_SUBCLASS_FOOD && 
        pItemProto->Spells[0].SpellCategory == 11);
}

BOOL PlayerbotAIFacade::isDrink(const ItemPrototype* pItemProto)
{
    return (pItemProto->Class == ITEM_CLASS_CONSUMABLE && pItemProto->SubClass == ITEM_SUBCLASS_FOOD && 
        pItemProto->Spells[0].SpellCategory == 59);
}


Player* PlayerbotAIFacade::GetPartyMinHealthPlayer()
{
    uint8 minHealth = 100;
    Player* minHealthPlayer = NULL;

    Group* group = ai->GetMaster()->GetGroup();
    if (group)
    {
        Group::MemberSlotList const& groupSlot = group->GetMemberSlots();
        for (Group::member_citerator itr = groupSlot.begin(); itr != groupSlot.end(); itr++)
        {
            Player *player = sObjectMgr.GetPlayer(uint64 (itr->guid));
            if( !player || !player->isAlive() || player == ai->GetPlayerBot())
                continue;

            uint8 health = ai->GetHealthPercent(*player);
            if (!minHealthPlayer || minHealth > health)
            {
                minHealthPlayer = player;
                minHealth = health;
            }
        }
    }
    return minHealthPlayer;
}

uint8 PlayerbotAIFacade::GetPartyMinHealthPercent()
{
    Player* player = GetPartyMinHealthPlayer();
    return player ? ai->GetHealthPercent(*player) : 100;
}


int PlayerbotAIFacade::GetAttackerCount()
{
    std::list<ThreatManager*> attackers;
    findAllAttackers(attackers);
    return attackers.size();
}


int PlayerbotAIFacade::GetMyAttackerCount()
{
    int count = 0;

    HostileReference *ref = ai->GetPlayerBot()->getHostileRefManager().getFirst();
    while( ref )
    {
        ThreatManager *target = ref->getSource();
        Unit *attacker = target->getOwner();
        if (attacker && !attacker->isDead() && attacker->getVictim() == ai->GetPlayerBot())
            count++;
        ref = ref->next();
    }
    return count;
}

void PlayerbotAIFacade::findAllAttackers(HostileReference *ref, std::list<ThreatManager*> &out)
{
    while( ref )
    {
        ThreatManager *target = ref->getSource();
        Unit *attacker = target->getOwner();
        if (attacker && !attacker->isDead())
        {
            BOOL found = FALSE;
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
                out.push_back(target);
        }
        ref = ref->next();
    }
}

void PlayerbotAIFacade::findAllAttackers(std::list<ThreatManager*> &out)
{
    Player* bot = ai->GetPlayerBot();
    HostileReference *ref = bot->getHostileRefManager().getFirst();
    findAllAttackers(ref, out);
    
    ref = ai->GetMaster()->getHostileRefManager().getFirst();
    findAllAttackers(ref, out);

    if (ai->GetPlayerBot()->GetGroup())
    {
        GroupReference *gref = bot->GetGroup()->GetFirstMember();
        while( gref )
        {
            if( gref->getSource() == bot || gref->getSource() == ai->GetMaster() )
            {
                gref = gref->next();
                continue;
            }
            ref = gref->getSource()->getHostileRefManager().getFirst();
            findAllAttackers(ref, out);
            gref = gref->next();
        }
    }
}

void PlayerbotAIFacade::GoAway(float distance)
{
    Player* bot = ai->GetPlayerBot();

    float rx = bot->GetPositionX();
    float ry = bot->GetPositionY();
    float rz = bot->GetPositionZ();
    float maxDistance = 0;

    for (float r = distance; r>=ATTACK_DISTANCE; r -= ATTACK_DISTANCE)
    {
        for (float angle = 0; angle < 2*M_PI; angle += M_PI / 12)
        {
            float x = bot->GetPositionX() + cos(angle) * r;
            float y = bot->GetPositionY() + sin(angle) * r;
            float z = bot->GetPositionZ();

            if (!bot->IsWithinLOS(x, y, z))
                continue;

            std::list<ThreatManager*> attackers;
            findAllAttackers(attackers);
            for (std::list<ThreatManager*>::iterator i = attackers.begin(); i!=attackers.end(); i++)
            {  
                Unit* unit = (*i)->getOwner();

                float maxPlayerDistance = 0;
                if (ai->GetPlayerBot()->GetGroup())
                {
                    GroupReference *gref = bot->GetGroup()->GetFirstMember();
                    while( gref )
                    {
                        if( gref->getSource() == bot || gref->getSource() == ai->GetMaster() )
                        {
                            gref = gref->next();
                            continue;
                        }
                        Player* player = gref->getSource();
                        float playerDistance = player->GetDistance(x, y, z);
                        if (playerDistance < SPELL_DISTANCE && maxDistance < playerDistance)
                        {
                            maxDistance = playerDistance;
                            rx = x; ry = y;
                        }

                        gref = gref->next();
                    }
                }

                float distToCreature = unit->GetDistance(x, y, z);
                if (maxPlayerDistance < SPELL_DISTANCE && maxDistance < distToCreature)
                {
                    maxDistance = distToCreature;
                    rx = x; ry = y;
                }
            }
            if (ai->GetPlayerBot()->GetGroup())
            {
                GroupReference *gref = bot->GetGroup()->GetFirstMember();
                while( gref )
                {
                    if( gref->getSource() == bot || gref->getSource() == ai->GetMaster() )
                    {
                        gref = gref->next();
                        continue;
                    }
                    Player* player = gref->getSource();
                    float playerDistance = player->GetDistance(x, y, z);
                    if (playerDistance < SPELL_DISTANCE && maxDistance < playerDistance)
                    {
                        maxDistance = playerDistance;
                        rx = x; ry = y;
                    }

                    gref = gref->next();
                }
            }
        }
    }

    ai->MovementClear();
    bot->GetMotionMaster()->MovePoint(0, rx, ry, rz);
}

void PlayerbotAIFacade::Flee(float distance)
{
    Player* bot = ai->GetPlayerBot();

    float rx = bot->GetPositionX();
    float ry = bot->GetPositionY();
    float rz = bot->GetPositionZ();
    float maxDistance = 0;

    for (float r = distance; r>=ATTACK_DISTANCE; r -= ATTACK_DISTANCE)
    {
        for (float angle = 0; angle < 2*M_PI; angle += M_PI / 12)
        {
            float x = bot->GetPositionX() + cos(angle) * r;
            float y = bot->GetPositionY() + sin(angle) * r;
            float z = bot->GetPositionZ();

            if (!bot->IsWithinLOS(x, y, z))
                continue;

            std::list<ThreatManager*> attackers;
            findAllAttackers(attackers);
            for (std::list<ThreatManager*>::iterator i = attackers.begin(); i!=attackers.end(); i++)
            {  
                Unit* unit = (*i)->getOwner();
                
                float maxPlayerDistance = 0;
                if (ai->GetPlayerBot()->GetGroup())
                {
                    GroupReference *gref = bot->GetGroup()->GetFirstMember();
                    while( gref )
                    {
                        if( gref->getSource() == bot || gref->getSource() == ai->GetMaster() )
                        {
                            gref = gref->next();
                            continue;
                        }
                        Player* player = gref->getSource();
                        float playerDistance = player->GetDistance(x, y, z);
                        if (playerDistance > maxPlayerDistance)
                        {
                            maxPlayerDistance = playerDistance;
                        }

                        gref = gref->next();
                    }
                }

                float distToCreature = unit->GetDistance(x, y, z);
                if (maxPlayerDistance < SPELL_DISTANCE && maxDistance < distToCreature)
                {
                    maxDistance = distToCreature;
                    rx = x; ry = y;
                }
            }
        }
    }

    ai->MovementClear();
    bot->GetMotionMaster()->MovePoint(0, rx, ry, rz);
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
    if (target && !ai->HasAura("polymorph", *target))
        ai->Attack(target);
}

void PlayerbotAIFacade::AttackBiggerThreat()
{
    std::list<ThreatManager*> attackers;
    findAllAttackers(attackers);

    float maxThreat = 1e8;
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
    if (target && !ai->HasAura("polymorph", *target))
        ai->Attack(target);
}

BOOL PlayerbotAIFacade::IsMounted()
{
    return ai->GetPlayerBot()->IsMounted();
}

void PlayerbotAIFacade::Emote(uint32 emote)
{
    ai->GetPlayerBot()->HandleEmoteCommand(emote);
}

float PlayerbotAIFacade::GetFollowAngle() 
{
    Player* bot = ai->GetPlayerBot();
    if (ai->GetPlayerBot()->GetGroup())
    {
        GroupReference *gref = bot->GetGroup()->GetFirstMember();
        int index = 0;
        while( gref )
        {
            if( gref->getSource() == bot)
            {
                return M_PI / 2.5f * index;
            }
            gref = gref->next();
            index++;
        }
    }
    return 0;
}

Player* PlayerbotAIFacade::GetPartyMemberToDispell(uint32 dispelType)
{
    Group* group = ai->GetMaster()->GetGroup();
    if (group)
    {
        Group::MemberSlotList const& groupSlot = group->GetMemberSlots();
        for (Group::member_citerator itr = groupSlot.begin(); itr != groupSlot.end(); itr++)
        {
            Player *player = sObjectMgr.GetPlayer(uint64 (itr->guid));
            if( !player || !player->isAlive() || player == ai->GetPlayerBot())
                continue;

            if (HasAuraToDispel(player, dispelType))
                return player;
        }
    }
    return NULL;
}

BOOL PlayerbotAIFacade::HasAuraToDispel(Player* player, uint32 dispelType) 
{
    Unit::AuraMap &uAuras = player->GetAuras();
    for (Unit::AuraMap::const_iterator itr = uAuras.begin(); itr != uAuras.end(); ++itr)
    {
        const SpellEntry* entry = itr->second->GetSpellProto();
        uint32 spellId = entry->Id;
        if (IsPositiveSpell(spellId))
            continue;

        if (entry->Dispel == dispelType) {
            return TRUE;
        }
    }
    return FALSE;
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

    return playerLevel * 100 / attackerLevel;
}

