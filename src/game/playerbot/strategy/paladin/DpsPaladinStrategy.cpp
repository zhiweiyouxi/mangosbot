#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "PaladinTriggers.h"
#include "PaladinMultipliers.h"
#include "DpsPaladinStrategy.h"
#include "PaladinActions.h"

using namespace ai;

NextAction** DpsPaladinStrategy::getDefaultActions()
{
    return NextAction::array(0, new NextAction("crusader strike", 10.0f), NULL);
}

void DpsPaladinStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    GenericPaladinStrategy::InitTriggers(triggers);

    triggers.push_back(new TriggerNode(
        new JudgementOfLightTrigger(ai), 
        NextAction::array(0, new NextAction("judgement of wisdom", 1.2f), NULL)));

    triggers.push_back(new TriggerNode(
        new BlessingTrigger(ai), 
        NextAction::array(0, new NextAction("blessing of might", 21.0f), NULL)));

	triggers.push_back(new TriggerNode(
		new AoeTrigger(ai, 3), 
		NextAction::array(0, new NextAction("divine storm", 27.0f), new NextAction("consecration", 27.0f), NULL)));

	triggers.push_back(new TriggerNode(
		new HasAuraTrigger(ai, "the art of war"), 
		NextAction::array(0, new NextAction("exorcism", 27.0f), NULL)));
}

void DpsPaladinStrategy::InitMultipliers(std::list<Multiplier*> &multipliers)
{

}

ActionNode* DpsPaladinStrategy::createAction(const char* name)
{
    if (!strcmp("seal of command", name)) 
    {
        return new ActionNode (new CastSealOfCommandAction(ai),  
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("seal of wisdom"), NULL), 
            /*C*/ NULL);
    }
    else if (!strcmp("blessing of might", name)) 
    {
        return new ActionNode (new CastBlessingOfMightAction(ai),  
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("blessing of kings"), NULL), 
            /*C*/ NULL);
    }
	else if (!strcmp("divine storm", name)) 
	{
		return new ActionNode (new CastDivineStormAction(ai),  
			/*P*/ NULL,
			/*A*/ NULL, 
			/*C*/ NULL);
	}
	else if (!strcmp("crusader strike", name)) 
	{
		return new ActionNode (new CastCrusaderStrikeAction(ai),  
			/*P*/ NULL,
			/*A*/ NextAction::array(0, new NextAction("melee"), NULL),
			/*C*/ NULL);
	}
    else return GenericPaladinStrategy::createAction(name);
}