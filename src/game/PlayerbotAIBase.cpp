#include "pchdef.h"
#include "Spell.h"
#include "SpellMgr.h"
#include "SpellAuras.h"
#include "Unit.h"
#include "Player.h"
#include "WorldSession.h"
#include "WorldPacket.h"
#include "PlayerbotAIBase.h"
#include "AiManagerRegistry.h"
#include "PlayerbotClassAI.h"

using namespace ai;
using namespace std;

PlayerbotAIBase::PlayerbotAIBase(PlayerbotMgr* mgr, Player* bot) 
{
	this->mgr = mgr;
	this->bot = bot;
	nextAICheckTime = 0;
	aiRegistry = new AiManagerRegistry(this);
	m_classAI = (PlayerbotClassAI*) new PlayerbotClassAI(bot, aiRegistry);
}

PlayerbotAIBase::~PlayerbotAIBase()
{
	if (m_classAI) 
		delete m_classAI;

	if (aiRegistry)
		delete aiRegistry;
}

void PlayerbotAIBase::UpdateAI(uint32 elapsed)
{
	if (!CanUpdateAI())
		return;

	SetNextCheckDelay(1);

	if (bot->isAlive())
	{
		m_classAI->DoNextAction();
	}
	else
	{
		aiRegistry->GetMoveManager()->Resurrect();
	}

	YieldThread();
}

void PlayerbotAIBase::SetNextCheckDelay(const uint32 delay) 
{
	nextAICheckTime = time(0) + delay;
}

bool PlayerbotAIBase::CanUpdateAI() 
{
	time_t now = time(0);

	if (now < nextAICheckTime)
		return false;

	if (bot->IsBeingTeleported() || bot->GetTrader())
		return false;

	return true;
}

void PlayerbotAIBase::YieldThread()
{
	if (CanUpdateAI())
		SetNextCheckDelay(BOT_REACT_DELAY);
}
