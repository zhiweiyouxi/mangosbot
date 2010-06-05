#pragma once

#include "../Strategy.h"

namespace ai
{
    class ShamanNonCombatStrategy : public CombatStrategy
    {
    public:
        ShamanNonCombatStrategy(AiManagerRegistry* const ai) : CombatStrategy(ai) {}

    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
        virtual void InitMultipliers(std::list<Multiplier*> &multipliers);
        virtual const char* getName() { return "nc"; }
        virtual ActionNode* createAction(const char* name);

    };
}