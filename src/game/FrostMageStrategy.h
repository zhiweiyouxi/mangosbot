#pragma once

#include "GenericMageStrategy.h"

namespace ai
{
    class FrostMageStrategy : public GenericMageStrategy
    {
    public:
        FrostMageStrategy(PlayerbotAIFacade* const ai) : GenericMageStrategy(ai) {}

    public:
        BEGIN_NEXT_ACTIONS(1)
            NEXT_ACTION(0, "frostbolt", 1.0f)
        END_NEXT_ACTIONS(1)

        virtual void InitMultipliers(std::list<Multiplier*> &multipliers);
        virtual const char* getName() { return "frost mage"; }
    };
}