#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "HunterActions.h"
#include "HunterActionFactory.h"
#include "DpsHunterStrategy.h"
#include "GenericHunterNonCombatStrategy.h"

using namespace ai;

Strategy* HunterActionFactory::createStrategy(const char* name)
{
    if (!strcmp("dps", name))
        return new DpsHunterStrategy(ai);

    if (!strcmp("nc", name))
        return new GenericHunterNonCombatStrategy(ai);

    if (!strcmp("boost", name))
        return new HunterBoostStrategy(ai);

    if (!strcmp("bspeed", name))
        return new HunterBuffSpeedNonCombatStrategy(ai);

    Strategy* strategy = ActionFactory::createStrategy(name);
    if (strategy)
        return strategy;
    return new GenericHunterStrategy(ai);
}

ActionNode* HunterActionFactory::createAction(const char* name)
{
    if (!strcmp("call pet", name)) 
    {
        return new ActionNode (new CastCallPetAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("mend pet", name)) 
    {
        return new ActionNode (new CastMendPetAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("revive pet", name)) 
    {
        return new ActionNode (new CastRevivePetAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("aspect of the pack", name)) 
    {
        return new ActionNode (new CastAspectOfThePackAction(ai),  
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("aspect of the cheetah"), NULL), 
            /*C*/ NULL);
    }
    else if (!strcmp("aspect of the cheetah", name)) 
    {
        return new ActionNode (new CastAspectOfTheCheetahAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("aspect of the hawk", name)) 
    {
        return new ActionNode (new CastAspectOfTheHawkAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
	else return ActionFactory::createAction(name);
}