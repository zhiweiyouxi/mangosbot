#include "pchdef.h"
#include "WarlockTriggers.h"
#include "WarlockMultipliers.h"
#include "GenericWarlockNonCombatStrategy.h"
#include "WarlockActions.h"

using namespace ai;

void GenericWarlockNonCombatStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    GenericNonCombatStrategy::InitTriggers(triggers);

    triggers.push_back(new TriggerNode(
        new DemonArmorTrigger(ai), 
        NextAction::array(0, new NextAction("demon armor", 21.0f), NULL)));

}


ActionNode* GenericWarlockNonCombatStrategy::createAction(const char* name)
{
    ActionNode* node = GenericNonCombatStrategy::createAction(name);
    if (node)
        return node;

    if (!strcmp("demon armor", name)) 
    {
        return new ActionNode (new CastDemonArmorAction(ai),  
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("demon skin"), NULL), 
            /*C*/ NULL);
    }
	else if (!strcmp("demon skin", name)) 
	{
		return new ActionNode (new CastDemonSkinAction(ai),  
			/*P*/ NULL,
			/*A*/ NULL, 
			/*C*/ NULL);
	}

    return NULL;
}