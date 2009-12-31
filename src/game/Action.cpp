#include "pchdef.h"
#include "PlayerbotAIFacade.h"
#include "Action.h"

using namespace ai;

NextAction** Action::getNextActions() 
{
    NextAction** actions = new NextAction*[2];
    actions[0] = getNextAction();
    actions[1] = NULL;
    return actions;
}

NextAction** Action::getAlternativeActions() 
{
    NextAction** actions = new NextAction*[2];
    actions[0] = getAlternativeAction();
    actions[1] = NULL;
    return actions;
}

NextAction** Action::getPrerequisiteActions() 
{
    NextAction** actions = new NextAction*[2];
    actions[0] = getPrerequisiteAction();
    actions[1] = NULL;
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