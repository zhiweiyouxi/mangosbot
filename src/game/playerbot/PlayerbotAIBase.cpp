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
    nextAICheckTime = time(0) + delay;
}

void PlayerbotAIBase::IncreaseNextCheckDelay(uint32 delay)
{
    nextAICheckTime += delay;
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
    {
        time_t yieldDelay = time(0) + BOT_REACT_DELAY;
        if(nextAICheckTime < yieldDelay)
            nextAICheckTime = yieldDelay;
    }
}
