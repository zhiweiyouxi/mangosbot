#include "pchdef.h"
#include "DruidActions.h"
#include "DruidActionFactory.h"
#include "BearTankDruidStrategy.h"
#include "CatDpsDruidStrategy.h"
#include "GenericDruidNonCombatStrategy.h"

using namespace ai;


Strategy* DruidActionFactory::createStrategy(const char* name)
{
    Strategy* strategy = ActionFactory::createStrategy(name);
    if (strategy)
        return strategy;

    if (!strcmp("bear tank", name))
        return new BearTankDruidStrategy(ai);

    if (!strcmp("cat dps", name))
        return new CatDpsDruidStrategy(ai);

    if (!strcmp("druid non combat", name))
        return new GenericDruidNonCombatStrategy(ai);

    return new GenericDruidStrategy(ai);
}
