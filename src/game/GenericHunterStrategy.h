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
        virtual void InitTriggers(std::list<Trigger*> &triggers);
        virtual ActionFactory* createActionFactory() { return new HunterActionFactory(ai); }
        virtual const char* getName() { return "hunter"; }
        virtual ActionNode* createAction(const char* name);
    };
}

