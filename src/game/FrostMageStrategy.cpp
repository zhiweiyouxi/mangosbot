#include "pchdef.h"
#include "MageTriggers.h"
#include "MageMultipliers.h"
#include "FrostMageStrategy.h"
#include "MageActions.h"

using namespace ai;

NextAction** FrostMageStrategy::getDefaultActions()
{
    return NextAction::array(0, new NextAction("frostbolt", 1.0f), NULL);
}

void FrostMageStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    GenericMageStrategy::InitTriggers(triggers);

}

void FrostMageStrategy::InitMultipliers(std::list<Multiplier*> &multipliers)
{
    GenericMageStrategy::InitMultipliers(multipliers);
}

ActionNode* FrostMageStrategy::createAction(const char* name)
{
    ActionNode* node = GenericMageStrategy::createAction(name);
    if (node)
        return node;

    if (!strcmp("frostbolt", name)) 
    {
        return new ActionNode (new CastFrostboltAction(ai),  
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("shoot"), NULL), 
            /*C*/ NULL);
    }
    else if (!strcmp("frost nova", name)) 
    {
        return new ActionNode (new CastFrostNovaAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NextAction::array(0, new NextAction("flee"), new NextAction("frostbolt"), NULL));
    }

    else return NULL;
}