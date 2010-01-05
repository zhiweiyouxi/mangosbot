#include "pchdef.h"
#include "WarriorTriggers.h"
#include "WarriorMultipliers.h"
#include "GenericWarriorNonCombatStrategy.h"
#include "WarriorActions.h"

using namespace ai;

void GenericWarriorNonCombatStrategy::InitTriggers(std::list<Trigger*> &triggers)
{
    GenericNonCombatStrategy::InitTriggers(triggers);

    triggers.push_back(new DefensiveStanceTrigger(ai));
}

ActionNode* GenericWarriorNonCombatStrategy::createAction(const char* name)
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
