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
}