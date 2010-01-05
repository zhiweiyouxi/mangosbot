#include "pchdef.h"
#include "WarriorActions.h"
#include "WarriorActionFactory.h"
#include "GenericWarriorNonCombatStrategy.h"
#include "TankWarriorStrategy.h"

using namespace ai;

Strategy* WarriorActionFactory::createStrategy(const char* name)
{
    Strategy* strategy = ActionFactory::createStrategy(name);
    if (strategy)
        return strategy;

    if (!strcmp("tank warrior", name))
        return new TankWarriorStrategy(ai);

    if (!strcmp("warrior non combat", name))
        return new GenericWarriorNonCombatStrategy(ai);

    return new GenericWarriorStrategy(ai);
}
