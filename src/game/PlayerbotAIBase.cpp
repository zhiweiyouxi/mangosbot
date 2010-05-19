#include "pchdef.h"
#include "Spell.h"
#include "SpellMgr.h"
#include "SpellAuras.h"
#include "Unit.h"
#include "Player.h"
#include "WorldSession.h"
#include "WorldPacket.h"
#include "PlayerbotAIBase.h"

using namespace ai;
using namespace std;

void PlayerbotAIBase::SetNextCheckDelay(const uint32 delay) 
{
	nextAICheckTime = time(0) + delay;
}

bool PlayerbotAIBase::CanUpdateAI() 
{
	time_t now = time(0);

	if (now < nextAICheckTime)
		return false;

	return true;
}