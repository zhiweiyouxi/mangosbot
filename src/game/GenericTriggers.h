#pragma once
#include "Trigger.h"

namespace ai
{
    BEGIN_TRIGGER(EnemyTooCloseTrigger, Trigger)
    END_TRIGGER()

    BEGIN_TRIGGER(EnemyOutOfMeleeTrigger, Trigger)
        BEGIN_NEXT_ACTIONS(1)
            NEXT_ACTION(0, "melee", 1.0f)
        END_NEXT_ACTIONS(1)
    END_TRIGGER()
}