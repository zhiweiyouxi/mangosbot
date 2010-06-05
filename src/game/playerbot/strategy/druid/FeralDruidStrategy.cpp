#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "DruidTriggers.h"
#include "FeralDruidStrategy.h"
#include "DruidActions.h"

using namespace ai;

void FeralDruidStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    GenericDruidStrategy::InitTriggers(triggers);
    
    triggers.push_back(new TriggerNode(
        new LowHealthTrigger(ai, 25),
        NextAction::array(0, new NextAction("survival instincts", 80.0f), NULL)));

}

ActionNode* FeralDruidStrategy::createAction(const char* name)
{
    if (!strcmp("survival instincts", name)) 
    {
        return new ActionNode (new CastSurvivalInstinctsAction(ai),  
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("rejuvenation"), NULL), 
            /*C*/ NULL);
    }
    else if (!strcmp("cure poison", name)) 
    {
        return new ActionNode (new CastCurePoisonAction(ai),  
            /*P*/ NextAction::array(0, new NextAction("caster form"), NULL),
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("cure poison on party", name)) 
    {
        return new ActionNode (new CastCurePoisonOnPartyAction(ai),  
            /*P*/ NextAction::array(0, new NextAction("caster form"), NULL),
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("abolish poison", name)) 
    {
        return new ActionNode (new CastAbolishPoisonAction(ai),  
            /*P*/ NextAction::array(0, new NextAction("caster form"), NULL),
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("abolish poison on party", name)) 
    {
        return new ActionNode (new CastAbolishPoisonOnPartyAction(ai),  
            /*P*/ NextAction::array(0, new NextAction("caster form"), NULL),
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("berserk", name)) 
    {
        return new ActionNode (new CastBerserkAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("tiger's fury", name)) 
    {
        return new ActionNode (new CastTigersFuryAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    
	else return GenericDruidStrategy::createAction(name);
}

