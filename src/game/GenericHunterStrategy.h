#pragma once

#include "Strategy.h"
#include "HunterActionFactory.h"

namespace ai
{
    class GenericHunterStrategy : public Strategy
    {
    public:
        GenericHunterStrategy(PlayerbotAIFacade* const ai) : Strategy(ai) {}

    public:
        virtual void InitTriggers(std::list<Trigger*> &triggers);
        virtual ActionFactory* createActionFactory() { return new HunterActionFactory(ai); }
    };
}