#include "../../pchdef.h"
#include "../playerbot.h"

using namespace ai;
using namespace std;

AiInventoryManager::AiInventoryManager(PlayerbotAI* ai, AiManagerRegistry* aiRegistry) : AiManagerBase(ai, aiRegistry)
{
    lootManager = new LootManager(bot);
}

AiInventoryManager::~AiInventoryManager()
{
    delete lootManager;
}


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

void AiInventoryManager::Buy(const char* link)
{
    list<uint32> itemIds;
    extractItemIds(link, itemIds);
    if (itemIds.empty()) 
        return;

    Player* master = bot->GetPlayerbotAI()->GetMaster();
    uint64 vendorguid = master->GetSelection();
    if (!vendorguid)
        return;

    for (list<uint32>::iterator i = itemIds.begin(); i != itemIds.end(); i++) 
    {
        bot->BuyItemFromVendor(vendorguid, *i, 1, NULL_BAG, NULL_SLOT);
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
	uint64 questRewarderGUID = bot->GetPlayerbotAI()->GetMaster()->GetSelection();
    bot->SetSelection(questRewarderGUID);
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
    else if (text.size() > 2 && text.substr(0, 2) == "b " || text.size() > 4 && text.substr(0, 7) == "buy ")
    {
        Buy(text.c_str());
    }
}

void AiInventoryManager::HandleBotOutgoingPacket(const WorldPacket& packet)
{
	switch (packet.GetOpcode())
	{
	case SMSG_INVENTORY_CHANGE_FAILURE:
		aiRegistry->GetSocialManager()->TellMaster("I can't use that.");
		break;
    }
}

void AiInventoryManager::HandleMasterIncomingPacket(const WorldPacket& packet)
{
    switch (packet.GetOpcode())
    {
    case CMSG_GAMEOBJ_REPORT_USE:
        WorldPacket p(packet);
        p.rpos(0); // reset reader
        uint64 guid;
        p >> guid;
        AddLoot(MAKE_NEW_GUID(guid, 0, HIGHGUID_GAMEOBJECT));
        break;
    }
}

void AiInventoryManager::QueryItemUsage(ItemPrototype const *item)
{
    if (!bot->CanUseItem(item))
        return;

    if (item->InventoryType == INVTYPE_NON_EQUIP)
        return;

    uint16 eDest;
    uint8 msg = bot->CanEquipNewItem(NULL_SLOT, eDest, item->ItemId, true);
    if( msg != EQUIP_ERR_OK )
        return;

    Item* existingItem = bot->GetItemByPos(eDest);
    if (!existingItem)
    {
        aiRegistry->GetSocialManager()->TellMaster("Equip");
        return;
    }

    bool equip = false;
    const ItemPrototype* oldItem = existingItem->GetProto();
    if (oldItem->ItemLevel < item->ItemLevel && oldItem->ItemId != item->ItemId)
    {
        switch (item->Class)
        {
        case ITEM_CLASS_ARMOR:
            equip = (oldItem->SubClass <= item->SubClass);
            break;
        default:
            equip = true;
        }
    }

    if (equip)
    {
        std::ostringstream out;
        out << "Replace +";
        out << (item->ItemLevel - oldItem->ItemLevel);
        out << " lvl";
        aiRegistry->GetSocialManager()->TellMaster(out.str().c_str());
    }
}

void AiInventoryManager::QueryItemsUsage(list<uint32> items) 
{
    for (list<uint32>::iterator i = items.begin(); i != items.end(); i++)
    {
        ItemPrototype const *item = sItemStorage.LookupEntry<ItemPrototype>(*i);
        QueryItemUsage(item);
    }
}

void AiInventoryManager::Query(const string& text)
{
    list<uint32> items; /* = */ extractItemIds(text, items);
    QueryItemsUsage(items);
}
