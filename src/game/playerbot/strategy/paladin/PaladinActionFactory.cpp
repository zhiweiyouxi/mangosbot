#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "PaladinActions.h"
#include "PaladinActionFactory.h"
#include "GenericPaladinNonCombatStrategy.h"
#include "TankPaladinStrategy.h"
#include "DpsPaladinStrategy.h"
#include "PaladinBuffStrategies.h"

using namespace ai;

Strategy* PaladinActionFactory::createStrategy(const char* name)
{
    if (!strcmp("tank", name))
        return new TankPaladinStrategy(ai);

    if (!strcmp("dps", name))
        return new DpsPaladinStrategy(ai);

    if (!strcmp("nc", name))
        return new GenericPaladinNonCombatStrategy(ai);

    if (!strcmp("bhealth", name))
        return new PaladinBuffHealthStrategy(ai);
    
	if (!strcmp("bmana", name))
        return new PaladinBuffManaStrategy(ai);
    
	if (!strcmp("bdps", name))
        return new PaladinBuffDpsStrategy(ai);

    Strategy* strategy = ActionFactory::createStrategy(name);
    if (strategy)
        return strategy;

    return new GenericPaladinStrategy(ai);
}
