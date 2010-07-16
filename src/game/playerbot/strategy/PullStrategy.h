#pragma once

namespace ai
{
    class PullStrategy : public RangedCombatStrategy
    {
    public:
        PullStrategy(AiManagerRegistry* const ai, const char *action) : RangedCombatStrategy(ai) 
        {
            this->action = action;
        }

    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
        virtual void InitMultipliers(std::list<Multiplier*> &multipliers);
        virtual const char* getName() { return "pull"; }
        virtual ActionNode* createAction(const char* name);
        virtual NextAction** getDefaultActions();

    private:
        const char* action;
    };
}