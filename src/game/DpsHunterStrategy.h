#pragma once

#include "GenericHunterStrategy.h"

namespace ai
{
    class DpsHunterStrategy : public GenericHunterStrategy
    {
    public:
        DpsHunterStrategy(PlayerbotAIFacade* const ai) : GenericHunterStrategy(ai) {}

    public:
        BEGIN_NEXT_ACTIONS(1)
            NEXT_ACTION(0, "hunter's mark", 50.0f)
        END_NEXT_ACTIONS(1)
    
    public:
        virtual void InitTriggers(std::list<Trigger*> &triggers);
        virtual void InitMultipliers(std::list<Multiplier*> &multipliers);
        virtual const char* getName() { return "dps hunter"; }
        virtual ActionNode* createAction(const char* name);
    };
}