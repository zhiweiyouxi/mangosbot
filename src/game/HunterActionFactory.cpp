#include "pchdef.h"
#include "HunterActions.h"
#include "HunterActionFactory.h"

using namespace ai;

Action* HunterActionFactory::createAction(const char* name)
{
    Action* action = ActionFactory::createAction(name);
    if (action)
        return action;

//    CREATE_ACTION_RULE("frostbolt", CastFrostBoltAction);

    return NULL;
}