#pragma once

#include "Strategy.h"

namespace ai
{
    class DpsWarlockStrategy : public Strategy
    {
    public:
        DpsWarlockStrategy(PlayerbotAIFacade* const ai) : Strategy(ai) {}
        virtual const char* getName() { return "warlock"; }
    
    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
        virtual ActionNode* createAction(const char* name);
        virtual NextAction** getDefaultActions();
    };
}