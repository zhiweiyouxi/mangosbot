#pragma once
#include "GenericTriggers.h"

namespace ai
{
    class MaulAvailable : public RageAvailable
    {
    public:
        MaulAvailable(PlayerbotAIFacade* const ai) : RageAvailable(ai, 10)  {}
    public: 
        BEGIN_NEXT_ACTIONS(1)
            NEXT_ACTION(0, "maul", 10.0f)
        END_NEXT_ACTIONS(1)
        virtual const char* getName() { return "maul available"; }
    };

    class SwipeAvailable : public RageAvailable
    {
    public:
        SwipeAvailable(PlayerbotAIFacade* const ai) : RageAvailable(ai, 15)  {}
    public: 
        BEGIN_NEXT_ACTIONS(2)
            NEXT_ACTION(0, "swipe", 10.0f)
            NEXT_ACTION(1, "maul", 1.0f)
        END_NEXT_ACTIONS(2)
        virtual const char* getName() { return "swipe available"; }
    };

    BEGIN_TRIGGER(DruidLowHealthTrigger, LowHealthTrigger)
        BEGIN_NEXT_ACTIONS(2)
            NEXT_ACTION(0, "life blood", 6.0f)
            NEXT_ACTION(1, "regrowth", 5.0f)
        END_NEXT_ACTIONS(2)
        virtual const char* getName() { return "low health"; }
  END_TRIGGER()
}