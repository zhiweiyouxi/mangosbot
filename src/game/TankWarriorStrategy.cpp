#include "pchdef.h"
#include "WarriorTriggers.h"
#include "WarriorMultipliers.h"
#include "TankWarriorStrategy.h"
#include "WarriorActions.h"

using namespace ai;

void TankWarriorStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    GenericWarriorStrategy::InitTriggers(triggers);
    
    triggers.push_back(new TriggerNode(
        new EnemyOutOfMeleeTrigger(ai), 
        NextAction::array(0, new NextAction("melee", 50.0f), NULL)));

    triggers.push_back(new TriggerNode(
        new LoseAggroTrigger(ai), 
        NextAction::array(0, new NextAction("mocking blow", 30.0f), NULL)));

    triggers.push_back(new TriggerNode(
        new HeroicStrikeAvailable(ai), 
        NextAction::array(0, new NextAction("heroic strike", 20.0f), NULL)));

    triggers.push_back(new TriggerNode(
        new AttackerCountTrigger(ai, 2), 
        NextAction::array(0, new NextAction("demoralizing shout", 20.0f), NULL)));

    triggers.push_back(new TriggerNode(
        new NoAttackersTrigger(ai), 
        NextAction::array(0, new NextAction("ttack bigger threat", 9.0f), NULL)));
}

void TankWarriorStrategy::InitMultipliers(std::list<Multiplier*> &multipliers)
{

}

ActionNode* TankWarriorStrategy::createAction(const char* name)
{
    if (!strcmp("rend", name)) 
    {
        return new ActionNode (new CastRendAction(ai),  
            /*P*/ NextAction::array(0, new NextAction("melee"), NULL),
            /*A*/ NULL, 
            /*C*/ NextAction::array(0, new NextAction("heroic strike", 20.0f), NULL));
    }
    else if (!strcmp("heroic strike", name)) 
    {
        return new ActionNode (new CastHeroicStrikeAction(ai),  
            /*P*/ NextAction::array(0, new NextAction("melee"), NULL),
            /*A*/ NULL, 
            /*C*/ NextAction::array(0, new NextAction("heroic strike", 20.0f), NULL));
    }
    else if (!strcmp("mocking blow", name)) 
    {
        return new ActionNode (new CastMockingBlowAction(ai),  
            /*P*/ NextAction::array(0, new NextAction("melee"), NULL),
            /*A*/ NextAction::array(0, new NextAction("taunt"), NULL), 
            /*C*/ NextAction::array(0, new NextAction("heroic strike", 20.0f), NULL));
    }
    else if (!strcmp("taunt", name)) 
    {
        return new ActionNode (new CastTauntAction(ai),  
            /*P*/ NextAction::array(0, new NextAction("melee"), NULL),
            /*A*/ NULL, 
            /*C*/ NextAction::array(0, new NextAction("heroic strike", 20.0f), NULL));
    }
    else if (!strcmp("revenge", name)) 
    {
        return new ActionNode (new CastRevengeAction(ai),  
            /*P*/ NextAction::array(0, new NextAction("melee"), NULL),
            /*A*/ NextAction::array(0, new NextAction("melee"), NULL), 
            /*C*/ NextAction::array(0, new NextAction("heroic strike", 20.0f), NULL));
    }
    else if (!strcmp("disarm", name)) 
    {
        return new ActionNode (new CastDisarmAction(ai),  
            /*P*/ NextAction::array(0, new NextAction("melee"), NULL),
            /*A*/ NULL, 
            /*C*/ NextAction::array(0, new NextAction("heroic strike", 20.0f), NULL));
    }
    else if (!strcmp("sunder armor", name)) 
    {
        return new ActionNode (new CastSunderArmorAction(ai),  
            /*P*/ NextAction::array(0, new NextAction("melee"), NULL),
            /*A*/ NULL, 
            /*C*/ NextAction::array(0, new NextAction("heroic strike", 20.0f), NULL));
    }
    else if (!strcmp("demoralizing shout", name)) 
    {
        return new ActionNode (new CastDemoralizingShoutAction(ai),  
            /*P*/ NextAction::array(0, new NextAction("melee"), NULL),
            /*A*/ NULL, 
            /*C*/ NextAction::array(0, new NextAction("heroic strike", 20.0f), NULL));
    }
    else if (!strcmp("shield bash", name)) 
    {
        return new ActionNode (new CastShieldBashAction(ai),  
            /*P*/ NextAction::array(0, new NextAction("melee"), NULL),
            /*A*/ NULL, 
            /*C*/ NextAction::array(0, new NextAction("heroic strike", 20.0f), NULL));
    }
    else if (!strcmp("intimidating shout", name)) 
    {
        return new ActionNode (new CastIntimidatingShoutAction(ai),  
            /*P*/ NextAction::array(0, new NextAction("melee"), NULL),
            /*A*/ NULL, 
            /*C*/ NextAction::array(0, new NextAction("heroic strike", 20.0f), NULL));
    }
    else if (!strcmp("battle shout", name)) 
    {
        return new ActionNode (new CastBattleShoutAction(ai),  
            /*P*/ NextAction::array(0, new NextAction("melee"), NULL),
            /*A*/ NULL, 
            /*C*/ NextAction::array(0, new NextAction("heroic strike", 20.0f), NULL));
    }
    else if (!strcmp("thunder clap", name)) 
    {
        return new ActionNode (new CastThunderClapAction(ai),  
            /*P*/ NextAction::array(0, new NextAction("melee"), NULL),
            /*A*/ NULL, 
            /*C*/ NextAction::array(0, new NextAction("heroic strike", 20.0f), NULL));
    }
    else return NULL;
}