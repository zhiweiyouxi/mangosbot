#pragma once

#include "Strategy.h"
#include "HealPriestNonCombatStrategy.h"

namespace ai
{
    class HealPriestStrategy : public HealPriestNonCombatStrategy
    {
    public:
        HealPriestStrategy(PlayerbotAIFacade* const ai) : HealPriestNonCombatStrategy(ai) {}

    public:
        virtual NextAction** HealPriestStrategy::getDefaultActions();
        virtual const char* getName() { return "heal"; }
        virtual ActionNode* createAction(const char* name);

    };
}