#include "pchdef.h"
#include "ShamanActions.h"
#include "ShamanActionFactory.h"
#include "ShamanNonCombatStrategy.h"
#include "HealShamanStrategy.h"

using namespace ai;

Strategy* ShamanActionFactory::createStrategy(const char* name)
{
    if (!strcmp("heal", name))
        return new HealShamanStrategy(ai);

    if (!strcmp("nc", name))
        return new ShamanNonCombatStrategy(ai);

    return ActionFactory::createStrategy(name);
}
