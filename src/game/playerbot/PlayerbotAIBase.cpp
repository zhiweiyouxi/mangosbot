#include "../pchdef.h"
#include "playerbot.h"

using namespace ai;
using namespace std;

PlayerbotAIBase::PlayerbotAIBase()
{
    nextAICheckTime = 0;
}


void PlayerbotAIBase::SetNextCheckDelay(const uint32 delay) 
{
    time_t checkTime = time(0) + delay;

    if (nextAICheckTime < checkTime)
        nextAICheckTime = checkTime;
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
