#include "pchdef.h"
#include "GenericTriggers.h"
#include "GenericNonCombatStrategy.h"
#include "GenericActions.h"
#include "NonCombatActions.h"

using namespace ai;

void GenericNonCombatStrategy::InitTriggers(std::list<Trigger*> &triggers)
{
    Strategy::InitTriggers(triggers);
    triggers.push_back(new LowHealthTrigger(ai));
    triggers.push_back(new LowManaTrigger(ai));
}

void AssistNonCombatStrategy::InitTriggers(std::list<Trigger*> &triggers)
{
    triggers.push_back(new NoAttackersTrigger(ai));
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