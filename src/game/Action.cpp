#include "pchdef.h"
#include "PlayerbotAI.h"
#include "Action.h"

using namespace ai;

CastSpellAction::CastSpellAction(PlayerbotAI* const ai, const char* spell) : Action(ai)
{
	this->spellid = ai->getSpellId(spell);
}

void CastSpellAction::Execute()
{
	ai->CastSpell(spellid);
}
