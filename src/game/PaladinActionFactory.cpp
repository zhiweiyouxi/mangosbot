#include "pchdef.h"
#include "PaladinActions.h"
#include "PaladinActionFactory.h"
#include "GenericPaladinNonCombatStrategy.h"
#include "TankPaladinStrategy.h"

using namespace ai;

Strategy* PaladinActionFactory::createStrategy(const char* name)
{
    if (!strcmp("tank", name))
        return new TankPaladinStrategy(ai);

    if (!strcmp("nc", name))
        return new GenericPaladinNonCombatStrategy(ai);

    Strategy* strategy = ActionFactory::createStrategy(name);
    if (strategy)
        return strategy;

    return new GenericPaladinStrategy(ai);
}
