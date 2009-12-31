#include "pchdef.h"
#include "PlayerbotAIFacade.h"

using namespace ai;

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

uint8 PlayerbotAIFacade::GetRage()
{
    return ai->GetRageAmount();
}

BOOL PlayerbotAIFacade::HasAura(const char* spell)
{
    return ai->HasAura(spell);
}