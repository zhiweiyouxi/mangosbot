#pragma once

#include "Strategy.h"

namespace ai
{
    class HealPriestNonCombatStrategy : public CombatStrategy
    {
    public:
        HealPriestNonCombatStrategy(PlayerbotAIFacade* const ai) : CombatStrategy(ai) {}

    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
        virtual void InitMultipliers(std::list<Multiplier*> &multipliers);
        virtual const char* getName() { return "nc"; }
        virtual ActionNode* createAction(const char* name);

    };

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