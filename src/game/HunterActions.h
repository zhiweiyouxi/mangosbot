#pragma once

#include "Action.h"

#define DEFAULT_HUNTER_NEXT_ACTIONS() \
    BEGIN_NEXT_ACTIONS(3) \
    NEXT_ACTION(0, "frostbolt", 1.0f) \
    NEXT_ACTION(1, "fireball", 1.0f) \
    NEXT_ACTION(2, "arcane blast", 1.0f) \
    END_NEXT_ACTIONS(3)

namespace ai
{
/*    BEGIN_SPELL_ACTION(CastFrostBoltAction, "frostbolt")
        DEFAULT_MAGE_NEXT_ACTIONS()
        ACTION_KIND(ACTION_KIND_FROST)
        END_SPELL_ACTION()
*/

}