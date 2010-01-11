#pragma once

#include "GenericDruidStrategy.h"

namespace ai
{
    class CatDpsDruidStrategy : public GenericDruidStrategy
    {
    public:
        CatDpsDruidStrategy(PlayerbotAIFacade* const ai) : GenericDruidStrategy(ai) {}

    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
        virtual void InitMultipliers(std::list<Multiplier*> &multipliers);
        virtual const char* getName() { return "dps"; }
        virtual ActionNode* createAction(const char* name);
        virtual NextAction** getDefaultActions();
    };
}