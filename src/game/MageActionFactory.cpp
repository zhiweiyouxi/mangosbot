#include "pchdef.h"
#include "MageActions.h"
#include "MageActionFactory.h"
#include "FrostMageStrategy.h"
#include "GenericMageNonCombatStrategy.h"

using namespace ai;

Strategy* MageActionFactory::createStrategy(const char* name)
{
    if (!strcmp("frost", name))
        return new FrostMageStrategy(ai);

    if (!strcmp("nc", name))
        return new GenericMageNonCombatStrategy(ai);

    Strategy* strategy = ActionFactory::createStrategy(name);
    if (strategy)
        return strategy;
    return new GenericMageStrategy(ai);
}
