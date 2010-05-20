#include "pchdef.h"
#include "GenericActions.h"
#include "PlayerbotAIFacade.h"
#include <math.h>

using namespace ai;

Unit* CastSpellAction::GetTarget()
{
	return targetManager->GetCurrentTarget();
}

bool CastSpellAction::ExecuteResult() 
{
	return spellManager->CastSpell(spell, GetTarget()); 
}

bool CastSpellAction::isPossible() 
{
	return spellManager->CanCastSpell(spell, GetTarget());
}

bool CastSpellAction::isUseful() 
{
	return GetTarget();
}


bool CastAuraSpellAction::isPossible() 
{
	return CastSpellAction::isPossible() && !spellManager->HasAura(spell, GetTarget());
}

bool CastAuraSpellAction::isUseful() 
{
	return CastSpellAction::isUseful() && !spellManager->HasAura(spell, GetTarget());
}


Unit* ResurrectPartyMemberAction::GetTarget()
{
	return targetManager->GetDeadPartyMember();
}


Unit* HealPartyMemberAction::GetTarget()
{
	return targetManager->GetPartyMinHealthPlayer();
}

Unit* CastHealingSpellAction::GetTarget()
{
	return targetManager->GetSelf();
}

bool CastHealingSpellAction::isUseful() 
{
	Unit* target = GetTarget();
	return CastSpellAction::isUseful() && statsManager->GetHealthPercent(target) < (100 - estAmount);
}


Unit* CurePartyMemberAction::GetTarget()
{
	return targetManager->GetPartyMemberToDispell(dispelType);
}


Unit* BuffOnPartyAction::GetTarget()
{
	return targetManager->GetPartyMemberWithoutAura(spell);
}

Unit* CastBuffSpellAction::GetTarget()
{
	return targetManager->GetSelf();
}
