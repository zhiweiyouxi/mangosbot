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
	Unit* target = GetTargetManager()->GetCurrentTarget();
    if (!target)
        return;

	Player* bot = ai->GetPlayerBot();
	if (!bot->isInFrontInMap(target, 5.0f))
		bot->SetInFront(target);
    
    Attack(target); 
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


bool PlayerbotAIFacade::IsMounted()
{
    return ai->GetPlayerBot()->IsMounted();
}

void PlayerbotAIFacade::Emote(uint32 emote)
{
    ai->GetPlayerBot()->HandleEmoteCommand(emote);
}



