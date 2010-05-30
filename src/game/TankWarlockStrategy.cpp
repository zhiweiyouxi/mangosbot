#include "pchdef.h"
#include "WarlockTriggers.h"
#include "WarlockMultipliers.h"
#include "TankWarlockStrategy.h"
#include "WarlockActions.h"

using namespace ai;

NextAction** TankWarlockStrategy::getDefaultActions()
{
    return NextAction::array(0, new NextAction("shoot", 10.0f), NULL);
}

void TankWarlockStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    GenericWarlockStrategy::InitTriggers(triggers);
    
    triggers.push_back(new TriggerNode(
        new NoPetTrigger(ai),
        NextAction::array(0, new NextAction("summon voidwalker", 50.0f), NULL)));

}


ActionNode* TankWarlockStrategy::createAction(const char* name)
{
    if (!strcmp("summon voidwalker", name)) 
    {
        return new ActionNode (new CastSummonVoidwalkerAction(ai),  
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("drain soul"), NULL), 
            /*C*/ NULL);
    }
    else 
        return GenericWarlockStrategy::createAction(name);
}


