#include "pchdef.h"
#include "ShamanTriggers.h"
#include "ShamanMultipliers.h"
#include "HealShamanStrategy.h"
#include "ShamanActions.h"

using namespace ai;

NextAction** HealShamanStrategy::getDefaultActions()
{
    return NextAction::array(0, new NextAction("melee", 10.0f), NULL);
}

void HealShamanStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    GenericShamanStrategy::InitTriggers(triggers);

    triggers.push_back(new TriggerNode(
        new PartyMemberLowHealthTrigger(ai, 60, 40),
        NextAction::array(0, new NextAction("chain heal on party", 25.0f), NULL)));

    triggers.push_back(new TriggerNode(
        new PartyMemberLowHealthTrigger(ai),
        NextAction::array(0, new NextAction("riptide on party", 25.0f), NULL)));

    triggers.push_back(new TriggerNode(
        new LowHealthTrigger(ai, 60, 40),
        NextAction::array(0, new NextAction("chain heal", 26.0f), NULL)));

    triggers.push_back(new TriggerNode(
        new LowHealthTrigger(ai),
        NextAction::array(0, new NextAction("riptide", 26.0f), NULL)));
}

ActionNode* HealShamanStrategy::createAction(const char* name)
{
    ActionNode* node = GenericShamanStrategy::createAction(name);
    if (node)
        return node;

    if (!strcmp("earth shield", name)) 
    {
        return new ActionNode (new CastEarthShieldAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("earth shield on party", name)) 
    {
        return new ActionNode (new CastEarthShieldOnPartyAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("chain heal", name)) 
    {
        return new ActionNode (new CastChainHealAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("riptide", name)) 
    {
        return new ActionNode (new CastRiptideAction(ai),  
            /*P*/ NULL,
			/*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("chain heal on party", name)) 
    {
        return new ActionNode (new CastChainHealOnPartyAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("riptide on party", name)) 
    {
        return new ActionNode (new CastRiptideOnPartyAction(ai),  
            /*P*/ NULL,
			/*A*/ NextAction::array(0, new NextAction("earth shield on party"), NULL), 
            /*C*/ NULL);
    }

    return NULL;
}

