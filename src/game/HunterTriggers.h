#pragma once
#include "GenericTriggers.h"

namespace ai
{
    BEGIN_TRIGGER(HunterNoStingsActiveTrigger, Trigger)
    END_TRIGGER()

    BUFF_TRIGGER(HunterAspectOfTheHawkTrigger, "aspect of the hawk", "aspect of the hawk")
    BUFF_TRIGGER(HunterAspectOfThePackTrigger, "aspect of the pack", "aspect of the pack")

    BEGIN_TRIGGER(HunterHasNoPetTrigger, Trigger)
    END_TRIGGER()

    BEGIN_TRIGGER(HuntersPetDeadTrigger, Trigger)
    END_TRIGGER()

    BEGIN_TRIGGER(HuntersPetLowHealthTrigger, Trigger)
    END_TRIGGER()

}