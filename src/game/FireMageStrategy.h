#pragma once

#include "GenericMageStrategy.h"

namespace ai
{
    class FireMageStrategy : public GenericMageStrategy
    {
    public:
        FireMageStrategy(AiManagerRegistry* const ai) : GenericMageStrategy(ai) {}

    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
        virtual void InitMultipliers(std::list<Multiplier*> &multipliers);
        virtual const char* getName() { return "fire"; }
        virtual ActionNode* createAction(const char* name);
        virtual NextAction** getDefaultActions();

    };
}