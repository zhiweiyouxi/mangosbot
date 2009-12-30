#pragma once

#include "Action.h"

#define DEFAULT_DRUID_NEXT_ACTIONS() \
    BEGIN_NEXT_ACTIONS(1) \
    NEXT_ACTION(0, "melee", 1.0f) \
    END_NEXT_ACTIONS(1)

namespace ai
{
    BEGIN_SPELL_ACTION(CastFaerieFireBoltAction, "faerie fire")
        DEFAULT_DRUID_NEXT_ACTIONS()
    END_SPELL_ACTION()


}