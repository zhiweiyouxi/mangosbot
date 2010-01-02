#include "pchdef.h"
#include "PlayerbotAIFacade.h"
#include "DBCStructure.h"
#include "Spell.h"
#include "Group.h"

using namespace ai;

float PlayerbotAIFacade::GetDistanceToEnemy()
{
    Unit *target = ai->GetCurrentTarget();
    if (target && !target->isDead())
    {
        return ai->GetPlayerBot()->GetDistance(target); 
    }
    return 1e8;
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

void PlayerbotAIFacade::FindAndUse(BOOL predicate(const ItemPrototype*))
{
    Item* item = ai->FindUsableItem(predicate);
    if (item)
    {
        ai->UseItem(*item);
    }
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
    int count = 0;

    Unit* currentTarget = ai->GetCurrentTarget();
    if (currentTarget)
    {
        HostileReference *ref = ai->GetPlayerBot()->getHostileRefManager().getFirst();
        while( ref )
        {
            ThreatManager *target = ref->getSource();
            Unit *attacker = target->getOwner();
            if (attacker && !attacker->isDead())
                count++;
            ref = ref->next();
        }
    }
    return count;
}
