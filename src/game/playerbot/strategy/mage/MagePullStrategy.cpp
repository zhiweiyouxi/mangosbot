#include "../../../pchdef.h"
#include "../../playerbot.h"
#include "MageTriggers.h"
#include "MageMultipliers.h"
#include "../PassiveMultiplier.h"
#include "MagePullStrategy.h"
#include "MageActions.h"

using namespace ai;

class MagePullMultiplier : public PassiveMultiplier
{
public:
    MagePullMultiplier() : PassiveMultiplier() {}

public:
    virtual float GetValue(Action* action);
};

float MagePullMultiplier::GetValue(Action* action) 
{
    if (!action) 
        return 1.0f;

    const char* name = action->getName();
    if (!strcmp("shoot", name) ||
        !strcmp("reach spell", name) ||
        !strcmp("change strategy", name))
        return 1.0f;

    return PassiveMultiplier::GetValue(action);
}

NextAction** MagePullStrategy::getDefaultActions()
{
    return NextAction::array(0, new NextAction("shoot", 105.0f), new NextAction("follow", 104.0f), new NextAction("end pull", 103.0f), NULL);
}

void MagePullStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    RangedCombatStrategy::InitTriggers(triggers);
}

void MagePullStrategy::InitMultipliers(std::list<Multiplier*> &multipliers)
{
    multipliers.push_back(new MagePullMultiplier());
    RangedCombatStrategy::InitMultipliers(multipliers);
}

ActionNode* MagePullStrategy::createAction(const char* name)
{
    if (!strcmp("end pull", name)) 
    {
        return new ActionNode (new ChangeCombatStrategyAction(ai, "-pull"),  
            /*P*/ NULL,
            /*A*/ NULL,
            /*C*/ NULL);
    }
    else if (!strcmp("follow", name)) 
    {
        return new ActionNode (new FollowAction(ai),  
            /*P*/ NULL,
            /*A*/ NULL, 
            /*C*/ NULL);
    }
    else return RangedCombatStrategy::createAction(name);
}