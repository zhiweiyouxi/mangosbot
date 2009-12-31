#pragma once

#include "GenericDruidStrategy.h"

namespace ai
{
    class BearTankDruidStrategy : public GenericDruidStrategy
    {
    public:
        BearTankDruidStrategy(PlayerbotAIFacade* const ai) : GenericDruidStrategy(ai) {}

    public:
        BEGIN_NEXT_ACTIONS(2)
            NEXT_ACTION(0, "faerie fire", 2.0f)
            NEXT_ACTION(1, "melee", 1.0f)
        END_NEXT_ACTIONS(2)
    
    public:
        virtual void InitTriggers(std::list<Trigger*> &triggers);
        virtual void InitMultipliers(std::list<Multiplier*> &multipliers);
    };
}