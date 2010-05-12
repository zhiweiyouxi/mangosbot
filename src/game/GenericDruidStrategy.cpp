#include "pchdef.h"
#include "DruidTriggers.h"
#include "GenericDruidStrategy.h"
#include "DruidActions.h"

using namespace ai;

void GenericDruidStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    CombatStrategy::InitTriggers(triggers);

	triggers.push_back(new TriggerNode(
		new LowHealthTrigger(ai, 60, 40),
		NextAction::array(0, new NextAction("rejuvenation", 50.0f), NULL)));

    triggers.push_back(new TriggerNode(
        new LowHealthTrigger(ai, 40, 25),
        NextAction::array(0, new NextAction("regrowth", 50.0f), NULL)));

	triggers.push_back(new TriggerNode(
		new PartyMemberLowHealthTrigger(ai, 60, 40),
		NextAction::array(0, new NextAction("rejuvenation on party", 50.0f), NULL)));

    triggers.push_back(new TriggerNode(
        new PartyMemberLowHealthTrigger(ai),
        NextAction::array(0, new NextAction("regrowth on party", 50.0f), NULL)));

    triggers.push_back(new TriggerNode(
        new NeedCureTrigger(ai, "cure poison", DISPEL_POISON),
        NextAction::array(0, new NextAction("abolish poison", 40.0f), NULL)));

    triggers.push_back(new TriggerNode(
        new PartyMemberNeedCureTrigger(ai, "cure poison", DISPEL_POISON),
        NextAction::array(0, new NextAction("abolish poison on party", 40.0f), NULL)));

	triggers.push_back(new TriggerNode(
		new PartyMemberDeadTrigger(ai),
		NextAction::array(0, new NextAction("rebirth", 30.0f), NULL)));
}

ActionNode* GenericDruidStrategy::createAction(const char* name)
{
    if (!strcmp("melee", name)) 
    {
        return new ActionNode (new MeleeAction(ai),  
            /*P*/ NextAction::array(0, new NextAction("reach melee"), NULL),
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("caster form", name)) 
    {
        return new ActionNode (new CastCasterFormAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("gift of the naaru", name)) 
    {
        return new ActionNode (new CastGiftOfTheNaaruAction(ai),  
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("regrowth"), NULL), 
            /*C*/ NULL);
    }
    else if (!strcmp("regrowth", name)) 
    {
        return new ActionNode (new CastRegrowthAction(ai),  
            /*P*/ NextAction::array(0, new NextAction("caster form"), NULL),
            /*A*/ NULL, 
            /*C*/ NextAction::array(0, new NextAction("melee", 10.0f), NULL));
    }
    else if (!strcmp("rejuvenation", name)) 
    {
        return new ActionNode (new CastRejuvenationAction(ai),  
            /*P*/ NextAction::array(0, new NextAction("caster form"), NULL),
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("regrowth on party", name)) 
    {
        return new ActionNode (new CastRegrowthOnPartyAction(ai),  
            /*P*/ NextAction::array(0, new NextAction("caster form"), new NextAction("rejuvenation on party"), NULL),
            /*A*/ NULL, 
            /*C*/ NextAction::array(0, new NextAction("melee", 10.0f), NULL));
    }
    else if (!strcmp("rejuvenation on party", name)) 
    {
        return new ActionNode (new CastRejuvenationOnPartyAction(ai),  
            /*P*/ NextAction::array(0, new NextAction("caster form"), NULL),
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("cure poison", name)) 
    {
        return new ActionNode (new CastCurePoisonAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("cure poison on party", name)) 
    {
        return new ActionNode (new CastCurePoisonOnPartyAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("abolish poison", name)) 
    {
        return new ActionNode (new CastAbolishPoisonAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("abolish poison on party", name)) 
    {
        return new ActionNode (new CastAbolishPoisonOnPartyAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
	else if (!strcmp("rebirth", name)) 
	{
		return new ActionNode (new CastRebirthAction(ai),  
			/*P*/ NULL,
			/*A*/ NULL, 
			/*C*/ NULL);
	}

    else return NULL;
}



void DruidBoostStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    triggers.push_back(new TriggerNode(
        new BoostTrigger(ai, "berserk", 45),
        NextAction::array(0, new NextAction("berserk", 40.0f), new NextAction("tiger's fury", 40.0f), NULL)));

}
