#pragma once
#include "GenericTriggers.h"

namespace ai
{
    BEGIN_TRIGGER(HunterEnemyTooCloseTrigger, EnemyTooCloseTrigger)
        BEGIN_NEXT_ACTIONS(1)
        NEXT_ACTION(0, "flee", 50.0f)
        END_NEXT_ACTIONS(1)
        END_TRIGGER()
}