#pragma once

#include "GenericMageStrategy.h"

namespace ai
{
    class MagePullStrategy : public RangedCombatStrategy
    {
    public:
        MagePullStrategy(AiManagerRegistry* const ai) : RangedCombatStrategy(ai) {}

    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
        virtual void InitMultipliers(std::list<Multiplier*> &multipliers);
        virtual const char* getName() { return "pull"; }
        virtual ActionNode* createAction(const char* name);
        virtual NextAction** getDefaultActions();

    };
}