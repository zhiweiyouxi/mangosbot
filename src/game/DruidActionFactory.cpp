#include "pchdef.h"
#include "DruidActions.h"
#include "DruidActionFactory.h"
#include "BearTankDruidStrategy.h"
#include "GenericDruidNonCombatStrategy.h"

using namespace ai;


Strategy* DruidActionFactory::createStrategy(const char* name)
{
    Strategy* strategy = ActionFactory::createStrategy(name);
    if (strategy)
        return strategy;

    if (!strcmp("bear tank", name))
        return new BearTankDruidStrategy(ai);

    if (!strcmp("druid non combat", name))
        return new GenericDruidNonCombatStrategy(ai);

    return new GenericDruidStrategy(ai);
}
