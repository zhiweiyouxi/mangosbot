#include "pchdef.h"
#include "DruidActions.h"
#include "DruidActionFactory.h"
#include "BearTankDruidStrategy.h"

using namespace ai;

Action* DruidActionFactory::createAction(const char* name)
{
    Action* action = ActionFactory::createAction(name);
    if (action)
        return action;

    CREATE_ACTION_RULE("faerie fire", CastFaerieFireBoltAction);

    return NULL;
}


Strategy* DruidActionFactory::createStrategy(const char* name)
{
    Strategy* strategy = ActionFactory::createStrategy(name);
    if (strategy)
        return strategy;

    if (!strcmp("bear tank", name))
        return new BearTankDruidStrategy(ai);

    return new GenericDruidStrategy(ai);
}
