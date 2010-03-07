#pragma once
#include "GenericTriggers.h"

namespace ai
{
    class MaulAvailable : public RageAvailable
    {
    public:
        MaulAvailable(PlayerbotAIFacade* const ai) : RageAvailable(ai, 10)  {}
    public: 
        virtual const char* getName() { return "maul available"; }
    };

    class SwipeAvailable : public RageAvailable
    {
    public:
        SwipeAvailable(PlayerbotAIFacade* const ai) : RageAvailable(ai, 15)  {}
    public: 
        virtual const char* getName() { return "swipe available"; }
    };

    BEGIN_TRIGGER(BearTankDruidLoseAggroTrigger, LoseAggroTrigger)
      virtual const char* getName() { return "lose aggro"; }
    END_TRIGGER()

    BUFF_ON_PARTY_TRIGGER(MarkOfTheWildOnPartyTrigger, "mark of the wild", "mark of the wild on party")

    BUFF_TRIGGER(MarkOfTheWildTrigger, "mark of the wild", "mark of the wild")
    BUFF_TRIGGER(ThornsTrigger, "thorns", "thorns")


    //--------------------------------------------------------------------------------------

    DEBUFF_TRIGGER(RakeTrigger, "rake", "rake")
}