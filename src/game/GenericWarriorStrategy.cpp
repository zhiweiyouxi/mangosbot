#include "pchdef.h"
#include "WarriorTriggers.h"
#include "GenericWarriorStrategy.h"
#include "WarriorActions.h"

using namespace ai;

void GenericWarriorStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{

    triggers.push_back(new TriggerNode(
        new RevengeAvailableTrigger(ai), 
        NextAction::array(0, new NextAction("revenge", 50.0f), NULL)));
    
    triggers.push_back(new TriggerNode(
        new RendDebuffTrigger(ai), 
        NextAction::array(0, new NextAction("rend", 1.0f), NULL)));
    
    triggers.push_back(new TriggerNode(
        new DisarmDebuffTrigger(ai), 
        NextAction::array(0, new NextAction("disarm", 1.0f), NULL)));

    triggers.push_back(new TriggerNode(
        new SunderArmorDebuffTrigger(ai), 
        NextAction::array(0, new NextAction("sunder armor", 1.0f), NULL)));
}


ActionNode* GenericWarriorStrategy::createAction(const char* name)
{
    if (!strcmp("defensive stance", name)) 
    {
        return new ActionNode (new CastDefensiveStanceAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else return NULL;
}
