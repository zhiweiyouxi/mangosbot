#include "pchdef.h"
#include "Trigger.h"
#include "Action.h"

using namespace ai;

NextAction** Trigger::getNextActions() 
{
    NextAction** actions = new NextAction*[1];
    actions[0] = getNextAction();
    return actions;
}