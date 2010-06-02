#include "pchdef.h"
#include "PlayerbotMgr.h"
#include "PlayerbotAI.h"
#include "Spell.h"
#include "SpellMgr.h"
#include "SpellAuras.h"
#include "Unit.h"
#include "Player.h"
#include "WorldSession.h"
#include "WorldPacket.h"
#include "AiManagerRegistry.h"
#include "AiStrategyManager.h"
#include "AiMoveManager.h"
#include "Item.h"
#include "Spell.h"


using namespace ai;
using namespace std;

PlayerbotAI::PlayerbotAI() : PlayerbotAIBase()
{
	aiRegistry = NULL;
}

PlayerbotAI::PlayerbotAI(PlayerbotMgr* mgr, Player* bot) : PlayerbotAIBase()
{
	this->mgr = mgr;
	this->bot = bot;
	aiRegistry = new AiManagerRegistry(this);

    aiRegistry->GetMoveManager()->Summon();
}

PlayerbotAI::~PlayerbotAI()
{
	if (aiRegistry)
		delete aiRegistry;
}

void PlayerbotAI::UpdateAI(uint32 elapsed)
{
	if (!CanUpdateAI())
		return;

    if (bot->IsBeingTeleported() || bot->GetTrader())
        return;

	SetNextCheckDelay(1);
    Group* group = bot->GetGroup();
    if (group)
    {
        if (group->GetMembersCount() > 10)
            SetNextCheckDelay(2);
        else if (group->GetMembersCount() > 20)
            SetNextCheckDelay(3);
    }

	if (bot->isAlive())
	{
		aiRegistry->GetStrategyManager()->DoNextAction();
	}
	else
	{
		aiRegistry->GetMoveManager()->Resurrect();
	}

	YieldThread();
}

void PlayerbotAI::HandleTeleportAck()
{
	bot->GetMotionMaster()->Clear(true);
	if (bot->IsBeingTeleportedNear())
	{
		WorldPacket p = WorldPacket(MSG_MOVE_TELEPORT_ACK, 8 + 4 + 4);
		p.appendPackGUID(bot->GetGUID());
		p << (uint32) 0; // supposed to be flags? not used currently
		p << (uint32) time(0); // time - not currently used
		bot->GetSession()->HandleMoveTeleportAck(p);
	}
	else if (bot->IsBeingTeleportedFar())
		bot->GetSession()->HandleMoveWorldportAckOpcode();
}

void PlayerbotAI::HandleCommand(const string& text, Player& fromPlayer)
{
	// ignore any messages from Addons
	if (text.empty() ||
		text.find("X-Perl") != std::wstring::npos ||
		text.find("HealBot") != std::wstring::npos ||
		text.find("LOOT_OPENED") != std::wstring::npos ||
		text.find("CTRA") != std::wstring::npos)
		return;

	if (fromPlayer.GetGuildId() != bot->GetGuildId())
	    return;

	AiManagerBase** managers = aiRegistry->GetManagers();
	for (int i=0; i<aiRegistry->GetManagerCount(); i++)
		managers[i]->HandleCommand(text, fromPlayer);
}

void PlayerbotAI::HandleBotOutgoingPacket(const WorldPacket& packet)
{
	AiManagerBase** managers = aiRegistry->GetManagers();
	for (int i=0; i<aiRegistry->GetManagerCount(); i++)
		managers[i]->HandleBotOutgoingPacket(packet);
}


