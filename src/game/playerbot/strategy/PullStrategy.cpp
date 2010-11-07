#include "../../pchdef.h"
#include "../playerbot.h"
#include "PassiveMultiplier.h"
#include "PullStrategy.h"
#include "GenericActions.h"

using namespace ai;

class MagePullMultiplier : public PassiveMultiplier
{
public:
    MagePullMultiplier(const char *action) : PassiveMultiplier() 
    {
        this->action = action;
    }

public:
    virtual float GetValue(Action* action);

private:
    const char *action;
};

float MagePullMultiplier::GetValue(Action* action) 
{
    if (!action) 
        return 1.0f;

    const char* name = action->getName();
    if (!strcmp(this->action, name) ||
        !strcmp("reach spell", name) ||
        !strcmp("change strategy", name))
        return 1.0f;

    return PassiveMultiplier::GetValue(action);
}

NextAction** PullStrategy::getDefaultActions()
{
    return NextAction::array(0, new NextAction(action, 105.0f), new NextAction("follow", 104.0f), new NextAction("end pull", 103.0f), NULL);
}

void PullStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    RangedCombatStrategy::InitTriggers(triggers);
}

void PullStrategy::InitMultipliers(std::list<Multiplier*> &multipliers)
{
    multipliers.push_back(new MagePullMultiplier(action));
    RangedCombatStrategy::InitMultipliers(multipliers);
}

ActionNode* PullStrategy::createAction(const char* name)
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