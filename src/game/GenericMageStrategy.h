#pragma once

#include "Strategy.h"

namespace ai
{
    class GenericMageStrategy : public Strategy
    {
    public:
        GenericMageStrategy(PlayerbotAIFacade* const ai) : Strategy(ai) {}
        virtual const char* getName() { return "mage"; }
    
    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
        virtual ActionNode* createAction(const char* name);
    };
}