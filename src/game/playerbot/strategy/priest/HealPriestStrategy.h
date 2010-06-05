#pragma once

#include "GenericPriestStrategy.h"

namespace ai
{
    class HealPriestStrategy : public GenericPriestStrategy
    {
    public:
        HealPriestStrategy(AiManagerRegistry* const ai) : GenericPriestStrategy(ai) {}

    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
        virtual NextAction** HealPriestStrategy::getDefaultActions();
        virtual const char* getName() { return "heal"; }
        virtual ActionNode* createAction(const char* name);

    };
}