#include "../../pchdef.h"
#include "../playerbot.h"

using namespace ai;
using namespace std;

char * strstri (
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

uint32 extractMoney(const string& text)
{
    // if user specified money in ##g##s##c format
    string acum = "";
    uint32 copper = 0;
    for (uint8 i = 0; i < text.length(); i++)
    {
        if (text[i] == 'g')
        {
            copper += (atol(acum.c_str()) * 100 * 100);
            acum = "";
        }
        else if (text[i] == 'c')
        {
            copper += atol(acum.c_str());
            acum = "";
        }
        else if (text[i] == 's')
        {
            copper += (atol(acum.c_str()) * 100);
            acum = "";
        }
        else if (text[i] == ' ')
            break;
        else if (text[i] >= 48 && text[i] <= 57)
            acum += text[i];
        else
        {
            copper = 0;
            break;
        }
    }
    return copper;
}


class FindUsableItemVisitor : public FindItemVisitor {
public:
    FindUsableItemVisitor(Player* bot) : FindItemVisitor() 
    {
        this->bot = bot;
    }

    virtual bool Visit(Item* item)
    {
        if (bot->CanUseItem(item->GetProto()) == EQUIP_ERR_OK)
            return FindItemVisitor::Visit(item);

        return true;
    }

private:
    Player* bot;
};


class SellItemsVisitor : public IterateItemsVisitor
{
public:
    SellItemsVisitor(AiInventoryManager* inventoryManager) : IterateItemsVisitor() 
    {
        this->inventoryManager = inventoryManager;
    }

    virtual bool Visit(Item* item)
    {
        inventoryManager->Sell(item);
        return true;
    }

private:
    AiInventoryManager* inventoryManager;
};

class SellGrayItemsVisitor : public SellItemsVisitor
{
public:
    SellGrayItemsVisitor(AiInventoryManager* inventoryManager) : SellItemsVisitor(inventoryManager) {}

    virtual bool Visit(Item* item)
    {
        if (item->GetProto()->Quality != ITEM_QUALITY_POOR)
            return true;

        return SellItemsVisitor::Visit(item);
    }
};


class QueryItemCountVisitor : public IterateItemsVisitor 
{
public:
    QueryItemCountVisitor(uint32 itemId) 
    {
        count = 0;
        this->itemId = itemId;
    }

    virtual bool Visit(Item* item)
    {
        if (item->GetProto()->ItemId == itemId)
            count += item->GetCount();

        return true;
    }

    int GetCount() { return count; }

protected:
    int count;
    uint32 itemId;
};


class QueryNamedItemCountVisitor : public QueryItemCountVisitor 
{
public:
    QueryNamedItemCountVisitor(const char* name) : QueryItemCountVisitor(0)
    {
        this->name = name;
    }

    virtual bool Visit(Item* item)
    {
        const ItemPrototype* proto = item->GetProto();
        if (proto && proto->Name1 && strstri(proto->Name1, name))
            count += item->GetCount();

        return true;
    }

private:
    const char* name;
};



class FindPotionVisitor : public FindUsableItemVisitor {
public:
    FindPotionVisitor(Player* bot, uint32 spellId) : FindUsableItemVisitor(bot) 
    {
        this->spellId = spellId;
    }

    virtual bool Accept(const ItemPrototype* proto)
    {
        return proto->Class == ITEM_CLASS_CONSUMABLE && 
            proto->SubClass == ITEM_SUBCLASS_POTION &&    
            proto->Spells[0].SpellCategory == 4 && 
            proto->Spells[0].SpellId == spellId;
    }

private:
    uint32 spellId;
};

class FindFoodVisitor : public FindUsableItemVisitor {
public:
    FindFoodVisitor(Player* bot, uint32 spellCategory) : FindUsableItemVisitor(bot) 
    {
        this->spellCategory = spellCategory;
    }

    virtual bool Accept(const ItemPrototype* proto)
    {
        return proto->Class == ITEM_CLASS_CONSUMABLE && 
            proto->SubClass == ITEM_SUBCLASS_FOOD && 
            proto->Spells[0].SpellCategory == spellCategory;
    }

private:
    uint32 spellCategory;
};


class FindUsableNamedItemVisitor : public FindUsableItemVisitor {
public:
    FindUsableNamedItemVisitor(Player* bot, const char* name) : FindUsableItemVisitor(bot) 
    {
        this->name = name;
    }

    virtual bool Accept(const ItemPrototype* proto)
    {
        return proto && proto->Name1 && strstri(proto->Name1, name);
    }

private:
    const char* name;
};

class FindItemByIdVisitor : public FindItemVisitor {
public:
    FindItemByIdVisitor(uint32 id) : FindItemVisitor() 
    {
        this->id = id;
    }

    virtual bool Accept(const ItemPrototype* proto)
    {
        return proto->ItemId == id;
    }

private:
    uint32 id;
};

class ListItemsVisitor : public IterateItemsVisitor
{
public:
    ListItemsVisitor() : IterateItemsVisitor() {}

	map<uint32, int> items;

    virtual bool Visit(Item* item)
    {
		uint32 id = item->GetProto()->ItemId;
		
		if (items.find(id) == items.end())
			items[id] = 0;

		items[id] += item->GetCount();
        return true;
    }
};


AiInventoryManager::AiInventoryManager(PlayerbotAI* ai, AiManagerRegistry* aiRegistry) : AiManagerBase(ai, aiRegistry)
{
    lootManager = new LootManager(bot);
}

AiInventoryManager::~AiInventoryManager()
{
    delete lootManager;
}


void AiInventoryManager::IterateItems(IterateItemsVisitor* visitor, IterateItemsMask mask)
{
    if (mask & ITERATE_ITEMS_IN_BAGS)
        IterateItemsInBags(visitor);

    if (mask & ITERATE_ITEMS_IN_EQUIP)
        IterateItemsInEquip(visitor);
}

void AiInventoryManager::IterateItemsInBags(IterateItemsVisitor* visitor)
{
    for(int i = INVENTORY_SLOT_ITEM_START; i < INVENTORY_SLOT_ITEM_END; ++i)
        if (Item *pItem = bot->GetItemByPos(INVENTORY_SLOT_BAG_0, i))
			if (!visitor->Visit(pItem))
				return;

    for(int i = KEYRING_SLOT_START; i < CURRENCYTOKEN_SLOT_END; ++i)
        if (Item *pItem = bot->GetItemByPos(INVENTORY_SLOT_BAG_0, i))
			if (!visitor->Visit(pItem))
				return;

    for(int i = INVENTORY_SLOT_BAG_START; i < INVENTORY_SLOT_BAG_END; ++i)
        if (Bag *pBag = (Bag*)bot->GetItemByPos(INVENTORY_SLOT_BAG_0, i))
            for(uint32 j = 0; j < pBag->GetBagSize(); ++j)
                if (Item* pItem = pBag->GetItemByPos(j))
					if (!visitor->Visit(pItem))
						return;
}

void AiInventoryManager::IterateItemsInEquip(IterateItemsVisitor* visitor)
{
    for (uint8 slot = EQUIPMENT_SLOT_START; slot < EQUIPMENT_SLOT_END; slot++)
    {
        Item* const pItem = bot->GetItemByPos(INVENTORY_SLOT_BAG_0, slot);
        if(!pItem)
            continue;

        if (!visitor->Visit(pItem))
            return;
    }
}


void AiInventoryManager::UseItem(FindItemVisitor* visitor, const uint32 delay)
{
    IterateItems(visitor, ITERATE_ALL_ITEMS);
    Item* item = visitor->GetResult();
    if (!item) 
        return;
    
    UseItem(*item);
    if (delay) bot->GetPlayerbotAI()->SetNextCheckDelay(delay);
}

bool AiInventoryManager::HasItem(FindItemVisitor* visitor)
{
    IterateItems(visitor, ITERATE_ALL_ITEMS);
    return visitor->GetResult();
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

    WorldPacket* const packet = new WorldPacket(CMSG_USE_ITEM, 1 + 1 + 1 + 4 + 8 + 4 + 1 + 8 + 1);
    *packet << bagIndex << slot << cast_count << spellid << item_guid
        << glyphIndex << unk_flags;

    for (int i=0; i<MAX_ITEM_PROTO_SPELLS; i++)
    {
        uint32 spellId = item.GetProto()->Spells[i].SpellId;
        if (!spellId)
            continue;

        const SpellEntry* const pSpellInfo = sSpellStore.LookupEntry(spellId);
        Item* itemForSpell = aiRegistry->GetSpellManager()->FindItemForSpell(pSpellInfo);
        if (itemForSpell)
        {
            if (itemForSpell->GetEnchantmentId(TEMP_ENCHANTMENT_SLOT))
                continue;

            if (bot->GetTrader())
            {
                *packet << TARGET_FLAG_TRADE_ITEM << (uint8)1 << (uint64)TRADE_SLOT_NONTRADED;
            }
            else
            {
                *packet << TARGET_FLAG_ITEM;
                *packet << itemForSpell->GetPackGUID();
            }
            bot->GetSession()->QueuePacket(packet);
            return;
        }
    }

    *packet << TARGET_FLAG_SELF;
 	bot->GetSession()->QueuePacket(packet);
}

int AiInventoryManager::GetItemCount(const char* name) 
{
    QueryNamedItemCountVisitor visitor(name);
    IterateItems(&visitor, ITERATE_ALL_ITEMS);
    return visitor.GetCount();
}

void AiInventoryManager::extractItemIds(const string& text, list<uint32>& itemIds)
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
		string idC = text.substr(pos, endPos - pos);
		uint32 id = atol(idC.c_str());
		pos = endPos;
		if (id)
			itemIds.push_back(id);
	}
}

void AiInventoryManager::EquipItem(const char* link)
{
	list<uint32> ids; /* = */ extractItemIds(link, ids);
    
    for (list<uint32>::iterator i =ids.begin(); i != ids.end(); i++)
        EquipItem(&FindItemByIdVisitor(*i));
}

void AiInventoryManager::EquipItem(FindItemVisitor* visitor)
{
    IterateItems(visitor);
    Item *item = visitor->GetResult();
    if (item) EquipItem(*item);
}

void AiInventoryManager::EquipItem(Item& item)
{
	uint8 bagIndex = item.GetBagSlot();
	uint8 slot = item.GetSlot();

	WorldPacket* const packet = new WorldPacket(CMSG_AUTOEQUIP_ITEM, 2);
	*packet << bagIndex << slot;
	bot->GetSession()->QueuePacket(packet);
}


void AiInventoryManager::UnequipItem(const char* link)
{
    list<uint32> ids; /* = */ extractItemIds(link, ids);

    for (list<uint32>::iterator i =ids.begin(); i != ids.end(); i++)
        UnequipItem(&FindItemByIdVisitor(*i));
}

void AiInventoryManager::UnequipItem(FindItemVisitor* visitor)
{
    IterateItems(visitor, ITERATE_ALL_ITEMS);
    Item *item = visitor->GetResult();
    if (item) UnequipItem(*item);
}

void AiInventoryManager::UnequipItem(Item& item)
{
    uint8 bagIndex = item.GetBagSlot();
    uint8 slot = item.GetSlot();
    uint8 dstBag = NULL_BAG; 

    WorldPacket* const packet = new WorldPacket(CMSG_AUTOSTORE_BAG_ITEM, 3);
    *packet << bagIndex << slot << dstBag;
    bot->GetSession()->QueuePacket(packet);
}

void AiInventoryManager::UseItem(const char* link)
{
    list<uint32> ids; /* = */ extractItemIds(link, ids);
    for (list<uint32>::iterator i =ids.begin(); i != ids.end(); i++)
        UseItem(&FindItemByIdVisitor(*i));
}

void AiInventoryManager::ItemLocalization(string& itemName, const uint32 itemID)
{
	int loc = ai->GetMaster()->GetSession()->GetSessionDbLocaleIndex();
	wstring wnamepart;

	ItemLocale const *pItemInfo = sObjectMgr.GetItemLocale(itemID);
	if (pItemInfo)
	{
		if (pItemInfo->Name.size() > loc && !pItemInfo->Name[loc].empty())
		{
			const string name = pItemInfo->Name[loc];
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
    uint64 vendorguid = master->GetSelectionGuid().GetRawValue();
    if (!vendorguid)
        return;

    Creature *pCreature = bot->GetNPCIfCanInteractWith(vendorguid,UNIT_NPC_FLAG_VENDOR);
    VendorItemData const* tItems = pCreature->GetVendorTemplateItems();

    for (list<uint32>::iterator i = itemIds.begin(); i != itemIds.end(); i++) 
    {
    	for (uint32 slot = 0; slot < tItems->GetItemCount(); slot++)
    	{
    		if (tItems->GetItem(slot)->item == *i)
    	        bot->BuyItemFromVendorSlot(vendorguid, *i, slot, 1, NULL_BAG, NULL_SLOT);
    	}
    }
}

void AiInventoryManager::Reward(const char* link)
{
	list<uint32> itemIds;
	extractItemIds(link, itemIds);
	if (itemIds.empty()) 
		return;

	uint32 itemId = itemIds.front();
	bool wasRewarded = false;
	const ObjectGuid &questRewarder = bot->GetPlayerbotAI()->GetMaster()->GetSelectionGuid();
	uint64 questRewarderGUID = bot->GetPlayerbotAI()->GetMaster()->GetSelectionGuid().GetRawValue();
    bot->SetSelectionGuid(questRewarder);
	Object* pNpc = ObjectAccessor::GetGameObjectInWorld(questRewarder);
	if (!pNpc)
		pNpc = ObjectAccessor::GetUnitInWorld(*bot, questRewarder);

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

					string questTitle  = pQuest->GetTitle();
					aiRegistry->GetQuestManager()->QuestLocalization(questTitle, questID);
					string itemName = pRewardItem->Name1;
					ItemLocalization(itemName, pRewardItem->ItemId);

					ostringstream out;
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
	ostringstream out;

	for( map<uint32, uint32>::iterator itr=questItems.begin(); itr!=questItems.end(); ++itr )
	{
		const ItemPrototype * pItemProto = sObjectMgr.GetItemPrototype( itr->first );

		string itemName = pItemProto->Name1;
		ItemLocalization(itemName, pItemProto->ItemId);

		out << " " << itr->second << "x|cffffffff|Hitem:" << pItemProto->ItemId
			<< ":0:0:0:0:0:0:0" << "|h[" << itemName
			<< "]|h|r";
	}

	aiRegistry->GetSocialManager()->TellMaster( "Here's a list of all items I need for quests:" );
	aiRegistry->GetSocialManager()->TellMaster( out.str().c_str() );
}

void AiInventoryManager::Sell(string link) 
{
    if (link == "gray" || link == "*")
    {
        IterateItems(&SellGrayItemsVisitor(this));
        return;
    }

    list<uint32> ids; /* = */ extractItemIds(link, ids);
    for (list<uint32>::iterator i =ids.begin(); i != ids.end(); i++)
        Sell(&FindItemByIdVisitor(*i));
}

void AiInventoryManager::Sell(FindItemVisitor* visitor)
{
    IterateItems(visitor);
    Item* item = visitor->GetResult();
    if (item) Sell(item);
}

void AiInventoryManager::Sell(Item* item)
{
    uint64 vendorguid = bot->GetPlayerbotAI()->GetMaster()->GetSelectionGuid().GetRawValue();
    if (!vendorguid)
    {
        aiRegistry->GetSocialManager()->TellMaster("Select a vendor first");
        return;
    }

    uint64 itemguid = item->GetGUID();
    uint32 count = item->GetCount();

    WorldPacket p;
    p << vendorguid << itemguid << count;
    bot->GetSession()->HandleSellItemOpcode(p);
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
    else if (text.size() > 3 && text.substr(0, 3) == "ue " || text.size() > 6 && text.substr(0, 8) == "unequip ")
    {
        UnequipItem(text.c_str());
    }
	else if (text.size() > 2 && text.substr(0, 2) == "r " || text.size() > 7 && text.substr(0, 7) == "reward ")
	{
		Reward(text.c_str());
	}
    else if (text.size() > 2 && text.substr(0, 2) == "b " || text.size() > 4 && text.substr(0, 4) == "buy ")
    {
        Buy(text.c_str());
    }
    else if (text.size() > 2 && text.substr(0, 2) == "s " || text.size() > 4 && text.substr(0, 5) == "sell ")
    {
        string link = text.substr(text.find(" ") + 1);
        Sell(link.c_str());
    }
    else if (text.size() > 2 && text.substr(0, 2) == "c " || text.size() > 4 && text.substr(0, 6) == "count ")
    {
        ListCount(text.c_str());
    }
	else if (text.size() > 2 && text.substr(0, 2) == "l " || text.size() > 4 && text.substr(0, 5) == "loot ")
	{
		string strategy = text.substr(text.find(" ") + 1);
		if (strategy == "?")
		{
			ostringstream out;
			out << "Loot strategy: ";
			out << lootManager->GetLootStrategy();
			out << ", always loot items: ";

			for (set<uint32>::iterator i = lootManager->lootItems.begin(); i != lootManager->lootItems.end(); i++)
			{
				ItemPrototype const *proto = sItemStorage.LookupEntry<ItemPrototype>(*i);
				if (!proto)
					continue;

				out << " |cffffffff|Hitem:" << proto->ItemId
					<< ":0:0:0:0:0:0:0" << "|h[" << proto->Name1
					<< "]|h|r";
			}
			ai->GetAiRegistry()->GetSocialManager()->TellMaster(out.str().c_str());
		}
		else
		{
			list<uint32> items; /* = */ extractItemIds(text, items);

			if (items.size() == 0)
			{
				lootManager->SetLootStrategy(strategy);
				return;
			}

			bool remove = strategy.size() > 1 && strategy.substr(0, 1) == "-";
			for (list<uint32>::iterator i = items.begin(); i != items.end(); i++)
			{
				if (remove)
					lootManager->RemoveLootItem(*i);
				else
					lootManager->AddLootItem(*i);
			}
		}
	}    
    else if (bot->GetTrader() && bot->GetTrader()->GetGUID() == fromPlayer.GetGUID())
    {
        Trade(text.c_str());
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
    case SMSG_TRADE_STATUS:
        {
            if (bot->GetTrader() == NULL)
                break;

            WorldPacket p(packet);
            uint32 status;
            p >> status;
            p.clear();

            //4 == TRADE_STATUS_TRADE_ACCEPT
            if (status == 4)
                AcceptTrade();

            //1 == TRADE_STATUS_BEGIN_TRADE
            else if (status == 1)
                BeginTrade();

            return;
        }
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
        AddLoot(guid);
        break;
    }
}

void AiInventoryManager::QueryItemUsage(ItemPrototype const *item)
{
    if (bot->CanUseItem(item) != EQUIP_ERR_OK)
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
        ostringstream out;
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

void AiInventoryManager::QueryItemCount(ItemPrototype const * item) 
{
    QueryItemCountVisitor visitor(item->ItemId);
    IterateItems(&visitor, ITERATE_ALL_ITEMS);

    int count = visitor.GetCount();
    if (count)
    {
        ostringstream out;
        out << count << "x";
        aiRegistry->GetSocialManager()->TellMaster(out.str().c_str());
    }
}

void AiInventoryManager::ListCount(const char* link)
{
    list<uint32> items; /* = */ extractItemIds(link, items);
    for (list<uint32>::iterator i = items.begin(); i != items.end(); i++)
    {
        ItemPrototype const *item = sItemStorage.LookupEntry<ItemPrototype>(*i);
        QueryItemCount(item);
    }

}


void AiInventoryManager::UseHealingPotion() 
{
    UseItem(&FindPotionVisitor(bot, 441));
}

bool AiInventoryManager::HasHealingPotion() 
{
    return HasItem(&FindPotionVisitor(bot, 441));
}


void AiInventoryManager::UseManaPotion() 
{
    UseItem(&FindPotionVisitor(bot, 438));
}

bool AiInventoryManager::HasManaPotion() 
{
    return HasItem(&FindPotionVisitor(bot, 438));
}


void AiInventoryManager::UsePanicPotion() 
{
}

bool AiInventoryManager::HasPanicPotion() 
{
    return false;
}


void AiInventoryManager::UseFood() 
{
    UseItem(&FindFoodVisitor(bot, 11), 30);
}

bool AiInventoryManager::HasFood() 
{
    return HasItem(&FindFoodVisitor(bot, 11));
}


void AiInventoryManager::UseDrink() 
{
    UseItem(&FindFoodVisitor(bot, 59), 30);
}

bool AiInventoryManager::HasDrink() 
{
    return HasItem(&FindFoodVisitor(bot, 59));
}

void AiInventoryManager::FindAndUse(const char* item, uint8 delay)
{
    UseItem(&FindUsableNamedItemVisitor(bot, item), delay);
}






void AiInventoryManager::AcceptTrade()
{
    WorldPacket p;
	uint32 status = 0;
	p << status;
    bot->GetSession()->HandleAcceptTradeOpcode(p);
}

bool compare_items(const ItemPrototype *proto1, const ItemPrototype *proto2)
{
	if (proto1->Class != proto2->Class)
		return proto1->Class < proto2->Class;

	if (proto1->SubClass != proto2->SubClass)
		return proto1->SubClass < proto2->SubClass;

	if (proto1->Quality != proto2->Quality)
		return proto1->Quality < proto2->Quality;

	if (proto1->ItemLevel != proto2->ItemLevel)
		return proto1->ItemLevel < proto2->ItemLevel;

	return false;
}

void AiInventoryManager::BeginTrade()
{
    WorldPacket p;
    bot->GetSession()->HandleBeginTradeOpcode(p);

    aiRegistry->GetStatsManager()->ListStats();

    ListItemsVisitor visitor;
    IterateItems(&visitor);

	list<ItemPrototype const*> items;
	for (map<uint32, int>::iterator i = visitor.items.begin(); i != visitor.items.end(); i++)
	{
		items.push_back(sItemStorage.LookupEntry<ItemPrototype>(i->first));
	}
	items.sort(compare_items);

	ostringstream* out = NULL;

	bool first = false;
	uint32 oldClass = -1;
	for (list<ItemPrototype const*>::iterator i = items.begin(); i != items.end(); i++)
	{
		ItemPrototype const *proto = *i;
		
		if (proto->Class != oldClass)
		{
			oldClass = proto->Class;
			first = true;
			if (out) 
			{
				aiRegistry->GetSocialManager()->TellMaster(out->str().c_str());
				delete out;
			}
			out = new ostringstream();
		}

		if (first) 
			first = false;
		else 
			*out << ", ";

		char color[32];
		sprintf(color, "%x", ItemQualityColors[proto->Quality]);

		*out << " |c" << color << "|Hitem:" << proto->ItemId
			<< ":0:0:0:0:0:0:0" << "|h[" << proto->Name1
			<< "]|h|r";
		int count = visitor.items[proto->ItemId];
		if (count > 1)
			*out << "x" << count;
	}

	if (out) 
	{
		aiRegistry->GetSocialManager()->TellMaster(out->str().c_str());
		delete out;
	}
}



void AiInventoryManager::Trade(const char* text)
{
    uint32 copper = extractMoney(text);
    if (copper > 0)
    {
        WorldPacket* const packet = new WorldPacket(CMSG_SET_TRADE_GOLD, 4);
        *packet << copper;
        bot->GetSession()->QueuePacket(packet);
    }

    int8 slot = !strncmp(text, "nt ", 3) ? TRADE_SLOT_NONTRADED : -1;

    list<uint32> ids; /* = */ extractItemIds(text, ids);
    for (list<uint32>::iterator i = ids.begin(); i != ids.end(); i++)
        TradeItem(&FindItemByIdVisitor(*i), slot);
}

bool AiInventoryManager::TradeItem(FindItemVisitor *visitor, int8 slot)
{
    IterateItems(visitor, ITERATE_ALL_ITEMS);
    Item* item = visitor->GetResult();
    if (item) return TradeItem(*item, slot);
    return false;
}

bool AiInventoryManager::TradeItem(const Item& item, int8 slot)
{
	if (!bot->GetTrader() || item.IsInTrade() || (!item.CanBeTraded() && slot != TRADE_SLOT_NONTRADED))
		return false;

	int8 tradeSlot = -1;

	TradeData* pTrade = bot->GetTradeData();
	if ((slot >= 0 && slot < TRADE_SLOT_COUNT) && pTrade->GetItem(TradeSlots(slot)) == NULL)
		tradeSlot = slot;
	else
		for (uint8 i = 0; i < TRADE_SLOT_TRADED_COUNT && tradeSlot == -1; i++)
		{
			if (pTrade->GetItem(TradeSlots(i)) == NULL)
			{
				tradeSlot = i;
				// reserve trade slot to allow multiple items to be traded
				pTrade->SetItem(TradeSlots(i), const_cast<Item*>(&item));
			}
		}

	if (tradeSlot == -1) return false;

	WorldPacket* const packet = new WorldPacket(CMSG_SET_TRADE_ITEM, 3);
	*packet << (uint8) tradeSlot << (uint8) item.GetBagSlot()
			<< (uint8) item.GetSlot();
	bot->GetSession()->QueuePacket(packet);
	return true;
}


