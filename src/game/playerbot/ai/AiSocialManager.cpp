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

void AiSocialManager::HandleCommand(const string& text, Player& fromPlayer)
{
	if (text == "leave")
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
