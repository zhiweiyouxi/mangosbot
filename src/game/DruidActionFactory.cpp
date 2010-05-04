#include "pchdef.h"
#include "DruidActions.h"
#include "DruidActionFactory.h"
#include "BearTankDruidStrategy.h"
#include "CatDpsDruidStrategy.h"
#include "GenericDruidNonCombatStrategy.h"

using namespace ai;


Strategy* DruidActionFactory::createStrategy(const char* name)
{
    if (!strcmp("bear", name))
        return new BearTankDruidStrategy(ai);

    if (!strcmp("cat", name))
        return new CatDpsDruidStrategy(ai);

    if (!strcmp("nc", name))
        return new GenericDruidNonCombatStrategy(ai);

    if (!strcmp("boost", name))
        return new DruidBoostStrategy(ai);

    Strategy* strategy = ActionFactory::createStrategy(name);
    if (strategy)
        return strategy;

    return new GenericDruidStrategy(ai);
}
