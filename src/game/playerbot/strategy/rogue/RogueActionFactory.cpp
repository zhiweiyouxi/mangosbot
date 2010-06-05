#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "RogueActions.h"
#include "RogueActionFactory.h"
#include "DpsRogueStrategy.h"
#include "GenericRogueNonCombatStrategy.h"

using namespace ai;


Strategy* RogueActionFactory::createStrategy(const char* name)
{
	if (!strcmp("dps", name))
		return new DpsRogueStrategy(ai);

    if (!strcmp("nc", name))
        return new GenericRogueNonCombatStrategy(ai);

    return ActionFactory::createStrategy(name);
}
