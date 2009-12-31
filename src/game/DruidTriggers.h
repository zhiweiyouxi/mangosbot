#pragma once
#include "GenericTriggers.h"

namespace ai
{
    BEGIN_TRIGGER(DruidEnemyTooCloseTrigger, EnemyTooCloseTrigger)
        BEGIN_NEXT_ACTIONS(2)
            NEXT_ACTION(0, "frost nova", 10.0f)
            NEXT_ACTION(1, "flee", 5.0f)
        END_NEXT_ACTIONS(2)
    END_TRIGGER()

    class MaulAvailable : public RageAvailable
    {
    public:
        MaulAvailable(PlayerbotAIFacade* const ai) : RageAvailable(ai, 10)  {}
    public: 
        BEGIN_NEXT_ACTIONS(2)
            NEXT_ACTION(0, "maul", 10.0f)
            NEXT_ACTION(1, "swipe", 1.0f)
        END_NEXT_ACTIONS(2)
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
    };
}