#include "../../pchdef.h"
#include "../playerbot.h"

using namespace ai;
using namespace std;

Item* AiInventoryManager::FindUsableItem(bool predicate(const ItemPrototype*, const void*), const void* param, int *count/*=NULL*/)
{
    if (count) (*count) = 0;
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
	//if (! bot->IsStandState())
	//    bot->GetMotionMaster()->Clear();
}

void AiInventoryManager::ClearLoot()
{
	availableLoot.clear();
	currentLoot = 0;
}

void AiInventoryManager::AddLoot(uint64 guid)
{
	for (list<uint64>::iterator i = availableLoot.begin(); i != availableLoot.end(); i++)
	{
		if (*i == guid) 
			return;
	}

	availableLoot.push_front( guid );
	int lootSize = availableLoot.size();
	for (; lootSize>50; lootSize--) 
		availableLoot.pop_back();
}

bool AiInventoryManager::CanLoot()
{
	return !availableLoot.empty();
}

void AiInventoryManager::DoLoot()
{
	if (availableLoot.empty())
		return;

	if (!currentLoot)
	{
		currentLoot = availableLoot.front();
		availableLoot.pop_front();
		Creature *c = bot->GetMap()->GetCreature( currentLoot );
		if( !c || c->getDeathState()!=CORPSE || bot->GetDistance( c )>BOTLOOT_DISTANCE )
		{
			currentLoot = 0;
			return;
		}
		bot->GetMotionMaster()->MovePoint( c->GetMapId(), c->GetPositionX(), c->GetPositionY(), c->GetPositionZ() );
		return;
	}

	Creature *c = bot->GetMap()->GetCreature( currentLoot );
	if( !c || c->getDeathState()!=CORPSE || bot->GetDistance( c )>BOTLOOT_DISTANCE )
	{
		currentLoot = 0;
		return;
	}

	if( !bot->IsWithinDistInMap( c, INTERACTION_DISTANCE ) )
		return;

	// check for needed items
	bot->SendLoot( currentLoot, LOOT_CORPSE );
	Loot* loot = &c->loot;
	uint32 lootNum = loot->GetMaxSlotInLootFor( bot );
	for( uint32 l=0; l<lootNum; l++ )
	{
		QuestItem *qitem=0, *ffaitem=0, *conditem=0;
		LootItem *item = loot->LootItemInSlot( l, bot, &qitem, &ffaitem, &conditem );
		if( !item )
			continue;

		if( !qitem && item->is_blocked )
		{
			bot->SendLootRelease( bot->GetLootGUID() );
			continue;
		}

		// TODO change to AiQuestManager
		if (item->AllowedForPlayer(bot) && item->needs_quest)
		{
			ItemPosCountVec dest;
			if( bot->CanStoreNewItem( NULL_BAG, NULL_SLOT, dest, item->itemid, item->count ) == EQUIP_ERR_OK )
			{
				Item * newitem = bot->StoreNewItem( dest, item->itemid, true, item->randomPropertyId);

				if( qitem )
				{
					qitem->is_looted = true;
					if( item->freeforall || loot->GetPlayerQuestItems().size() == 1 )
						bot->SendNotifyLootItemRemoved( l );
					else
						loot->NotifyQuestItemRemoved( qitem->index );
				}
				else
				{
					if( ffaitem )
					{
						ffaitem->is_looted=true;
						bot->SendNotifyLootItemRemoved( l );
					}
					else
					{
						if( conditem )
							conditem->is_looted=true;
						loot->NotifyItemRemoved( l );
					}
				}
				if (!item->freeforall)
					item->is_looted = true;
				--loot->unlootedCount;
				bot->SendNewItem( newitem, uint32(item->count), false, false, true );
				bot->GetAchievementMgr().UpdateAchievementCriteria( ACHIEVEMENT_CRITERIA_TYPE_LOOT_ITEM, item->itemid, item->count );
			}
		}
	}
	// release loot
	if( uint64 lguid = bot->GetLootGUID() && bot->GetSession() )
		bot->GetSession()->DoLootRelease( lguid );
	//else if( !bot->GetSession() )
	//    sLog.outDebug( "[PlayerbotAI]: %s has no session. Cannot release loot!", bot->GetName() );

	bot->GetMotionMaster()->Clear();
	currentLoot = 0;
}


int AiInventoryManager::GetItemCount(const char* name) 
{
    int count; 
    if (!FindUsableItem(isTheSameName, (const void*)name, &count))
        return 0;
    return count; 
}

void AiInventoryManager::extractItemIds(const std::string& text, std::list<uint32>& itemIds)
{
	uint8 pos = 0;
	while (true)
	{
		int i = text.find("Hitem:", pos);
		if (i == -1)
			break;
		pos = i + 6;
		int endPos = text.find(':', pos);
		if (endPos == -1)
			break;
		std::string idC = text.substr(pos, endPos - pos);
		uint32 id = atol(idC.c_str());
		pos = endPos;
		if (id)
			itemIds.push_back(id);
	}
}

// TODO: rewrite
void AiInventoryManager::findItemsInInv(list<uint32>& itemIdSearchList, list<Item*>& foundItemList)
{

	// look for items in main bag
	for (uint8 slot = INVENTORY_SLOT_ITEM_START; itemIdSearchList.size() > 0 && slot < INVENTORY_SLOT_ITEM_END; ++slot)
	{
		Item* const pItem = bot->GetItemByPos(INVENTORY_SLOT_BAG_0, slot);
		if (!pItem)
			continue;

		for (std::list<uint32>::iterator it = itemIdSearchList.begin(); it != itemIdSearchList.end(); ++it)
		{
			if (pItem->GetProto()->ItemId != *it)
				continue;

			foundItemList.push_back(pItem);
			itemIdSearchList.erase(it);
			break;
		}
	}

	// for all for items in other bags
	for (uint8 bag = INVENTORY_SLOT_BAG_START; itemIdSearchList.size() > 0 && bag < INVENTORY_SLOT_BAG_END; ++bag)
	{
		Bag* const pBag = (Bag*) bot->GetItemByPos(INVENTORY_SLOT_BAG_0, bag);
		if (!pBag)
			continue;

		for (uint8 slot = 0; itemIdSearchList.size() > 0 && slot < pBag->GetBagSize(); ++slot)
		{
			Item* const pItem = bot->GetItemByPos(bag, slot);
			if (!pItem)
				continue;

			for (std::list<uint32>::iterator it = itemIdSearchList.begin(); it != itemIdSearchList.end(); ++it)
			{
				if (pItem->GetProto()->ItemId != *it)
					continue;

				foundItemList.push_back(pItem);
				itemIdSearchList.erase(it);
				break;
			}
		}
	}
}

void AiInventoryManager::findItemsInEquip(std::list<uint32>& itemIdSearchList, std::list<Item*>& foundItemList)
{
	for( uint8 slot=EQUIPMENT_SLOT_START; itemIdSearchList.size()>0 && slot<EQUIPMENT_SLOT_END; slot++ ) {
		Item* const pItem = bot->GetItemByPos( INVENTORY_SLOT_BAG_0, slot );
		if( !pItem )
			continue;

		for (std::list<uint32>::iterator it = itemIdSearchList.begin(); it != itemIdSearchList.end(); ++it)
		{
			if (pItem->GetProto()->ItemId != *it)
				continue;

			foundItemList.push_back(pItem);
			itemIdSearchList.erase(it);
			break;
		}
	}
}

void AiInventoryManager::EquipItem(const char* link)
{
	std::list<uint32> itemIds;
	std::list<Item*> itemList;
	extractItemIds(string(link), itemIds);
	findItemsInInv(itemIds, itemList);
	for (std::list<Item*>::iterator it = itemList.begin(); it != itemList.end(); ++it)
		EquipItem(**it);
}

void AiInventoryManager::EquipItem(Item& item)
{
	uint8 bagIndex = item.GetBagSlot();
	uint8 slot = item.GetSlot();

	WorldPacket* const packet = new WorldPacket(CMSG_AUTOEQUIP_ITEM, 2);
	*packet << bagIndex << slot;
	bot->GetSession()->QueuePacket(packet);
}

void AiInventoryManager::UseItem(const char* link)
{
	std::list<uint32> itemIds;
	std::list<Item*> itemList;
	extractItemIds(string(link), itemIds);
	findItemsInInv(itemIds, itemList);
	for (std::list<Item*>::iterator it = itemList.begin(); it != itemList.end(); ++it)
		UseItem(**it);
}

void AiInventoryManager::ItemLocalization(std::string& itemName, const uint32 itemID)
{
	int loc = ai->GetMaster()->GetSession()->GetSessionDbLocaleIndex();
	std::wstring wnamepart;

	ItemLocale const *pItemInfo = sObjectMgr.GetItemLocale(itemID);
	if (pItemInfo)
	{
		if (pItemInfo->Name.size() > loc && !pItemInfo->Name[loc].empty())
		{
			const std::string name = pItemInfo->Name[loc];
			if (Utf8FitTo(name, wnamepart))
				itemName = name.c_str();
		}
	}
}

void AiInventoryManager::Reward(const char* link)
{
	std::list<uint32> itemIds;
	extractItemIds(link, itemIds);
	if (itemIds.empty()) 
		return;

	uint32 itemId = itemIds.front();
	bool wasRewarded = false;
	uint64 questRewarderGUID = bot->GetSelection();
	Object* const pNpc = ObjectAccessor::GetObjectByTypeMask(*bot, questRewarderGUID, TYPEMASK_UNIT|TYPEMASK_GAMEOBJECT);
	if (!pNpc)
		return;

	QuestMenu& questMenu = bot->PlayerTalkClass->GetQuestMenu();
	for (uint32 iI = 0; !wasRewarded && iI < questMenu.MenuItemCount(); ++iI)
	{
		QuestMenuItem const& qItem = questMenu.GetItem(iI);

		uint32 questID = qItem.m_qId;
		Quest const* pQuest = sObjectMgr.GetQuestTemplate(questID);
		QuestStatus status = bot->GetQuestStatus(questID);

		// if quest is complete, turn it in
		if (status == QUEST_STATUS_COMPLETE && 
			! bot->GetQuestRewardStatus(questID) && 
			pQuest->GetRewChoiceItemsCount() > 1 &&
			bot->CanRewardQuest(pQuest, false))
		{
			for (uint8 rewardIdx=0; !wasRewarded && rewardIdx < pQuest->GetRewChoiceItemsCount(); ++rewardIdx)
			{
				ItemPrototype const * const pRewardItem = sObjectMgr.GetItemPrototype(pQuest->RewChoiceItemId[rewardIdx]);
				if (itemId == pRewardItem->ItemId)
				{
					bot->RewardQuest(pQuest, rewardIdx, pNpc, false);

					std::string questTitle  = pQuest->GetTitle();
					aiRegistry->GetQuestManager()->QuestLocalization(questTitle, questID);
					std::string itemName = pRewardItem->Name1;
					ItemLocalization(itemName, pRewardItem->ItemId);

					std::ostringstream out;
					out << "|cffffffff|Hitem:" << pRewardItem->ItemId << ":0:0:0:0:0:0:0" << "|h[" << itemName << "]|h|r rewarded";
					aiRegistry->GetSocialManager()->TellMaster(out.str().c_str());
					wasRewarded = true;
				}
			}
		}
	}
}

void AiInventoryManager::ListQuestItems()
{
	map<uint32, uint32> questItems = aiRegistry->GetQuestManager()->GetQuestItems();
	std::ostringstream out;

	for( map<uint32, uint32>::iterator itr=questItems.begin(); itr!=questItems.end(); ++itr )
	{
		const ItemPrototype * pItemProto = sObjectMgr.GetItemPrototype( itr->first );

		std::string itemName = pItemProto->Name1;
		ItemLocalization(itemName, pItemProto->ItemId);

		out << " " << itr->second << "x|cffffffff|Hitem:" << pItemProto->ItemId
			<< ":0:0:0:0:0:0:0" << "|h[" << itemName
			<< "]|h|r";
	}

	aiRegistry->GetSocialManager()->TellMaster( "Here's a list of all items I need for quests:" );
	aiRegistry->GetSocialManager()->TellMaster( out.str().c_str() );
}

void AiInventoryManager::HandleCommand(const string& text, Player& fromPlayer)
{
	if (text == "report")
	{
		ListQuestItems();
	}
	else if (text.size() > 2 && text.substr(0, 2) == "u " || text.size() > 4 && text.substr(0, 4) == "use ")
	{
		UseItem(text.c_str());
	}

	else if (text.size() > 2 && text.substr(0, 2) == "e " || text.size() > 6 && text.substr(0, 6) == "equip ")
	{
		EquipItem(text.c_str());
	}
	else if (text.size() > 2 && text.substr(0, 2) == "r " || text.size() > 7 && text.substr(0, 7) == "reward ")
	{
		Reward(text.c_str());
	}
}

void AiInventoryManager::HandleBotOutgoingPacket(const WorldPacket& packet)
{
	switch (packet.GetOpcode())
	{
	case SMSG_INVENTORY_CHANGE_FAILURE:
		{
			aiRegistry->GetSocialManager()->TellMaster("I can't use that.");
			return;
		}
	}

}
