#pragma once

#include "Strategy.h"
#include "GenericShamanStrategy.h"

namespace ai
{
    class HealShamanStrategy : public GenericShamanStrategy
    {
    public:
        HealShamanStrategy(AiManagerRegistry* const ai) : GenericShamanStrategy(ai) {}

    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
        virtual NextAction** HealShamanStrategy::getDefaultActions();
        virtual const char* getName() { return "heal"; }
        virtual ActionNode* createAction(const char* name);

    };
}