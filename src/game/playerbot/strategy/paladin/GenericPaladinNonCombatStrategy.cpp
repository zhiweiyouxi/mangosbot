#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "PaladinTriggers.h"
#include "PaladinMultipliers.h"
#include "GenericPaladinNonCombatStrategy.h"
#include "PaladinActions.h"

using namespace ai;

void GenericPaladinNonCombatStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    GenericNonCombatStrategy::InitTriggers(triggers);

    triggers.push_back(new TriggerNode(
        new BlessingOfKingsOnPartyTrigger(ai), 
        NextAction::array(0, new NextAction("blessing of kings on party", 20.0f), NULL)));

	triggers.push_back(new TriggerNode(
		new PartyMemberDeadTrigger(ai),
		NextAction::array(0, new NextAction("redemption", 30.0f), NULL)));
}

ActionNode* GenericPaladinNonCombatStrategy::createAction(const char* name)
{
    if (!strcmp("blessing of kings on party", name)) 
    {
        return new ActionNode (new CastBlessingOfKingsOnPartyAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
	else if (!strcmp("redemption", name)) 
	{
		return new ActionNode (new CastRedemptionAction(ai),  
			/*P*/ NULL,
			/*A*/ NULL, 
			/*C*/ NULL);
	}
    else return NULL;
}
