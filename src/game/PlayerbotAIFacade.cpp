#include "pchdef.h"
#include "PlayerbotAIFacade.h"

float PlayerbotAIFacade::GetDistanceToEnemy()
{
    Unit *target = ai->GetCurrentTarget();
    if (target && !target->isDead())
    {
        return ai->GetPlayerBot()->GetDistance(target); 
    }
    return 1e8;
}
