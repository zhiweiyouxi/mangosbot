#include "pchdef.h"
#include "WarriorActions.h"
#include "WarriorActionFactory.h"
#include "GenericWarriorNonCombatStrategy.h"
#include "TankWarriorStrategy.h"
#include "DpsWarriorStrategy.h"

using namespace ai;

Strategy* WarriorActionFactory::createStrategy(const char* name)
{
    if (!strcmp("tank", name))
        return new TankWarriorStrategy(ai);

    if (!strcmp("dps", name))
        return new DpsWarriorStrategy(ai);

    if (!strcmp("nc", name))
        return new GenericWarriorNonCombatStrategy(ai);

    if (!strcmp("boost", name))
        return new WarriorBoostStrategy(ai);

    Strategy* strategy = ActionFactory::createStrategy(name);
    if (strategy)
        return strategy;

    return new GenericWarriorStrategy(ai);
}
