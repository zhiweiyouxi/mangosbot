#include "pchdef.h"
#include "WarlockTriggers.h"
#include "WarlockMultipliers.h"
#include "GenericWarlockStrategy.h"
#include "WarlockActions.h"

using namespace ai;

NextAction** GenericWarlockStrategy::getDefaultActions()
{
    return NextAction::array(0, new NextAction("shadow bolt", 1.0f), new NextAction("shoot", 1.0f), NULL);
}

void GenericWarlockStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    Strategy::InitTriggers(triggers);
    
    triggers.push_back(new TriggerNode(
        new NoAttackersTrigger(ai), 
        NextAction::array(0, new NextAction("attack least threat", 20.0f), NULL)));

    triggers.push_back(new TriggerNode(
        new ImmolateTrigger(ai),
        NextAction::array(0, new NextAction("immolate", 13.0f), NULL)));

    triggers.push_back(new TriggerNode(
        new CorruptionTrigger(ai),
        NextAction::array(0, new NextAction("corruption", 12.0f), NULL)));

    triggers.push_back(new TriggerNode(
        new CurseOfAgonyTrigger(ai),
        NextAction::array(0, new NextAction("curse of agony", 11.0f), NULL)));

    triggers.push_back(new TriggerNode(
        new NoPetTrigger(ai),
        NextAction::array(0, new NextAction("summon voidwalker", 50.0f), NULL)));

    triggers.push_back(new TriggerNode(
        new LowHealthTrigger(ai, 50),
        NextAction::array(0, new NextAction("drain life", 40.0f), NULL)));

    triggers.push_back(new TriggerNode(
        new LowManaTrigger(ai),
        NextAction::array(0, new NextAction("drain mana", 35.0f), NULL)));
}


ActionNode* GenericWarlockStrategy::createAction(const char* name)
{
    if (!strcmp("immolate", name)) 
    {
        return new ActionNode (new CastImmolateAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("corruption", name)) 
    {
        return new ActionNode (new CastCorruptionAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("summon voidwalker", name)) 
    {
        return new ActionNode (new CastSummonVoidwalkerAction(ai),  
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("drain soul"), NULL), 
            /*C*/ NULL);
    }
    else if (!strcmp("curse of agony", name)) 
    {
        return new ActionNode (new CastCurseOfAgonyAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("shadow bolt", name)) 
    {
        return new ActionNode (new CastShadowBoltAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("drain soul", name)) 
    {
        return new ActionNode (new CastDrainSoulAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("drain mana", name)) 
    {
        return new ActionNode (new CastDrainManaAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("drain life", name)) 
    {
        return new ActionNode (new CastDrainLifeAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("shoot", name)) 
    {
        return new ActionNode (new CastShootAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else return NULL;
}


