#include "pchdef.h"
#include "PriestTriggers.h"
#include "PriestMultipliers.h"
#include "HealPriestStrategy.h"
#include "PriestActions.h"

using namespace ai;

NextAction** HealPriestStrategy::getDefaultActions()
{
    return NextAction::array(0, new NextAction("shoot", 10.0f), NULL);
}

ActionNode* HealPriestStrategy::createAction(const char* name)
{
    ActionNode* node = HealPriestNonCombatStrategy::createAction(name);
    if (node)
        return node;

    if (!strcmp("shoot", name)) 
    {
        return new ActionNode (new CastShootAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else return NULL;
}

