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

BOOL PlayerbotAIFacade::canCastSpell( const char* spell )
{
    uint32 spellid = ai->getSpellId(spell);
    Player* bot = ai->GetPlayerBot();

    return bot->HasSpell(spellid) && !bot->HasSpellCooldown(spellid);
}