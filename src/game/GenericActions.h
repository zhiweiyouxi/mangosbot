#pragma once

#include "Action.h"

namespace ai
{

    BEGIN_ACTION(FleeAction, "flee")
    END_ACTION()

    BEGIN_ACTION(MeleeAction, "melee")
    END_ACTION()

    BEGIN_ACTION(ReachSpellAction, "reach spell")
        virtual BOOL isUseful();
    END_ACTION()

    BEGIN_SPELL_ACTION(CastLifeBloodAction, "lifeblood")
        BEGIN_ALTERNATIVE_ACTIONS(1)
            ALTERNATIVE_ACTION(0, "regrowth")
        END_ALTERNATIVE_ACTIONS(1)

        virtual BOOL isUseful();
    END_SPELL_ACTION()

    BEGIN_ACTION(UseHealingPotion, "healing potion")
        ALTERNATIVE_ACTIONS("mana potion")
        virtual BOOL isAvailable();
    END_ACTION()

    BEGIN_ACTION(UseManaPotion, "mana potion")
        ALTERNATIVE_ACTIONS("flee")
        virtual BOOL isAvailable();
    END_ACTION()

    BEGIN_ACTION(UsePanicPotion, "panic potion")
        ALTERNATIVE_ACTIONS("healing potion")
        virtual BOOL isAvailable();
    END_ACTION()
}