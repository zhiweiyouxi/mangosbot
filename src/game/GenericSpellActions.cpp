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

bool ResurrectPartyMemberAction::ExecuteResult()
{
	return ai->CastSpell(spell, ai->GetDeadPartyMember());
}

bool ResurrectPartyMemberAction::isUseful()
{
	return CastSpellAction::isUseful() && ai->GetDeadPartyMember();
}

//---------------------------------------------------------------------------------------------------------------------

bool HealPartyMemberAction::ExecuteResult()
{
    return ai->CastSpell(spell, ai->GetPartyMinHealthPlayer());
}

bool HealPartyMemberAction::isUseful()
{
    return CastSpellAction::isUseful() && ai->GetPartyMinHealthPercent() < (100 - estAmount);
}

//---------------------------------------------------------------------------------------------------------------------

bool CurePartyMemberAction::ExecuteResult()
{
    return ai->CastSpell(spell, ai->GetPartyMemberToDispell(dispelType));
}

//---------------------------------------------------------------------------------------------------------------------

bool BuffOnPartyAction::ExecuteResult()
{
    return ai->CastSpell(spell, ai->GetPartyMemberWithoutAura(spell));
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
