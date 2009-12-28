#include "pchdef.h"
#include "PlayerbotAI.h"
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

ActionBasket::ActionBasket(Action* action, float relevance)
{
	this->action = action;
	this->relevance = relevance;
}

ActionBasket::~ActionBasket(void)
{
}

}