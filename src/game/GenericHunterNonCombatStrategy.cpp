#include "pchdef.h"
#include "HunterTriggers.h"
#include "HunterMultipliers.h"
#include "GenericHunterNonCombatStrategy.h"
#include "HunterActions.h"

using namespace ai;

void GenericHunterNonCombatStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    GenericNonCombatStrategy::InitTriggers(triggers);
    
    triggers.push_back(new TriggerNode(
        new HunterAspectOfThePackTrigger(ai), 
        NextAction::array(0, new NextAction("aspect of the pack", 1.0f), NULL)));

    triggers.push_back(new TriggerNode(
        new AttackerCountTrigger(ai, 1), 
        NextAction::array(0, new NextAction("aspect of the hawk", 90.0f), NULL)));

    triggers.push_back(new TriggerNode(
        new HunterHasNoPetTrigger(ai), 
        NextAction::array(0, new NextAction("call pet", 60.0f), NULL)));

    triggers.push_back(new TriggerNode(
        new HuntersPetDeadTrigger(ai), 
        NextAction::array(0, new NextAction("revive pet", 60.0f), NULL)));

    triggers.push_back(new TriggerNode(
        new HuntersPetLowHealthTrigger(ai), 
        NextAction::array(0, new NextAction("mend pet", 60.0f), NULL)));
}


ActionNode* GenericHunterNonCombatStrategy::createAction(const char* name)
{
    if (!strcmp("call pet", name)) 
    {
        return new ActionNode (new CastCallPetAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("mend pet", name)) 
    {
        return new ActionNode (new CastMendPetAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("revive pet", name)) 
    {
        return new ActionNode (new CastRevivePetAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("aspect of the pack", name)) 
    {
        return new ActionNode (new CastAspectOfThePackAction(ai),  
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("aspect of the cheetah"), NULL), 
            /*C*/ NULL);
    }
    else if (!strcmp("aspect of the cheetah", name)) 
    {
        return new ActionNode (new CastAspectOfTheCheetahAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("aspect of the hawk", name)) 
    {
        return new ActionNode (new CastAspectOfTheHawkAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else return NULL;
}