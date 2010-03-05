#include "pchdef.h"
#include "WarriorTriggers.h"
#include "GenericWarriorStrategy.h"
#include "WarriorActions.h"

using namespace ai;

void GenericWarriorStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    triggers.push_back(new TriggerNode(
        new EnemyOutOfMeleeTrigger(ai), 
        NextAction::array(0, new NextAction("melee", 50.0f), NULL)));
    
    triggers.push_back(new TriggerNode(
        new BattleShoutTrigger(ai), 
        NextAction::array(0, new NextAction("battle shout", 80.0f), NULL)));

    /*triggers.push_back(new TriggerNode(
        new RevengeAvailableTrigger(ai), 
        NextAction::array(0, new NextAction("revenge", 50.0f), NULL)));*/
    
    triggers.push_back(new TriggerNode(
        new RendDebuffTrigger(ai), 
        NextAction::array(0, new NextAction("rend", 1.3f), NULL)));
    
    triggers.push_back(new TriggerNode(
        new AttackerCountTrigger(ai, 2), 
        NextAction::array(0, new NextAction("demoralizing shout", 20.0f), NULL)));

    triggers.push_back(new TriggerNode(
        new LowHealthTrigger(ai), 
        NextAction::array(0, new NextAction("lifeblood", 60.0f), NULL)));
}


ActionNode* GenericWarriorStrategy::createAction(const char* name)
{
    if (!strcmp("hamstring", name)) 
    {
        return new ActionNode (new CastHamstringAction(ai),  
            /*P*/ NextAction::array(0, new NextAction("battle stance"), NULL),
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("defensive stance", name)) 
    {
        return new ActionNode (new CastDefensiveStanceAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("gift of the naaru", name)) 
    {
        return new ActionNode (new CastGiftOfTheNaaruAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("battle stance", name)) 
    {
        return new ActionNode (new CastBattleStanceAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("heroic strike", name)) 
    {
        return new ActionNode (new CastHeroicStrikeAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("demoralizing shout", name)) 
    {
        return new ActionNode (new CastDemoralizingShoutAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("battle shout", name)) 
    {
        return new ActionNode (new CastBattleShoutAction(ai),  
            /*P*/ NextAction::array(0, new NextAction("battle stance"), NULL),
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("thunder clap", name)) 
    {
        return new ActionNode (new CastThunderClapAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else return NULL;
}
