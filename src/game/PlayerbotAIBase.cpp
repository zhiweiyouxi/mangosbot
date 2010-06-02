#include "pchdef.h"
#include "PlayerbotAIBase.h"
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

PlayerbotAIBase::PlayerbotAIBase()
{
    nextAICheckTime = 0;
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

    return true;
}

void PlayerbotAIBase::YieldThread()
{
    if (CanUpdateAI())
        SetNextCheckDelay(BOT_REACT_DELAY);
}
