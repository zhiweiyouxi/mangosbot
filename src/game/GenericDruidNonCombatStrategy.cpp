#include "pchdef.h"
#include "DruidTriggers.h"
#include "DruidMultipliers.h"
#include "GenericDruidNonCombatStrategy.h"
#include "DruidActions.h"

using namespace ai;

void GenericDruidNonCombatStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    GenericNonCombatStrategy::InitTriggers(triggers);
    
    triggers.push_back(new TriggerNode(
        new PartyMemberLowHealthTrigger(ai),
        NextAction::array(0, new NextAction("regrowth on party", 50.0f), NULL)));

    triggers.push_back(new TriggerNode(
        new ThornsTrigger(ai),
        NextAction::array(0, new NextAction("thorns", 1.0f), NULL)));
    
    triggers.push_back(new TriggerNode(
        new MarkOfTheWildTrigger(ai),
        NextAction::array(0, new NextAction("mark of the wild", 1.0f), NULL)));
    
    triggers.push_back(new TriggerNode(
        new MarkOfTheWildOnPartyTrigger(ai),
        NextAction::array(0, new NextAction("mark of the wild on party", 1.0f), NULL)));
}


ActionNode* GenericDruidNonCombatStrategy::createAction(const char* name)
{
    if (!strcmp("thorns", name)) 
    {
        return new ActionNode (new CastThornsAction(ai),  
            /*P*/ NextAction::array(0, new NextAction("caster form"), NULL),
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("mark of the wild", name)) 
    {
        return new ActionNode (new CastMarkOfTheWildAction(ai),  
            /*P*/ NextAction::array(0, new NextAction("caster form"), NULL),
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("mark of the wild on party", name)) 
    {
        return new ActionNode (new CastMarkOfTheWildOnPartyAction(ai),  
            /*P*/ NextAction::array(0, new NextAction("caster form"), NULL),
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("regrowth on party", name)) 
    {
        return new ActionNode (new CastRegrowthOnPartyAction(ai),  
            /*P*/ NextAction::array(0, new NextAction("caster form"), NULL),
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("caster form", name)) 
    {
        return new ActionNode (new CastCasterFormAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
   else return NULL;
}