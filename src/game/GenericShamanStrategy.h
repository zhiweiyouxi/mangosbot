#pragma once

#include "Strategy.h"

namespace ai
{
    class GenericShamanStrategy : public CombatStrategy
    {
    public:
        GenericShamanStrategy(AiManagerRegistry* const ai) : CombatStrategy(ai) {}

    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
        virtual void InitMultipliers(std::list<Multiplier*> &multipliers);
        virtual ActionNode* createAction(const char* name);

    };
}