#pragma once

#include "Action.h"

namespace ai
{
    BEGIN_ACTION(FleeAction, "flee")
    END_ACTION()

    BEGIN_ACTION(MeleeAction, "melee")
    END_ACTION()

    BEGIN_SPELL_ACTION(CastLifeBloodAction, "life blood")
    END_SPELL_ACTION()
}