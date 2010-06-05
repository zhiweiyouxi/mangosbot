#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "WarlockActions.h"
#include "WarlockActionFactory.h"
#include "DpsWarlockStrategy.h"
#include "GenericWarlockNonCombatStrategy.h"
#include "TankWarlockStrategy.h"

using namespace ai;

Strategy* WarlockActionFactory::createStrategy(const char* name)
{
    if (!strcmp("nc", name))
        return new GenericWarlockNonCombatStrategy(ai);

    if (!strcmp("dps", name))
        return new DpsWarlockStrategy(ai);

    if (!strcmp("tank", name))
        return new TankWarlockStrategy(ai);

    return ActionFactory::createStrategy(name);
}
