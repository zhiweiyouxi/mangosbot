#pragma once

#include "GenericDruidStrategy.h"

namespace ai
{
    class BearTankDruidStrategy : public GenericDruidStrategy
    {
    public:
        BearTankDruidStrategy(PlayerbotAIFacade* const ai) : GenericDruidStrategy(ai) {}
    
    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
        virtual void InitMultipliers(std::list<Multiplier*> &multipliers);
        virtual const char* getName() { return "bear"; }
        virtual ActionNode* createAction(const char* name);
        virtual NextAction** getDefaultActions();
    };
}