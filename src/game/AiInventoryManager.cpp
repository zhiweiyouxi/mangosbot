#include "pchdef.h"
#include "AiInventoryManager.h"
#include "AiManagerRegistry.h"
#include "Spell.h"
#include "WorldPacket.h"

using namespace ai;
using namespace std;

Item* AiInventoryManager::FindUsableItem(bool predicate(const ItemPrototype*, const void*), const void* param, int *count/*=NULL*/)
{
	Item* found = NULL;

	// list out items in main backpack
	for (uint8 slot = INVENTORY_SLOT_ITEM_START; slot < INVENTORY_SLOT_ITEM_END; slot++)
	{
		Item* const pItem = bot->GetItemByPos(INVENTORY_SLOT_BAG_0, slot);
		if (pItem)
		{
			const ItemPrototype* const pItemProto = pItem->GetProto();

			if (!pItemProto || !bot->CanUseItem(pItemProto))
				continue;

			if (predicate(pItemProto, param)) {
				if (!found) 
					found = pItem;

				if (count) 
					(*count)++;
				else 
					return found;
			}
		}
	}
	// list out items in other removable backpacks
	for (uint8 bag = INVENTORY_SLOT_BAG_START; bag < INVENTORY_SLOT_BAG_END; ++bag)
	{
		const Bag* const pBag = (Bag*) bot->GetItemByPos(INVENTORY_SLOT_BAG_0, bag);
		if (pBag)
		{
			for (uint8 slot = 0; slot < pBag->GetBagSize(); ++slot)
			{
				Item* const pItem = bot->GetItemByPos(bag, slot);
				if (pItem)
				{
					const ItemPrototype* const pItemProto = pItem->GetProto();

					if (!pItemProto || !bot->CanUseItem(pItemProto))
						continue;

					if (predicate(pItemProto, param)) {
						if (!found) 
							found = pItem;

						if (count) 
							(*count)++;
						else 
							return found;
					}
				}
			}
		}
	}
	return found;
}


bool AiInventoryManager::FindAndUse(bool predicate(const ItemPrototype*, const void*), const void* param, uint8 ignore_time)
{
	Item* item = FindUsableItem(predicate, param);
	if (item)
	{
		UseItem(*item);
		if (ignore_time)
			ai->SetNextCheckDelay(ignore_time);
		return TRUE;
	}
	return FALSE;
}

void AiInventoryManager::UseFood() 
{
	FindAndUse(isFood, NULL, 30);
}

void AiInventoryManager::UseDrink() 
{
	FindAndUse(isDrink, NULL, 30);
}


bool AiInventoryManager::isPanicPotion(const ItemPrototype* pItemProto, const void* param)
{
	return FALSE; //(pItemProto->Class == ITEM_CLASS_CONSUMABLE && pItemProto->SubClass == ITEM_SUBCLASS_POTION;
}

bool AiInventoryManager::isHealingPotion(const ItemPrototype* pItemProto, const void* param)
{
	return pItemProto->Class == ITEM_CLASS_CONSUMABLE && pItemProto->SubClass == ITEM_SUBCLASS_POTION &&    
		pItemProto->Spells[0].SpellCategory == 4 && pItemProto->Spells[0].SpellId == 441;
}

bool AiInventoryManager::isManaPotion(const ItemPrototype* pItemProto, const void* param)
{
	return pItemProto->Class == ITEM_CLASS_CONSUMABLE && pItemProto->SubClass == ITEM_SUBCLASS_POTION &&    
		pItemProto->Spells[0].SpellCategory == 4 && pItemProto->Spells[0].SpellId == 438;
}

bool AiInventoryManager::isFood(const ItemPrototype* pItemProto, const void* param)
{
	return (pItemProto->Class == ITEM_CLASS_CONSUMABLE && pItemProto->SubClass == ITEM_SUBCLASS_FOOD && 
		pItemProto->Spells[0].SpellCategory == 11);
}

bool AiInventoryManager::isDrink(const ItemPrototype* pItemProto, const void* param)
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

bool AiInventoryManager::isTheSameName(const ItemPrototype* pItemProto, const void* param)
{
	const char* name = (const char*)param;
	return pItemProto && pItemProto->Name1 && strstri(pItemProto->Name1, name);
}

void AiInventoryManager::UseItem(Item& item)
{
	uint8 bagIndex = item.GetBagSlot();
	uint8 slot = item.GetSlot();
	uint8 cast_count = 1;
	uint32 spellid = 0; // only used in combat
	uint64 item_guid = item.GetGUID();
	uint32 glyphIndex = 0; // ??
	uint8 unk_flags = 0; // not 0x02

	// create target data
	// note other targets are possible but not supported at the moment
	// see SpellCastTargets::read in Spell.cpp to see other options
	// for setting target

	uint32 target = TARGET_FLAG_SELF;

	WorldPacket* const packet = new WorldPacket(CMSG_USE_ITEM, 1 + 1 + 1 + 4 + 8 + 4 + 1);
	*packet << bagIndex << slot << cast_count << spellid << item_guid
		<< glyphIndex << unk_flags << target;
	bot->GetSession()->QueuePacket(packet); // queue the packet to get around race condition

	// certain items cause player to sit (food,drink)
	// tell bot to stop following if this is the case
	// (doesn't work since we queued the packet!)
	// maybe its not needed???
	//if (! m_bot->IsStandState())
	//    m_bot->GetMotionMaster()->Clear();
}