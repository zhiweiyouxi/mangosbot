#pragma once

#include "GenericMageStrategy.h"

namespace ai
{
    class FrostMageStrategy : public GenericMageStrategy
    {
    public:
        FrostMageStrategy(PlayerbotAIFacade* const ai) : GenericMageStrategy(ai) {}

    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
        virtual void InitMultipliers(std::list<Multiplier*> &multipliers);
        virtual const char* getName() { return "frost mage"; }
        virtual ActionNode* createAction(const char* name);
        virtual NextAction** getDefaultActions();

    };
}