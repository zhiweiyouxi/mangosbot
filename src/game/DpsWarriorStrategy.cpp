#include "pchdef.h"
#include "WarriorTriggers.h"
#include "WarriorMultipliers.h"
#include "DpsWarriorStrategy.h"
#include "WarriorActions.h"

using namespace ai;

NextAction** DpsWarriorStrategy::getDefaultActions()
{
    return NextAction::array(0, new NextAction("melee", 10.0f), NULL);
}

void DpsWarriorStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    GenericWarriorStrategy::InitTriggers(triggers);
    
    triggers.push_back(new TriggerNode(
        new EnemyOutOfMeleeTrigger(ai), 
        NextAction::array(0, new NextAction("melee", 50.0f), NULL)));

    triggers.push_back(new TriggerNode(
        new LoseAggroTrigger(ai), 
        NextAction::array(0, new NextAction("mocking blow", 30.0f), NULL)));

    triggers.push_back(new TriggerNode(
        new NoAttackersTrigger(ai), 
        NextAction::array(0, new NextAction("attack least threat", 90.0f), NULL)));

    triggers.push_back(new TriggerNode(
        new TargetLowHealthTrigger(ai, 25), 
        NextAction::array(0, new NextAction("execute", 60.0f), NULL)));

    triggers.push_back(new TriggerNode(
        new SnareTargetTrigger(ai, "hamstring"), 
        NextAction::array(0, new NextAction("hamstring", 50.0f), NULL)));
}

void DpsWarriorStrategy::InitMultipliers(std::list<Multiplier*> &multipliers)
{

}

ActionNode* DpsWarriorStrategy::createAction(const char* name)
{
    if (!strcmp("overpower", name)) 
    {
        return new ActionNode (new CastOverpowerAction(ai),  
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("melee"), NULL), 
            /*C*/ NULL);
    }
    else if (!strcmp("melee", name)) 
    {
        return new ActionNode (new MeleeAction(ai),  
            /*P*/ NextAction::array(0, new NextAction("charge"), NULL),
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("charge", name)) 
    {
        return new ActionNode (new CastChargeAction(ai),  
            /*P*/ NextAction::array(0, new NextAction("battle stance"), NULL),
            /*A*/ NextAction::array(0, new NextAction("reach melee"), NULL), 
            /*C*/ NULL);
    }
    else if (!strcmp("rend", name)) 
    {
        return new ActionNode (new CastRendAction(ai),  
            /*P*/ NextAction::array(0, new NextAction("battle stance"), NULL),
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("mocking blow", name)) 
    {
        return new ActionNode (new CastMockingBlowAction(ai),  
            /*P*/ NextAction::array(0, new NextAction("battle stance"), NULL),
            /*A*/ NextAction::array(0, NULL), 
            /*C*/ NULL);
    }
    else if (!strcmp("death wish", name)) 
    {
        return new ActionNode (new CastDeathWishAction(ai),  
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("berserker rage"), NULL), 
            /*C*/ NULL);
    }
    else if (!strcmp("berserker rage", name)) 
    {
        return new ActionNode (new CastBerserkerRageAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("execute", name)) 
    {
        return new ActionNode (new CastExecuteAction(ai),  
            /*P*/ NextAction::array(0, new NextAction("battle stance"), NULL),
            /*A*/ NextAction::array(0, new NextAction("heroic strike"), NULL), 
            /*C*/ NULL);
    }
    else return GenericWarriorStrategy::createAction(name);
}


void WarriorBoostStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    triggers.push_back(new TriggerNode(
        new BoostTrigger(ai, "death wish", 45),
        NextAction::array(0, new NextAction("death wish", 40.0f), NULL)));

}
