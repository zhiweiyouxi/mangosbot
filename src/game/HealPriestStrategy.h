#pragma once

#include "Strategy.h"

namespace ai
{
    class HealPriestStrategy : public CombatStrategy
    {
    public:
        HealPriestStrategy(PlayerbotAIFacade* const ai) : CombatStrategy(ai) {}

    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
        virtual void InitMultipliers(std::list<Multiplier*> &multipliers);
        virtual const char* getName() { return "heal priest"; }
        virtual ActionNode* createAction(const char* name);

    };
}