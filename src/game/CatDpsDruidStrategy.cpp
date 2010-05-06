#include "pchdef.h"
#include "DruidTriggers.h"
#include "DruidMultipliers.h"
#include "DruidActions.h"
#include "CatDpsDruidStrategy.h"

using namespace ai;


NextAction** CatDpsDruidStrategy::getDefaultActions()
{
    return NextAction::array(0, new NextAction("faerie fire", 30.0f), new NextAction("mangle (cat)", 10.0f), NULL);
}

void CatDpsDruidStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    FeralDruidStrategy::InitTriggers(triggers);

    triggers.push_back(new TriggerNode(
        new EnemyOutOfMeleeTrigger(ai), 
        NextAction::array(0, new NextAction("melee", 10.0f), NULL)));

    triggers.push_back(new TriggerNode(
        new RakeTrigger(ai), 
        NextAction::array(0, new NextAction("rake", 15.0f), NULL)));

    triggers.push_back(new TriggerNode(
        new ComboPointsAvailable(ai, 5), 
        NextAction::array(0, new NextAction("ferocious bite", 20.0f), NULL)));

    triggers.push_back(new TriggerNode(
        new MyAttackerCountTrigger(ai, 2),
        NextAction::array(0, new NextAction("cower", 90.0f), NULL)));
}

void CatDpsDruidStrategy::InitMultipliers(std::list<Multiplier*> &multipliers)
{

}


ActionNode* CatDpsDruidStrategy::createAction(const char* name)
{
    if (!strcmp("reach melee", name)) 
    {
        return new ActionNode (new ReachMeleeAction(ai),  
            /*P*/ NextAction::array(0, new NextAction("cat form"), NULL),
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("melee", name)) 
    {
        return new ActionNode (new MeleeAction(ai),  
            /*P*/ NextAction::array(0, new NextAction("cat form"), new NextAction("feral charge - cat"), NULL),
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("feral charge - cat", name)) 
    {
        return new ActionNode (new CastFeralChargeCatAction(ai),  
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("reach melee"), NULL), 
            /*C*/ NULL);
    }
    else if (!strcmp("faerie fire", name)) 
    {
        return new ActionNode (new CastFaerieFireAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NextAction::array(0, new NextAction("melee", 10.0f), NULL));
    }
    else if (!strcmp("cat form", name)) 
    {
        return new ActionNode (new CastCatFormAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NextAction::array(0, new NextAction("melee", 10.0f), NULL));
    }
    else if (!strcmp("claw", name)) 
    {
        return new ActionNode (new CastClawAction(ai),  
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("melee"), NULL), 
            /*C*/ NextAction::array(0, new NextAction("claw", 15.0f), NULL));
    }
    else if (!strcmp("mangle (cat)", name)) 
    {
        return new ActionNode (new CastMangleCatAction(ai),  
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("claw"), NULL), 
            /*C*/ NextAction::array(0, new NextAction("mangle (cat)", 15.0f), NULL));
    }
    else if (!strcmp("rake", name)) 
    {
        return new ActionNode (new CastRakeAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NextAction::array(0, new NextAction("mangle (cat)", 15.0f), NULL));
    }
    else if (!strcmp("ferocious bite", name)) 
    {
        return new ActionNode (new CastFerociousBiteAction(ai),  
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("rip"), NULL), 
            /*C*/ NextAction::array(0, new NextAction("mangle (cat)", 10.0f), NULL));
    }
    else if (!strcmp("rip", name)) 
    {
        return new ActionNode (new CastRipAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NextAction::array(0, new NextAction("mangle (cat)", 10.0f), NULL));
    }
    else if (!strcmp("cower", name)) 
    {
        return new ActionNode (new CastCowerAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else return FeralDruidStrategy::createAction(name);
}