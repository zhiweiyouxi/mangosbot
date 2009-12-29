#include "pchdef.h"
#include "DruidActions.h"
#include "DruidActionFactory.h"

using namespace ai;

Action* DruidActionFactory::createAction(const char* name)
{
    Action* action = ActionFactory::createAction(name);
    if (action)
        return action;

//    CREATE_ACTION_RULE("frostbolt", CastFrostBoltAction);

    return NULL;
}