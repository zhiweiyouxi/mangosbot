#pragma once

#include "Strategy.h"
#include "HunterActionFactory.h"

namespace ai
{
    class GenericHunterStrategy : public CombatStrategy
    {
    public:
        GenericHunterStrategy(PlayerbotAIFacade* const ai) : CombatStrategy(ai) {}

    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
        virtual ActionFactory* createActionFactory() { return new HunterActionFactory(ai); }
        virtual const char* getName() { return "hunter"; }
        virtual ActionNode* createAction(const char* name);
    };

    class HunterBoostStrategy : public Strategy
    {
    public:
        HunterBoostStrategy(PlayerbotAIFacade* const ai) : Strategy(ai) {}

    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
        virtual const char* getName() { return "hunter boost"; }
    };
}

