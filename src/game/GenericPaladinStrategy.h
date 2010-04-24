#pragma once

#include "Strategy.h"
#include "PaladinActionFactory.h"

namespace ai
{
    class GenericPaladinStrategy : public Strategy
    {
    public:
        GenericPaladinStrategy(PlayerbotAIFacade* const ai) : Strategy(ai) {}

    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
        virtual ActionFactory* createActionFactory() { return new PaladinActionFactory(ai); }
        virtual const char* getName() { return "paladin"; }
        ActionNode* createAction(const char* name);
    };
}