#pragma once

#include "Strategy.h"
#include "MageActionFactory.h"

namespace ai
{
    class GenericMageStrategy : public Strategy
    {
    public:
        GenericMageStrategy(PlayerbotAIFacade* const ai) : Strategy(ai) {}

    public:
        virtual void InitTriggers(std::list<Trigger*> &triggers);
        virtual ActionFactory* createActionFactory() { return new MageActionFactory(ai); }
    };
}