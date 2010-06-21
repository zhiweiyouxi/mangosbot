#include "../../pchdef.h"
#include "../playerbot.h"

using namespace ai;
using namespace std;

void AiSocialManager::Emote(uint32 emote)
{
	bot->HandleEmoteCommand(emote);
}

void AiSocialManager::TellMaster(const char* text)
{
	WorldPacket data(SMSG_MESSAGECHAT, 200);
	bot->BuildPlayerChat(&data, CHAT_MSG_WHISPER, text, LANG_UNIVERSAL);
	ai->GetMaster()->GetSession()->SendPacket(&data);
	bot->HandleEmoteCommand(EMOTE_ONESHOT_TALK);
}

// extracts currency in #g#s#c format
uint32 AiSocialManager::extractMoney(const std::string& text)
{
	// if user specified money in ##g##s##c format
	std::string acum = "";
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

void AiSocialManager::Trade(const char* text)
{
	uint32 copper = extractMoney(text);
	if (copper > 0)
	{
		WorldPacket* const packet = new WorldPacket(CMSG_SET_TRADE_GOLD, 4);
		*packet << copper;
		bot->GetSession()->QueuePacket(packet);
	}


    std::list<uint32> itemIds;
    aiRegistry->GetInventoryManager()->extractItemIds(text, itemIds);
	if( !strncmp( text, "nt ", 3 ) )
    {
        if( itemIds.size() > 1 )
            TellMaster("There is only one 'Will not be traded' slot. Shift-click just one item, please!");
        else
        {
            std::list<Item*> itemList;
            aiRegistry->GetInventoryManager()->findItemsInEquip( itemIds, itemList );
            aiRegistry->GetInventoryManager()->findItemsInInv( itemIds, itemList );
            if( itemList.size()>0 )
                TradeItem( (**itemList.begin()), TRADE_SLOT_NONTRADED );
            else
                TellMaster( "I do not have this item equipped or in my bags!");
        }
    }
    else
    {
        std::list<Item*> itemList;
        aiRegistry->GetInventoryManager()->findItemsInInv(itemIds, itemList);
        for (std::list<Item*>::iterator it = itemList.begin(); it != itemList.end(); ++it)
            TradeItem(**it);
    }
}

bool AiSocialManager::TradeItem(const Item& item, int8 slot)
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

void AiSocialManager::LeaveGroup()
{
	Group* group = bot->GetGroup();
	if (group) 
		group->RemoveMember(bot->GetGUID(), 0);
}

void AiSocialManager::AcceptInvitation()
{
	Group* grp = bot->GetGroupInvite();
	if (!grp)
		return;

	Player* inviter = sObjectMgr.GetPlayer(grp->GetLeaderGUID());
	if (!inviter)
		return;

	WorldPacket p;
	bot->GetSession()->HandleGroupAcceptOpcode(p);
}

void AiSocialManager::AcceptTrade()
{
	WorldPacket p;
	bot->GetSession()->HandleAcceptTradeOpcode(p);
}

void AiSocialManager::BeginTrade()
{
	WorldPacket p;
	bot->GetSession()->HandleBeginTradeOpcode(p);

	// calculate how much money bot has
	uint32 copper = bot->GetMoney();
	uint32 gold = uint32(copper / 10000);
	copper -= (gold * 10000);
	uint32 silver = uint32(copper / 100);
	copper -= (silver * 100);

	// send bot the message
	std::ostringstream whisper;
	whisper << "I have |cff00ff00" << gold
		<< "|r|cfffffc00g|r|cff00ff00" << silver
		<< "|r|cffcdcdcds|r|cff00ff00" << copper
		<< "|r|cffffd333c|r" << " and the following items:";
	TellMaster(whisper.str().c_str());

	// list out items in main backpack
	for (uint8 slot = INVENTORY_SLOT_ITEM_START; slot < INVENTORY_SLOT_ITEM_END; slot++)
	{
		const Item* const pItem = bot->GetItemByPos(INVENTORY_SLOT_BAG_0, slot);
		if (pItem && pItem->CanBeTraded())
		{
			const ItemPrototype* const pItemProto = pItem->GetProto();

			std::string itemName = pItemProto->Name1;
			aiRegistry->GetInventoryManager()->ItemLocalization(itemName, pItemProto->ItemId);

			std::ostringstream out;
			out << " |cffffffff|Hitem:" << pItemProto->ItemId
				<< ":0:0:0:0:0:0:0" << "|h[" << itemName << "]|h|r";
			if (pItem->GetCount() > 1)
				out << "x" << pItem->GetCount() << ' ';
			TellMaster(out.str().c_str());
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
				const Item* const pItem = bot->GetItemByPos(bag, slot);
				if (pItem && pItem->CanBeTraded())
				{
					const ItemPrototype* const pItemProto = pItem->GetProto();

					std::string itemName = pItemProto->Name1;
					aiRegistry->GetInventoryManager()->ItemLocalization(itemName, pItemProto->ItemId);

					// item link format: http://www.wowwiki.com/ItemString
					// itemId, enchantId, jewelId1, jewelId2, jewelId3, jewelId4, suffixId, uniqueId
					std::ostringstream out;
					out << " |cffffffff|Hitem:" << pItemProto->ItemId
						<< ":0:0:0:0:0:0:0" << "|h[" << itemName
						<< "]|h|r";
					if (pItem->GetCount() > 1)
						out << "x" << pItem->GetCount() << ' ';
					TellMaster(out.str().c_str());
				}
			}
		}
	}
}

void AiSocialManager::HandleCommand(const string& text, Player& fromPlayer)
{
	if (bot->GetTrader() && bot->GetTrader()->GetGUID() == fromPlayer.GetGUID())
	{
		Trade(text.c_str());
	}
	else if (text == "leave")
	{
		LeaveGroup();
	}
}

void AiSocialManager::HandleBotOutgoingPacket(const WorldPacket& packet)
{
	switch (packet.GetOpcode())
	{
		// If the leader role was given to the bot automatically give it to the master
		// if the master is in the group, otherwise leave group
	case SMSG_GROUP_SET_LEADER:
		{
			WorldPacket p(packet);
			std::string name;
			p >> name;
			if (bot->GetGroup() && name == bot->GetName())
			{
				if (bot->GetGroup()->IsMember(ai->GetMaster()->GetGUID()))
				{
					p.resize(8);
					p << ai->GetMaster()->GetGUID();
					bot->GetSession()->HandleGroupSetLeaderOpcode(p);
				}
			}
			return;
		}
	case SMSG_GROUP_INVITE:
		{
			AcceptInvitation();
			return;
		}

		// Handle when another player opens the trade window with the bot
		// also sends list of tradable items bot can trade if bot is allowed to obey commands from
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
    case BUY_ERR_NOT_ENOUGHT_MONEY:
        {
            TellMaster("Not enought money");
            return;
        }
    case BUY_ERR_ITEM_ALREADY_SOLD:
        {
            TellMaster("Item is already sold out");
            return;
        }
    case BUY_ERR_REPUTATION_REQUIRE:
        {
            TellMaster("Not enought reputation");
            return;
        }
    case BUY_ERR_CANT_FIND_ITEM:
        {
            TellMaster("Item not found");
            return;
        }
    }
}
