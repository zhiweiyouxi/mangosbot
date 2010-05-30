#include "pchdef.h"
#include "WarlockTriggers.h"
#include "WarlockMultipliers.h"
#include "DpsWarlockStrategy.h"
#include "WarlockActions.h"

using namespace ai;

NextAction** DpsWarlockStrategy::getDefaultActions()
{
    return NextAction::array(0, new NextAction("shoot", 10.0f), NULL);
}

void DpsWarlockStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    GenericWarlockStrategy::InitTriggers(triggers);
    
    triggers.push_back(new TriggerNode(
        new NoPetTrigger(ai),
        NextAction::array(0, new NextAction("summon imp", 50.0f), NULL)));

}


ActionNode* DpsWarlockStrategy::createAction(const char* name)
{
    //else if (!strcmp("summon voidwalker", name)) 
    //{
    //    return new ActionNode (new CastSummonVoidwalkerAction(ai),  
    //        /*P*/ NULL,
    //        /*A*/ NextAction::array(0, new NextAction("drain soul"), NULL), 
    //        /*C*/ NULL);
    //}
    if (!strcmp("summon imp", name)) 
    {
        return new ActionNode (new CastSummonImpAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else 
        return GenericWarlockStrategy::createAction(name);
}


