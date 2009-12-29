#include "pchdef.h"
#include "MageActionFactory.h"
#include "MageActions.h"

using namespace ai;

Action* MageActionFactory::createAction(const char* name)
{
    Action* action = ActionFactory::createAction(name);
    if (action)
        return action;

    if (!strcmp("frostbolt", name))
        return new CastFrostBoltAction(ai);

    if (!strcmp("frostnova", name))
        return new CastFrostNovaAction(ai);

    return NULL;
}