#include "../../pchdef.h"
#include "../playerbot.h"

using namespace ai;
using namespace std;

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
        if (bot->CanUseItem(item->GetProto()))
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
    ListItemsVisitor() : IterateItemsVisitor(), first(true) {}

    virtual bool Visit(Item* item)
    {
        if (first) 
            first = false;
        else 
            out << ", ";

        const ItemPrototype *proto = item->GetProto();
        out << " |cffffffff|Hitem:" << proto->ItemId
            << ":0:0:0:0:0:0:0" << "|h[" << proto->Name1
            << "]|h|r";
        if (item->GetCount() > 1)
            out << "x" << item->GetCount();

        return true;
    }
    
    ostringstream out;

private:
    bool first;
};


AiInventoryManager::AiInventoryManager(PlayerbotAI* ai, AiManagerRegistry* aiRegistry) : AiManagerBase(ai, aiRegistry)
{
    lootManager = new LootManager(bot);
}

AiInventoryManager::~AiInventoryManager()
{
    delete lootManager;
}


void AiInventoryManager::IterateItems(IterateItemsVisitor* visitor)
{
    int count = 0;
    for (uint8 slot = INVENTORY_SLOT_ITEM_START; slot < INVENTORY_SLOT_ITEM_END; slot++)
    {
        Item* pItem = bot->GetItemByPos(INVENTORY_SLOT_BAG_0, slot);
        if (!pItem)
            continue;

        if (!visitor->Visit(pItem))
            return;
    }    

    for (uint8 bag = INVENTORY_SLOT_BAG_START; bag < INVENTORY_SLOT_BAG_END; ++bag)
    {
        const Bag* pBag = (Bag*) bot->GetItemByPos(INVENTORY_SLOT_BAG_0, bag);
        if (!pBag)
            continue;

        for (uint8 slot = 0; slot < pBag->GetBagSize(); ++slot)
        {
            Item* pItem = bot->GetItemByPos(bag, slot);
            if (!pItem)
                continue;

            if (!visitor->Visit(pItem))
                return;
        }
    }
}


void AiInventoryManager::UseItem(FindItemVisitor* visitor, const uint32 delay)
{
    IterateItems(visitor);
    Item* item = visitor->GetResult();
    if (!item) 
        return;
    
    UseItem(*item);
    if (delay) bot->GetPlayerbotAI()->SetNextCheckDelay(delay);
}

bool AiInventoryManager::HasItem(FindItemVisitor* visitor)
{
    IterateItems(visitor);
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
    QueryNamedItemCountVisitor visitor(name);
    IterateItems(&visitor);
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

void AiInventoryManager::findItemsInEquip(list<uint32>& itemIdSearchList, list<Item*>& foundItemList)
{
	for( uint8 slot=EQUIPMENT_SLOT_START; itemIdSearchList.size()>0 && slot<EQUIPMENT_SLOT_END; slot++ ) {
		Item* const pItem = bot->GetItemByPos( INVENTORY_SLOT_BAG_0, slot );
		if( !pItem )
			continue;

		for (list<uint32>::iterator it = itemIdSearchList.begin(); it != itemIdSearchList.end(); ++it)
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
	list<uint32> itemIds;
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
    uint64 vendorguid = bot->GetPlayerbotAI()->GetMaster()->GetSelection();
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
    if (bot->GetTrader() && bot->GetTrader()->GetGUID() == fromPlayer.GetGUID())
    {
        Trade(text.c_str());
    }
	else if (text == "report")
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
    IterateItems(&visitor);

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
    bot->GetSession()->HandleAcceptTradeOpcode(p);
}

void AiInventoryManager::BeginTrade()
{
    WorldPacket p;
    bot->GetSession()->HandleBeginTradeOpcode(p);

    aiRegistry->GetStatsManager()->ListStats();

    ListItemsVisitor visitor;
    IterateItems(&visitor);
    aiRegistry->GetSocialManager()->TellMaster(visitor.out.str().c_str());
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
    IterateItems(visitor);
    Item* item = visitor->GetResult();
    if (item) return TradeItem(*item, slot);
    return false;
}

bool AiInventoryManager::TradeItem(const Item& item, int8 slot)
{
    if (!bot->GetTrader() || item.IsInTrade() || (!item.CanBeTraded() && slot!=TRADE_SLOT_NONTRADED) )
        return false;

    int8 tradeSlot = -1;

    if( (slot>=0 && slot<TRADE_SLOT_COUNT) && bot->GetItemPosByTradeSlot(slot)==NULL_SLOT )
        tradeSlot = slot;
    else
    {
        for( uint8 i=0; i<TRADE_SLOT_TRADED_COUNT && tradeSlot==-1; i++ )
        {
            if( bot->GetItemPosByTradeSlot(i) == NULL_SLOT )
                tradeSlot = i;
        }
    }

    if( tradeSlot == -1 ) return false;

    WorldPacket* const packet = new WorldPacket(CMSG_SET_TRADE_ITEM, 3);
    *packet << (uint8) tradeSlot << (uint8) item.GetBagSlot()
        << (uint8) item.GetSlot();
    bot->GetSession()->QueuePacket(packet);
    return true;
}


