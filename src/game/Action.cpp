#include "pchdef.h"
#include "PlayerbotAIFacade.h"
#include "Action.h"

using namespace ai;

NextAction** Action::getNextActions() 
{
    NextAction** actions = new NextAction*[1];
    actions[0] = getNextAction();
    return actions;
}

void CastSpellAction::Execute()
{
	ai->CastSpell(spell);
}


BOOL CastSpellAction::isAvailable()
{
    return ai->canCastSpell(spell);
}