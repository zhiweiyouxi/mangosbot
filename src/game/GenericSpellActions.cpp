#include "pchdef.h"
#include "GenericActions.h"
#include "PlayerbotAIFacade.h"
#include <math.h>

using namespace ai;

//---------------------------------------------------------------------------------------------------------------------

BOOL CastLifeBloodAction::isUseful()
{
    return ai->GetHealthPercent() <= EAT_DRINK_PERCENT;
}

BOOL CastGiftOfTheNaaruAction::isUseful()
{
    return ai->GetHealthPercent() <= EAT_DRINK_PERCENT;
}

//---------------------------------------------------------------------------------------------------------------------

BOOL HealPartyMemberAction::Execute()
{
    ai->CastSpell(spell, ai->GetPartyMinHealthPlayer());
    return TRUE;
}

BOOL HealPartyMemberAction::isUseful()
{
    return ai->GetPartyMinHealthPercent() < 75;
}

//---------------------------------------------------------------------------------------------------------------------

BOOL CurePartyMemberAction::Execute()
{
    ai->CastSpell(spell, ai->GetPartyMemberToDispell(dispelType));
    return TRUE;
}

//---------------------------------------------------------------------------------------------------------------------

BOOL BuffOnPartyAction::Execute()
{
    ai->CastSpell(spell, ai->GetPartyMemberWithoutAura(spell));
    return TRUE;
}

BOOL BuffOnPartyAction::isUseful()
{
    return !ai->IsAllPartyHasAura(spell);
}

//---------------------------------------------------------------------------------------------------------------------

BOOL CastDebuffSpellAction::isPossible()
{
    return CastSpellAction::isPossible() && !ai->TargetHasAura(spell);
}
