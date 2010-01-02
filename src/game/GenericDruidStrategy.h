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
        virtual void InitTriggers(std::list<Trigger*> &triggers);
        virtual ActionFactory* createActionFactory() { return new DruidActionFactory(ai); }
        virtual const char* getName() { return "generic druid"; }
    };
}