#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "RogueTriggers.h"
#include "RogueMultipliers.h"
#include "RogueActions.h"
#include "DpsRogueStrategy.h"

using namespace ai;


NextAction** DpsRogueStrategy::getDefaultActions()
{
    return NextAction::array(0, new NextAction("melee", 10.0f), NULL);
}

void DpsRogueStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    CombatStrategy::InitTriggers(triggers);

    triggers.push_back(new TriggerNode(
        new EnemyOutOfMeleeTrigger(ai), 
        NextAction::array(0, new NextAction("melee", 10.0f), NULL)));

	triggers.push_back(new TriggerNode(
		new EnergyAvailable(ai, 60), 
		NextAction::array(0, new NextAction("mutilate", 20.0f), NULL)));

    triggers.push_back(new TriggerNode(
        new ComboPointsAvailable(ai, 5), 
        NextAction::array(0, new NextAction("kidney shot", 30.0f), NULL)));

	triggers.push_back(new TriggerNode(
		new MyAttackerCountTrigger(ai, 2), 
		NextAction::array(0, new NextAction("vanish", 40.0f), NULL)));

	triggers.push_back(new TriggerNode(
		new LowHealthTrigger(ai), 
		NextAction::array(0, new NextAction("evasion", 50.0f), new NextAction("feint", 50.0f), NULL)));

	triggers.push_back(new TriggerNode(
		new InterruptSpellTrigger(ai, "kick"), 
		NextAction::array(0, new NextAction("kick", 30.0f), NULL)));

    triggers.push_back(new TriggerNode(
        new IsBehindTargetTrigger(ai), 
        NextAction::array(0, new NextAction("backstab", 21.0f), NULL)));
}

void DpsRogueStrategy::InitMultipliers(std::list<Multiplier*> &multipliers)
{

}


ActionNode* DpsRogueStrategy::createAction(const char* name)
{
    if (!strcmp("mutilate", name)) 
    {
        return new ActionNode (new CastMutilateAction(ai),  
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("sinister strike"), NULL), 
            /*C*/ NULL);
    }
    else if (!strcmp("sinister strike", name)) 
    {
        return new ActionNode (new CastSinisterStrikeAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
	else if (!strcmp("kidney shot", name)) 
	{
		return new ActionNode (new CastKidneyShotAction(ai),  
			/*P*/ NULL,
			/*A*/ NextAction::array(0, new NextAction("rupture"), NULL), 
			/*C*/ NULL);
	}
	else if (!strcmp("rupture", name)) 
	{
		return new ActionNode (new CastRuptureAction(ai),  
			/*P*/ NULL,
			/*A*/ NextAction::array(0, new NextAction("slice and dice"), NULL), 
			/*C*/ NULL);
	}
	else if (!strcmp("slice and dice", name)) 
	{
		return new ActionNode (new CastSliceAndDiceAction(ai),  
			/*P*/ NULL,
			/*A*/ NextAction::array(0, new NextAction("eviscerate"), NULL), 
			/*C*/ NULL);
	}    
	else if (!strcmp("eviscerate", name)) 
	{
		return new ActionNode (new CastEviscerateAction(ai),  
			/*P*/ NULL,
			/*A*/ NULL, 
			/*C*/ NULL);
	}
	else if (!strcmp("vanish", name)) 
	{
		return new ActionNode (new CastVanishAction(ai),  
			/*P*/ NULL,
			/*A*/ NULL, 
			/*C*/ NULL);
	}
	else if (!strcmp("evasion", name)) 
	{
		return new ActionNode (new CastEvasionAction(ai),  
			/*P*/ NULL,
			/*A*/ NULL, 
			/*C*/ NULL);
	}
	else if (!strcmp("kick", name)) 
	{
		return new ActionNode (new CastKickAction(ai),  
			/*P*/ NULL,
			/*A*/ NULL, 
			/*C*/ NULL);
	}
	else if (!strcmp("feint", name)) 
	{
		return new ActionNode (new CastFeintAction(ai),  
			/*P*/ NULL,
			/*A*/ NULL, 
			/*C*/ NULL);
	}
    else if (!strcmp("backstab", name)) 
    {
        return new ActionNode (new CastBackstabAction(ai),  
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("mutilate"), NULL), 
            /*C*/ NULL);
    }
	else return CombatStrategy::createAction(name);
}