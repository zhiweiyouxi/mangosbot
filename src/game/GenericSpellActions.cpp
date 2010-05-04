#include "pchdef.h"
#include "GenericActions.h"
#include "PlayerbotAIFacade.h"
#include <math.h>

using namespace ai;

//---------------------------------------------------------------------------------------------------------------------

bool CastLifeBloodAction::isUseful()
{
    return ai->GetHealthPercent() <= EAT_DRINK_PERCENT;
}

bool CastGiftOfTheNaaruAction::isUseful()
{
    return ai->GetHealthPercent() <= EAT_DRINK_PERCENT;
}

//---------------------------------------------------------------------------------------------------------------------

bool HealPartyMemberAction::ExecuteResult()
{
    ai->CastSpell(spell, ai->GetPartyMinHealthPlayer());
    return TRUE;
}

bool HealPartyMemberAction::isUseful()
{
    return ai->GetPartyMinHealthPercent() < 75;
}

//---------------------------------------------------------------------------------------------------------------------

bool CurePartyMemberAction::ExecuteResult()
{
    ai->CastSpell(spell, ai->GetPartyMemberToDispell(dispelType));
    return TRUE;
}

//---------------------------------------------------------------------------------------------------------------------

bool BuffOnPartyAction::ExecuteResult()
{
    ai->CastSpell(spell, ai->GetPartyMemberWithoutAura(spell));
    return TRUE;
}

bool BuffOnPartyAction::isUseful()
{
    return !ai->IsAllPartyHasAura(spell);
}

//---------------------------------------------------------------------------------------------------------------------

bool CastDebuffSpellAction::isPossible()
{
    return CastSpellAction::isPossible() && !ai->TargetHasAura(spell);
}
