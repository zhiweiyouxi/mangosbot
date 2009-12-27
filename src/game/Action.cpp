#include "pchdef.h"
#include "Action.h"

namespace ai
{

Action::Action(PlayerbotAI* const ai)
{
	this->ai = ai;
}

Action::~Action(void)
{
}

//---------------------------------------------------------------------------------------------------------------------

CastSpellAction::CastSpellAction(PlayerbotAI* const ai, const char* spell) : Action(ai)
{
	this->spellid = ai->getSpellId(spell);
}

void CastSpellAction::Execute()
{
	ai->CastSpell(spellid);
}

}