#include "pchdef.h"
#include "HunterActions.h"
#include "HunterActionFactory.h"
#include "DpsHunterStrategy.h"
#include "GenericHunterNonCombatStrategy.h"

using namespace ai;

Strategy* HunterActionFactory::createStrategy(const char* name)
{
    Strategy* strategy = ActionFactory::createStrategy(name);
    if (strategy)
        return strategy;

    if (!strcmp("dps hunter", name))
        return new DpsHunterStrategy(ai);

    if (!strcmp("hunter non combat", name))
        return new GenericHunterNonCombatStrategy(ai);

    return new GenericHunterStrategy(ai);
}
