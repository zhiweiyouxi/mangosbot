#include "pchdef.h"
#include "HunterTriggers.h"
#include "HunterMultipliers.h"
#include "GenericHunterNonCombatStrategy.h"
#include "HunterActions.h"

using namespace ai;

void GenericHunterNonCombatStrategy::InitTriggers(std::list<Trigger*> &triggers)
{
    GenericNonCombatStrategy::InitTriggers(triggers);
    
    triggers.push_back(new HunterAspectOfTheHawkTrigger(ai));
    triggers.push_back(new HunterHasNoPetTrigger(ai));
    triggers.push_back(new HuntersPetDeadTrigger(ai));
    triggers.push_back(new HuntersPetLowHealthTrigger(ai));
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
    else if (!strcmp("aspect of the hawk", name)) 
    {
        return new ActionNode (new CastAspectOfTheHawkAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else return NULL;
}