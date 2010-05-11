#include "pchdef.h"
#include "WarlockTriggers.h"
#include "WarlockMultipliers.h"
#include "DpsWarlockStrategy.h"
#include "WarlockActions.h"

using namespace ai;

NextAction** DpsWarlockStrategy::getDefaultActions()
{
    return NextAction::array(0, new NextAction("shoot", 10.0f), NULL);
}

void DpsWarlockStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    CombatStrategy::InitTriggers(triggers);
    
    triggers.push_back(new TriggerNode(
        new CorruptionTrigger(ai),
        NextAction::array(0, new NextAction("corruption", 12.0f), NULL)));

    triggers.push_back(new TriggerNode(
        new CurseOfAgonyTrigger(ai),
        NextAction::array(0, new NextAction("curse of agony", 11.0f), NULL)));

    triggers.push_back(new TriggerNode(
        new NoPetTrigger(ai),
        NextAction::array(0, new NextAction("summon imp", 50.0f), NULL)));

    triggers.push_back(new TriggerNode(
        new LowHealthTrigger(ai, 50),
        NextAction::array(0, new NextAction("drain life", 40.0f), NULL)));

	triggers.push_back(new TriggerNode(
		new TargetLowHealthTrigger(ai, 20),
		NextAction::array(0, new NextAction("drain soul", 30.0f), NULL)));

}


ActionNode* DpsWarlockStrategy::createAction(const char* name)
{
    if (!strcmp("immolate", name)) 
    {
        return new ActionNode (new CastImmolateAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
	else if (!strcmp("reach spell", name)) 
	{
		return new ActionNode (new ReachSpellAction(ai, 30.0f),  
			/*P*/ NULL,
			/*A*/ NULL, 
			/*C*/ NULL);
	}
	else if (!strcmp("flee", name)) 
	{
		return new ActionNode (new FleeAction(ai, 30.0f),  
			/*P*/ NULL,
			/*A*/ NULL, 
			/*C*/ NULL);
	}
    else if (!strcmp("corruption", name)) 
    {
        return new ActionNode (new CastCorruptionAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("summon voidwalker", name)) 
    {
        return new ActionNode (new CastSummonVoidwalkerAction(ai),  
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("drain soul"), NULL), 
            /*C*/ NULL);
    }
    else if (!strcmp("summon imp", name)) 
    {
        return new ActionNode (new CastSummonImpAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("curse of agony", name)) 
    {
        return new ActionNode (new CastCurseOfAgonyAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("shadow bolt", name)) 
    {
        return new ActionNode (new CastShadowBoltAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("drain soul", name)) 
    {
        return new ActionNode (new CastDrainSoulAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("drain mana", name)) 
    {
        return new ActionNode (new CastDrainManaAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("drain life", name)) 
    {
        return new ActionNode (new CastDrainLifeAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("shoot", name)) 
    {
        return new ActionNode (new CastShootAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else return NULL;
}


