#include "pchdef.h"
#include "DruidTriggers.h"
#include "DruidMultipliers.h"
#include "BearTankDruidStrategy.h"
#include "DruidActions.h"

using namespace ai;

NextAction** BearTankDruidStrategy::getDefaultActions()
{
    return NextAction::array(0, new NextAction("faerie fire", 20.0f), new NextAction("melee", 10.0f), NULL);
}

void BearTankDruidStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    GenericDruidStrategy::InitTriggers(triggers);
    
    triggers.push_back(new TriggerNode(
        new EnemyOutOfMeleeTrigger(ai), 
        NextAction::array(0, new NextAction("melee", 10.0f), NULL)));

    triggers.push_back(new TriggerNode(
        new BearTankDruidLoseAggroTrigger(ai),
        NextAction::array(0, new NextAction("growl", 30.0f), NULL)));

    triggers.push_back(new TriggerNode(
        new MaulAvailable(ai),
        NextAction::array(0, new NextAction("maul", 20.0f), NULL)));

    triggers.push_back(new TriggerNode(
        new SwipeAvailable(ai),
        NextAction::array(0, new NextAction("swipe", 20.0f), new NextAction("maul", 10.0f), NULL)));

    triggers.push_back(new TriggerNode(
        new AttackerCountTrigger(ai, 2),
        NextAction::array(0, new NextAction("demoralizing roar", 20.0f), NULL)));

    triggers.push_back(new TriggerNode(
        new NoAttackersTrigger(ai),
        NextAction::array(0, new NextAction("attack bigger threat", 50.0f), NULL)));

    triggers.push_back(new TriggerNode(
        new InterruptSpellTrigger(ai, "bash"),
        NextAction::array(0, new NextAction("bash", 50.0f), NULL)));
}

void BearTankDruidStrategy::InitMultipliers(std::list<Multiplier*> &multipliers)
{

}


ActionNode* BearTankDruidStrategy::createAction(const char* name)
{
    if (!strcmp("melee", name)) 
    {
        return new ActionNode (new MeleeAction(ai),  
            /*P*/ NextAction::array(0, new NextAction("dire bear form"), new NextAction("feral charge - bear"), NULL),
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("feral charge - bear", name)) 
    {
        return new ActionNode (new CastFeralChargeBearAction(ai),  
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("reach melee"), NULL), 
            /*C*/ NULL);
    }
    else if (!strcmp("faerie fire", name)) 
    {
        return new ActionNode (new CastFaerieFireAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NextAction::array(0, new NextAction("melee", 10.0f), new NextAction("dire bear form", 15.0f), NULL));
    }
    else if (!strcmp("bear form", name)) 
    {
        return new ActionNode (new CastBearFormAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NextAction::array(0, new NextAction("melee", 10.0f), NULL));
    }
    else if (!strcmp("dire bear form", name)) 
    {
        return new ActionNode (new CastDireBearFormAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NextAction::array(0, new NextAction("melee", 10.0f), NULL));
    }
    else if (!strcmp("maul", name)) 
    {
        return new ActionNode (new CastMaulAction(ai),  
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("melee"), NULL), 
            /*C*/ NextAction::array(0, new NextAction("melee", 10.0f), NULL));
    }
    else if (!strcmp("bash", name)) 
    {
        return new ActionNode (new CastBashAction(ai),  
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("melee"), NULL), 
            /*C*/ NextAction::array(0, new NextAction("melee", 10.0f), NULL));
    }
    else if (!strcmp("swipe", name)) 
    {
        return new ActionNode (new CastSwipeAction(ai),  
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("melee"), NULL), 
            /*C*/ NextAction::array(0, new NextAction("melee", 10.0f), NULL));
    }
    else if (!strcmp("growl", name)) 
    {
        return new ActionNode (new CastGrowlAction(ai),  
            /*P*/ NextAction::array(0, new NextAction("dire bear form"), new NextAction("reach spell"), NULL),
            /*A*/ NextAction::array(0, new NextAction("faerie fire"), NULL), 
            /*C*/ NextAction::array(0, new NextAction("melee", 10.0f), NULL));
    }
    else if (!strcmp("demoralizing roar", name)) 
    {
        return new ActionNode (new CastDemoralizingRoarAction(ai),  
            /*P*/ NextAction::array(0, new NextAction("dire bear form"), NULL),
            /*A*/ NULL, 
            /*C*/ NextAction::array(0, new NextAction("melee", 10.0f), NULL));
    }
    else return GenericDruidStrategy::createAction(name);
}