#include "pchdef.h"
#include "PlayerbotAIFacade.h"
#include "DBCStructure.h"
#include "Spell.h"

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

void PlayerbotAIFacade::UseHealingPotion() 
{
    Item* item = ai->FindUsableItem(isHealingPotion);
    if (item)
        ai->UseItem(*item);
}

void PlayerbotAIFacade::UseManaPotion() 
{
    Item* item = ai->FindUsableItem(isManaPotion);
    if (item)
        ai->UseItem(*item);
}

void PlayerbotAIFacade::UsePanicPotion() 
{
    Item* item = ai->FindUsableItem(isManaPotion);
    if (item)
        ai->UseItem(*item);
}


BOOL PlayerbotAIFacade::isPanicPotion(const ItemPrototype* pItemProto)
{
    return FALSE; //(pItemProto->Class == ITEM_CLASS_CONSUMABLE && pItemProto->SubClass == ITEM_SUBCLASS_POTION;
}

BOOL PlayerbotAIFacade::isHealingPotion(const ItemPrototype* pItemProto)
{
    return FALSE; //(pItemProto->Class == ITEM_CLASS_CONSUMABLE && pItemProto->SubClass == ITEM_SUBCLASS_POTION;
}

BOOL PlayerbotAIFacade::isManaPotion(const ItemPrototype* pItemProto)
{
    return FALSE; //(pItemProto->Class == ITEM_CLASS_CONSUMABLE && pItemProto->SubClass == ITEM_SUBCLASS_POTION;
}
