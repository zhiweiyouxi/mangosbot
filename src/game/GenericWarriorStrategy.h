#pragma once

#include "Strategy.h"
#include "WarriorActionFactory.h"

namespace ai
{
    class GenericWarriorStrategy : public Strategy
    {
    public:
        GenericWarriorStrategy(PlayerbotAIFacade* const ai) : Strategy(ai) {}

    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
        virtual ActionFactory* createActionFactory() { return new WarriorActionFactory(ai); }
        virtual const char* getName() { return "warrior"; }
    };
}