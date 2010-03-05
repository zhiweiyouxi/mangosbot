#include "pchdef.h"
#include "WarriorTriggers.h"
#include "WarriorMultipliers.h"
#include "TankWarriorStrategy.h"
#include "WarriorActions.h"

using namespace ai;

NextAction** TankWarriorStrategy::getDefaultActions()
{
    return NextAction::array(0, new NextAction("melee", 10.0f), NULL);
}

void TankWarriorStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    GenericWarriorStrategy::InitTriggers(triggers);
   
    triggers.push_back(new TriggerNode(
        new SunderArmorDebuffTrigger(ai), 
        NextAction::array(0, new NextAction("sunder armor", 1.0f), NULL)));

    triggers.push_back(new TriggerNode(
        new DisarmDebuffTrigger(ai), 
        NextAction::array(0, new NextAction("disarm", 1.2f), NULL)));

    triggers.push_back(new TriggerNode(
        new LoseAggroTrigger(ai), 
        NextAction::array(0, new NextAction("taunt", 30.0f), NULL)));

    triggers.push_back(new TriggerNode(
        new NoAttackersTrigger(ai), 
        NextAction::array(0, new NextAction("attack bigger threat", 9.0f), NULL)));

    triggers.push_back(new TriggerNode(
        new LowHealthTrigger(ai, 60, 40), 
        NextAction::array(0, new NextAction("shield wall", 50.0f), NULL)));
}

void TankWarriorStrategy::InitMultipliers(std::list<Multiplier*> &multipliers)
{

}

ActionNode* TankWarriorStrategy::createAction(const char* name)
{
    if (!strcmp("melee", name)) 
    {
        return new ActionNode (new MeleeAction(ai),  
            /*P*/ NextAction::array(0, new NextAction("defensive stance"), new NextAction("reach melee"), NULL),
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("shield wall", name)) 
    {
        return new ActionNode (new CastShieldWallAction(ai),  
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("shield block"), NULL), 
            /*C*/ NULL);
    }
    else if (!strcmp("rend", name)) 
    {
        return new ActionNode (new CastRendAction(ai),  
            /*P*/ NextAction::array(0, new NextAction("defensive stance"), NULL),
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("mocking blow", name)) 
    {
        return new ActionNode (new CastMockingBlowAction(ai),  
            /*P*/ NextAction::array(0, new NextAction("battle stance"), NULL),
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("taunt", name)) 
    {
        return new ActionNode (new CastTauntAction(ai),  
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("mocking blow"), NULL), 
            /*C*/ NULL);
    }
    else if (!strcmp("revenge", name)) 
    {
        return new ActionNode (new CastRevengeAction(ai),  
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("melee"), NULL), 
            /*C*/ NULL);
    }
    else if (!strcmp("disarm", name)) 
    {
        return new ActionNode (new CastDisarmAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("sunder armor", name)) 
    {
        return new ActionNode (new CastSunderArmorAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("shield bash", name)) 
    {
        return new ActionNode (new CastShieldBashAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("intimidating shout", name)) 
    {
        return new ActionNode (new CastIntimidatingShoutAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else return GenericWarriorStrategy::createAction(name);
}