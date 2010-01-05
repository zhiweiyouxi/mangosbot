#include "pchdef.h"
#include "GenericTriggers.h"
#include "GenericNonCombatStrategy.h"
#include "GenericActions.h"
#include "NonCombatActions.h"

using namespace ai;

void GenericNonCombatStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    Strategy::InitTriggers(triggers);
    
    triggers.push_back(new TriggerNode(
        new LowHealthTrigger(ai), 
        NextAction::array(0, new NextAction("eat", 9.0f), NULL)));
    
    triggers.push_back(new TriggerNode(
        new LowManaTrigger(ai), 
        NextAction::array(0, new NextAction("drink", 9.0f), NULL)));
}

void AssistNonCombatStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    triggers.push_back(new TriggerNode(
        new NoAttackersTrigger(ai), 
        NextAction::array(0, new NextAction("attack least threat", 9.0f), NULL)));
}

ActionNode* AssistNonCombatStrategy::createAction(const char* name)
{
    if (!strcmp("attack least threat", name)) 
    {
        return new ActionNode (new AttackLeastThreatAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("attack bigger threat", name)) 
    {
        return new ActionNode (new AttackBiggerThreatAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else return NULL;
}

ActionNode* StayNonCombatStrategy::createAction(const char* name)
{
    if (!strcmp("stay", name)) 
    {
        return new ActionNode (new StayAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else return NULL;
}

ActionNode* FollowMasterNonCombatStrategy::createAction(const char* name)
{
    if (!strcmp("follow", name)) 
    {
        return new ActionNode (new FollowAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else return NULL;
}