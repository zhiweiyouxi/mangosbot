#pragma once

#include "GenericHunterStrategy.h"

namespace ai
{
    class DpsHunterStrategy : public GenericHunterStrategy
    {
    public:
        DpsHunterStrategy(PlayerbotAIFacade* const ai) : GenericHunterStrategy(ai) {}

    public:
        BEGIN_NEXT_ACTIONS(2)
            NEXT_ACTION(0, "concussive shot", 60.0f)
            NEXT_ACTION(1, "auto shot", 10.0f)
        END_NEXT_ACTIONS(2)
    
    public:
        virtual void InitTriggers(std::list<Trigger*> &triggers);
        virtual void InitMultipliers(std::list<Multiplier*> &multipliers);
        virtual const char* getName() { return "dps hunter"; }
    };
}