#include "../../../pchdef.h"
#include "../../playerbot.h"
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

	triggers.push_back(new TriggerNode(
		new ItemCountTrigger(ai, "healthstone", 1), 
		NextAction::array(0, new NextAction("create healthstone", 15.0f), NULL)));

	triggers.push_back(new TriggerNode(
		new ItemCountTrigger(ai, "firestone", 1), 
		NextAction::array(0, new NextAction("create firestone", 14.0f), NULL)));

	triggers.push_back(new TriggerNode(
		new ItemCountTrigger(ai, "spellstone", 1), 
		NextAction::array(0, new NextAction("create spellstone", 13.0f), NULL)));
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
	else if (!strcmp("create healthstone", name)) 
	{
		return new ActionNode (new CastCreateHealthstoneAction(ai),  
			/*P*/ NULL,
			/*A*/ NULL, 
			/*C*/ NULL);
	}
	else if (!strcmp("create firestone", name)) 
	{
		return new ActionNode (new CastCreateFirestoneAction(ai),  
			/*P*/ NULL,
			/*A*/ NULL, 
			/*C*/ NULL);
	}
	else if (!strcmp("create spellstone", name)) 
	{
		return new ActionNode (new CastCreateSpellstoneAction(ai),  
			/*P*/ NULL,
			/*A*/ NULL, 
			/*C*/ NULL);
	}

    return NULL;
}