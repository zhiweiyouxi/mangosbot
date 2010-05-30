#pragma once

#include "Strategy.h"
#include "HealPriestStrategy.h"

namespace ai
{
    class DpsPriestStrategy : public HealPriestStrategy
    {
    public:
        DpsPriestStrategy(AiManagerRegistry* const ai) : HealPriestStrategy(ai) {}

    public:
        virtual NextAction** getDefaultActions();
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
        virtual void InitMultipliers(std::list<Multiplier*> &multipliers);
        virtual const char* getName() { return "dps"; }
        virtual ActionNode* createAction(const char* name);

    };

    class PriestBoostStrategy : public Strategy
    {
    public:
        PriestBoostStrategy(AiManagerRegistry* const ai) : Strategy(ai) {}

    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
        virtual const char* getName() { return "boost"; }
    };
}