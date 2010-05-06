#include "pchdef.h"
#include "DruidActions.h"
#include "DruidActionFactory.h"
#include "BearTankDruidStrategy.h"
#include "CatDpsDruidStrategy.h"
#include "CasterDruidStrategy.h"
#include "GenericDruidNonCombatStrategy.h"

using namespace ai;


Strategy* DruidActionFactory::createStrategy(const char* name)
{
    if (!strcmp("bear", name) || !strcmp("tank", name))
        return new BearTankDruidStrategy(ai);

    if (!strcmp("cat", name))
        return new CatDpsDruidStrategy(ai);

	if (!strcmp("caster", name) || !strcmp("dps", name))
		return new CasterDruidStrategy(ai);

    if (!strcmp("nc", name))
        return new GenericDruidNonCombatStrategy(ai);

    if (!strcmp("boost", name))
        return new DruidBoostStrategy(ai);

    return ActionFactory::createStrategy(name);
}
