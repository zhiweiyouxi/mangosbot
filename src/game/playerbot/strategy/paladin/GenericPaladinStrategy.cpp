#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "PaladinTriggers.h"
#include "GenericPaladinStrategy.h"
#include "PaladinActions.h"

using namespace ai;

void GenericPaladinStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
	CombatStrategy::InitTriggers(triggers);

    triggers.push_back(new TriggerNode(
        new EnemyOutOfMeleeTrigger(ai), 
        NextAction::array(0, new NextAction("melee", 50.0f), NULL)));

    triggers.push_back(new TriggerNode(
        new SnareTargetTrigger(ai, "hammer of justice"), 
        NextAction::array(0, new NextAction("hammer of justice", 50.0f), NULL)));

    triggers.push_back(new TriggerNode(
        new LowHealthTrigger(ai, 60, 40),
        NextAction::array(0, new NextAction("flash of light", 50.0f), NULL)));

    triggers.push_back(new TriggerNode(
        new PartyMemberLowHealthTrigger(ai, 60, 40),
        NextAction::array(0, new NextAction("flash of light on party", 40.0f), NULL)));

    triggers.push_back(new TriggerNode(
        new LowHealthTrigger(ai, 40),
        NextAction::array(0, new NextAction("divine shield", 50.0f), new NextAction("holy light", 50.0f), NULL)));

    triggers.push_back(new TriggerNode(
        new PartyMemberLowHealthTrigger(ai, 40),
        NextAction::array(0, new NextAction("divine protection on party", 40.0f), new NextAction("holy light on party", 40.0f), NULL)));

	triggers.push_back(new TriggerNode(
		new InterruptSpellTrigger(ai, "hammer of justice"), 
		NextAction::array(0, new NextAction("hammer of justice", 40.0f), NULL)));

	triggers.push_back(new TriggerNode(
		new LowHealthTrigger(ai, 25), 
		NextAction::array(0, new NextAction("lay on hands", 90.0f), NULL)));

	triggers.push_back(new TriggerNode(
		new PartyMemberLowHealthTrigger(ai, 25), 
		NextAction::array(0, new NextAction("lay on hands on party", 90.0f), NULL)));

	triggers.push_back(new TriggerNode(
		new TargetLowHealthTrigger(ai, 25), 
		NextAction::array(0, new NextAction("hammer of wrath", 40.0f), NULL)));

}


ActionNode* GenericPaladinStrategy::createAction(const char* name)
{
    if (!strcmp("flash of light", name)) 
    {
        return new ActionNode (new CastFlashOfLightAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("divine shield", name)) 
    {
        return new ActionNode (new CastDivineShieldAction(ai),  
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("divine protection"), NULL), 
            /*C*/ NULL);
    }
    else if (!strcmp("divine protection", name)) 
    {
        return new ActionNode (new CastDivineProtectionAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("divine protection on party", name)) 
    {
        return new ActionNode (new CastDivineProtectionOnPartyAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("hammer of justice", name)) 
    {
        return new ActionNode (new CastHammerOfJusticeAction(ai),  
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("judgement of justice"), NULL), 
            /*C*/ NULL);
    }
    else if (!strcmp("flash of light", name)) 
    {
        return new ActionNode (new CastFlashOfLightAction(ai),  
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("holy light"), NULL), 
            /*C*/ NULL);
    }
    else if (!strcmp("flash of light on party", name)) 
    {
        return new ActionNode (new CastFlashOfLightOnPartyAction(ai),  
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("holy light on party"), NULL), 
            /*C*/ NULL);
    }
    else if (!strcmp("holy light", name)) 
    {
        return new ActionNode (new CastHolyLightAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("holy light on party", name)) 
    {
        return new ActionNode (new CastHolyLightOnPartyAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
	else if (!strcmp("lay on hands", name)) 
	{
		return new ActionNode (new CastLayOnHandsAction(ai),  
			/*P*/ NULL,
			/*A*/ NULL, 
			/*C*/ NULL);
	}
	else if (!strcmp("lay on hands on party", name)) 
	{
		return new ActionNode (new CastLayOnHandsOnPartyAction(ai),  
			/*P*/ NULL,
			/*A*/ NULL, 
			/*C*/ NULL);
	}
	else if (!strcmp("judgement of justice", name)) 
	{
		return new ActionNode (new CastJudgementOfJusticeAction(ai),  
			/*P*/ NULL,
			/*A*/ NULL, 
			/*C*/ NULL);
	}
	else if (!strcmp("hammer of wrath", name)) 
	{
		return new ActionNode (new CastHammerOfWrathAction(ai),  
			/*P*/ NULL,
			/*A*/ NULL, 
			/*C*/ NULL);
	}
    return NULL;
}
