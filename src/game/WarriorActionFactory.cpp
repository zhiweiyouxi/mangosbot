#include "pchdef.h"
#include "WarriorActions.h"
#include "WarriorActionFactory.h"

using namespace ai;

Action* WarriorActionFactory::createAction(const char* name)
{
    Action* action = ActionFactory::createAction(name);
    if (action)
        return action;

//    CREATE_ACTION_RULE("frostbolt", CastFrostBoltAction);

    return NULL;
}