#include "pchdef.h"
#include "MageTriggers.h"
#include "MageMultipliers.h"
#include "GenericMageNonCombatStrategy.h"
#include "MageActions.h"

using namespace ai;

void GenericMageNonCombatStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    GenericMageStrategy::InitTriggers(triggers);

    triggers.push_back(new TriggerNode(
        new ArcaneIntellectTrigger(ai), 
        NextAction::array(0, new NextAction("arcane intellect", 21.0f), NULL)));

    triggers.push_back(new TriggerNode(
        new ArcaneIntellectOnPartyTrigger(ai), 
        NextAction::array(0, new NextAction("arcane intellect on party", 20.0f), NULL)));

}


ActionNode* GenericMageNonCombatStrategy::createAction(const char* name)
{
    ActionNode* node = GenericMageStrategy::createAction(name);
    if (node)
        return node;

    if (!strcmp("arcane intellect", name)) 
    {
        return new ActionNode (new CastArcaneIntellectAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else if (!strcmp("arcane intellect on party", name)) 
    {
        return new ActionNode (new CastArcaneIntellectOnPartyAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }

    return NULL;
}