#include "pchdef.h"
#include "MageTriggers.h"
#include "MageActions.h"

using namespace ai;

NextAction** MageEnemyTooCloseTrigger::getNextActions()
{ 
    NextAction** actions = new NextAction*[3];
    actions[0] = new NextAction("frostnova", 10.0f);
    actions[1] = new NextAction("flee", 5.0f);
    actions[2] = NULL;
    return actions;
}