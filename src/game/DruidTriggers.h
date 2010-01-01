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
            NEXT_ACTION(0, "maul", 2.0f)
        END_NEXT_ACTIONS(1)
        virtual const char* getName() { return "maul available"; }
    };

    class SwipeAvailable : public RageAvailable
    {
    public:
        SwipeAvailable(PlayerbotAIFacade* const ai) : RageAvailable(ai, 15)  {}
    public: 
        BEGIN_NEXT_ACTIONS(2)
            NEXT_ACTION(0, "swipe", 2.0f)
            NEXT_ACTION(1, "maul", 1.0f)
        END_NEXT_ACTIONS(2)
        virtual const char* getName() { return "swipe available"; }
    };

    BEGIN_TRIGGER(DruidLowHealthTrigger, LowHealthTrigger)
        BEGIN_NEXT_ACTIONS(2)
            NEXT_ACTION(0, "lifeblood", 6.0f)
            NEXT_ACTION(1, "rejuvenation", 5.0f)
        END_NEXT_ACTIONS(2)
        virtual const char* getName() { return "low health"; }
    END_TRIGGER()

    BEGIN_TRIGGER(DruidPartyMemberLowHealthTrigger, PartyMemberLowHealthTrigger)
        NEXT_ACTIONS("regrowth on party", 5.0f)
        virtual const char* getName() { return "party member low health"; }
    END_TRIGGER()

    BEGIN_TRIGGER(BearTankDruidLoseAggroTrigger, LoseAggroTrigger)
      BEGIN_NEXT_ACTIONS(1)
          NEXT_ACTION(0, "growl", 3.0f)
      END_NEXT_ACTIONS(1)
      virtual const char* getName() { return "lose aggro"; }
    END_TRIGGER()

    class BearTankDruidDemoralizeAttackers : public AttackerCountTrigger
    {
    public:
        BearTankDruidDemoralizeAttackers(PlayerbotAIFacade* const ai) : AttackerCountTrigger(ai, 2)  {}
    public: 
        BEGIN_NEXT_ACTIONS(1)
            NEXT_ACTION(0, "demoralizing roar", 2.0f)
        END_NEXT_ACTIONS(1)
    };
}