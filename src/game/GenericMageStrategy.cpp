#include "pchdef.h"
#include "MageTriggers.h"
#include "MageMultipliers.h"
#include "GenericMageStrategy.h"
#include "MageActions.h"

using namespace ai;

void GenericMageStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    CombatStrategy::InitTriggers(triggers);

    triggers.push_back(new TriggerNode(
        new NeedCureTrigger(ai, "remove curse", DISPEL_CURSE),
        NextAction::array(0, new NextAction("remove curse", 41.0f), NULL)));

    triggers.push_back(new TriggerNode(
        new PartyMemberNeedCureTrigger(ai, "remove curse", DISPEL_CURSE),
        NextAction::array(0, new NextAction("remove curse on party", 40.0f), NULL)));

    triggers.push_back(new TriggerNode(
        new EnemyTooCloseTrigger(ai),
        NextAction::array(0, new NextAction("frost nova", 50.0f), NULL)));

    triggers.push_back(new TriggerNode(
        new InterruptSpellTrigger(ai, "counterspell"), 
        NextAction::array(0, new NextAction("counterspell", 40.0f), NULL)));

	triggers.push_back(new TriggerNode(
		new LowHealthTrigger(ai, 25), 
		NextAction::array(0, new NextAction("ice block", 80.0f), NULL)));
}


ActionNode* GenericMageStrategy::createAction(const char* name)
{
    if (!strcmp("frostbolt", name)) 
    {
        return new ActionNode (new CastFrostboltAction(ai),  
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("shoot"), NULL), 
            /*C*/ NULL);
    }
	else if (!strcmp("reach spell", name)) 
	{
		return new ActionNode (new ReachSpellAction(ai, 40.0f),  
			/*P*/ NULL,
			/*A*/ NULL, 
			/*C*/ NULL);
	}
	else if (!strcmp("flee", name)) 
	{
		return new ActionNode (new FleeAction(ai, 40.0f),  
			/*P*/ NULL,
			/*A*/ NULL, 
			/*C*/ NULL);
	}
    else if (!strcmp("frost nova", name)) 
    {
        return new ActionNode (new CastFrostNovaAction(ai),  
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("flee"), NULL), 
            /*C*/ NextAction::array(0, new NextAction("flee"), NULL));
    }
    else if (!strcmp("counterspell", name)) 
    {
        return new ActionNode (new CastCounterspellAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("remove curse", name)) 
    {
        return new ActionNode (new CastRemoveCurseAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("remove curse on party", name)) 
    {
        return new ActionNode (new CastRemoveCurseOnPartyAction(ai),  
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
    else if (!strcmp("icy veins", name) || !strcmp("boost", name)) 
    {
        return new ActionNode (new CastIcyVeinsAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
	else if (!strcmp("ice block", name)) 
	{
		return new ActionNode (new CastIceBlockAction(ai),  
			/*P*/ NULL,
			/*A*/ NULL, 
			/*C*/ NULL);
	}
    else return NULL;
}


void MageBoostStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    triggers.push_back(new TriggerNode(
        new BoostTrigger(ai, "berserk", 45),
        NextAction::array(0, new NextAction("icy veins", 40.0f), NULL)));

}
