#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "WarlockActions.h"
#include "WarlockActionFactory.h"
#include "DpsWarlockStrategy.h"
#include "GenericWarlockNonCombatStrategy.h"
#include "TankWarlockStrategy.h"
#include "../PullStrategy.h"

using namespace ai;

Strategy* WarlockActionFactory::createStrategy(const char* name)
{
    if (!strcmp("nc", name))
        return new GenericWarlockNonCombatStrategy(ai);

    if (!strcmp("dps", name))
        return new DpsWarlockStrategy(ai);

    if (!strcmp("tank", name))
        return new TankWarlockStrategy(ai);

    if (!strcmp("pull", name))
        return new PullStrategy(ai, "shoot");

    return ActionFactory::createStrategy(name);
}
