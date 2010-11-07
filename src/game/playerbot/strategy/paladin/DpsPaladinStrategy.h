#pragma once

#include "GenericPaladinStrategy.h"

namespace ai
{
    class DpsPaladinStrategy : public GenericPaladinStrategy
    {
    public:
        DpsPaladinStrategy(AiManagerRegistry* const ai) : GenericPaladinStrategy(ai) {}
    
    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
        virtual void InitMultipliers(std::list<Multiplier*> &multipliers);
        virtual const char* getName() { return "dps"; }
        virtual ActionNode* createAction(const char* name);
        virtual NextAction** getDefaultActions();

    };
}