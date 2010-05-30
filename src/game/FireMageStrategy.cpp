#include "pchdef.h"
#include "MageTriggers.h"
#include "MageMultipliers.h"
#include "FireMageStrategy.h"
#include "MageActions.h"

using namespace ai;

NextAction** FireMageStrategy::getDefaultActions()
{
    return NextAction::array(0, new NextAction("fireball", 1.0f), NULL);
}

void FireMageStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    GenericMageStrategy::InitTriggers(triggers);

}

void FireMageStrategy::InitMultipliers(std::list<Multiplier*> &multipliers)
{
    GenericMageStrategy::InitMultipliers(multipliers);
}

ActionNode* FireMageStrategy::createAction(const char* name)
{
    ActionNode* node = GenericMageStrategy::createAction(name);
    if (node)
        return node;

    if (!strcmp("fireball", name)) 
    {
        return new ActionNode (new CastFireballAction(ai),  
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("shoot"), NULL), 
            /*C*/ NULL);
    }
    else return NULL;
}