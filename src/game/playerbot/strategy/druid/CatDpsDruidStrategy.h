#pragma once

#include "FeralDruidStrategy.h"

namespace ai
{
    class CatDpsDruidStrategy : public FeralDruidStrategy
    {
    public:
        CatDpsDruidStrategy(AiManagerRegistry* const ai) : FeralDruidStrategy(ai) {}

    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
        virtual void InitMultipliers(std::list<Multiplier*> &multipliers);
        virtual const char* getName() { return "cat"; }
        virtual ActionNode* createAction(const char* name);
        virtual NextAction** getDefaultActions();
    };
}