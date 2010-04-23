#pragma once

#include "Strategy.h"
#include "DruidActionFactory.h"

namespace ai
{
    class GenericDruidStrategy : public CombatStrategy
    {
    public:
        GenericDruidStrategy(PlayerbotAIFacade* const ai) : CombatStrategy(ai) {}

    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
        virtual ActionFactory* createActionFactory() { return new DruidActionFactory(ai); }
        virtual ActionNode* createAction(const char* name);
        virtual const char* getName() { return "druid"; }
    };

    class DruidBoostStrategy : public Strategy
    {
    public:
        DruidBoostStrategy(PlayerbotAIFacade* const ai) : Strategy(ai) {}

    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
        virtual const char* getName() { return "druid boost"; }
    };
}