#pragma once
#include "GenericTriggers.h"

namespace ai
{
    BEGIN_TRIGGER(BearTankDruidLoseAggroTrigger, LoseAggroTrigger)
      virtual const char* getName() { return "lose aggro"; }
    END_TRIGGER()

    BUFF_ON_PARTY_TRIGGER(MarkOfTheWildOnPartyTrigger, "mark of the wild", "mark of the wild on party")

    BUFF_TRIGGER(MarkOfTheWildTrigger, "mark of the wild", "mark of the wild")
    BUFF_TRIGGER(ThornsTrigger, "thorns", "thorns")


    //--------------------------------------------------------------------------------------

    DEBUFF_TRIGGER(RakeTrigger, "rake", "rake")
}