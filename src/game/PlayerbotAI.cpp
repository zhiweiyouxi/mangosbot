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


using namespace ai;
using namespace std;

PlayerbotAI::PlayerbotAI()
{
	aiRegistry = NULL;
}

PlayerbotAI::PlayerbotAI(PlayerbotMgr* mgr, Player* bot) 
{
	this->mgr = mgr;
	this->bot = bot;
	nextAICheckTime = 0;
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

	SetNextCheckDelay(1);

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

void PlayerbotAI::SetNextCheckDelay(const uint32 delay) 
{
	nextAICheckTime = time(0) + delay;
}

bool PlayerbotAI::CanUpdateAI() 
{
	time_t now = time(0);

	if (now < nextAICheckTime)
		return false;

	if (bot->IsBeingTeleported() || bot->GetTrader())
		return false;

	return true;
}

void PlayerbotAI::YieldThread()
{
	if (CanUpdateAI())
		SetNextCheckDelay(BOT_REACT_DELAY);
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

	if (fromPlayer.GetSession()->GetAccountId() != bot->GetSession()->GetAccountId())
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