#pragma once

#include "GenericDruidStrategy.h"
#include "DruidActionFactory.h"

namespace ai
{
    class FeralDruidStrategy : public GenericDruidStrategy
    {
    public:
        FeralDruidStrategy(PlayerbotAIFacade* const ai) : GenericDruidStrategy(ai) {}

    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
        virtual ActionFactory* createActionFactory() { return new DruidActionFactory(ai); }
        virtual ActionNode* createAction(const char* name);
        virtual const char* getName() { return "feral druid"; }
    };

}