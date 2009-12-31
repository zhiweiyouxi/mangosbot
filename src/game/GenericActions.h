#pragma once

#include "Action.h"

namespace ai
{
    BEGIN_ACTION(FleeAction, "flee")
    END_ACTION()

    BEGIN_ACTION(MeleeAction, "melee")
    END_ACTION()

    BEGIN_SPELL_ACTION(CastLifeBloodAction, "life blood")
        BEGIN_ALTERNATIVE_ACTIONS(1)
            ALTERNATIVE_ACTION(0, "rejuvenation", 6.0f)
        END_ALTERNATIVE_ACTIONS(1)

        virtual BOOL isUseful();
    END_SPELL_ACTION()
}