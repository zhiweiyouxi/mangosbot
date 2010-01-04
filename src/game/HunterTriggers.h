#pragma once
#include "GenericTriggers.h"

namespace ai
{
    BEGIN_TRIGGER(HunterEnemyTooCloseTrigger, EnemyTooCloseTrigger)
        BEGIN_NEXT_ACTIONS(2)
            NEXT_ACTION(0, "flee", 50.0f)
            NEXT_ACTION(1, "concussive shot", 40.0f)
        END_NEXT_ACTIONS(2)
    END_TRIGGER()

    BEGIN_TRIGGER(HunterNoStingsActiveTrigger, Trigger)
        BEGIN_NEXT_ACTIONS(1)
            NEXT_ACTION(0, "serpent sting", 50.0f)
        END_NEXT_ACTIONS(1)
    END_TRIGGER()

    BUFF_TRIGGER(HunterAspectOfTheHawkTrigger, "aspect of the hawk", "aspect of the hawk")
    
    BEGIN_TRIGGER(HunterHasNoPetTrigger, Trigger)
        BEGIN_NEXT_ACTIONS(1)
            NEXT_ACTION(0, "call pet", 50.0f)
        END_NEXT_ACTIONS(1)
    END_TRIGGER()

    BEGIN_TRIGGER(HuntersPetDeadTrigger, Trigger)
        BEGIN_NEXT_ACTIONS(1)
            NEXT_ACTION(0, "revive pet", 50.0f)
        END_NEXT_ACTIONS(1)
    END_TRIGGER()

    BEGIN_TRIGGER(HuntersPetLowHealthTrigger, Trigger)
        BEGIN_NEXT_ACTIONS(1)
            NEXT_ACTION(0, "mend pet", 50.0f)
        END_NEXT_ACTIONS(1)
    END_TRIGGER()

}