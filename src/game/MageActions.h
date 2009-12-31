#pragma once

#include "Action.h"

#define ACTION_KIND_FROST 1

#define DEFAULT_MAGE_NEXT_ACTIONS() \
    BEGIN_NEXT_ACTIONS(3) \
        NEXT_ACTION(0, "frostbolt", 1.0f) \
        NEXT_ACTION(1, "fireball", 1.0f) \
        NEXT_ACTION(2, "arcane blast", 1.0f) \
    END_NEXT_ACTIONS(3)

namespace ai
{
    BEGIN_RANGED_SPELL_ACTION(CastFrostBoltAction, "frostbolt")
        DEFAULT_MAGE_NEXT_ACTIONS()
        ACTION_KIND(ACTION_KIND_FROST)
    END_SPELL_ACTION()

    BEGIN_RANGED_SPELL_ACTION(CastIceLanceAction, "ice lance")
        DEFAULT_MAGE_NEXT_ACTIONS()
        ACTION_KIND(ACTION_KIND_FROST)
    END_SPELL_ACTION()

    // --------------------------------------------------------------------------------

    BEGIN_RANGED_SPELL_ACTION(CastFireBallAction, "fireball")
        DEFAULT_MAGE_NEXT_ACTIONS()
    END_SPELL_ACTION()

    BEGIN_RANGED_SPELL_ACTION(CastFireBlastAction, "fire blast")
        DEFAULT_MAGE_NEXT_ACTIONS()
    END_SPELL_ACTION()
    
    BEGIN_RANGED_SPELL_ACTION(CastPyroblastAction, "pyroblast")
        DEFAULT_MAGE_NEXT_ACTIONS()
    END_SPELL_ACTION()

    BEGIN_RANGED_SPELL_ACTION(CastScorchAction, "scorch")
        DEFAULT_MAGE_NEXT_ACTIONS()
    END_SPELL_ACTION()
    
    // --------------------------------------------------------------------------------

    BEGIN_SPELL_ACTION(CastFrostNovaAction, "frost nova")
        BEGIN_NEXT_ACTIONS(2) \
            NEXT_ACTION(0, "frostbolt", 1.0f)
            NEXT_ACTION(1, "ice lance", 0.5f)
        END_NEXT_ACTIONS(2)
        ACTION_KIND(ACTION_KIND_FROST)
    END_SPELL_ACTION()

    BEGIN_SPELL_ACTION(CastBlastWaveAction, "blast wave")
        DEFAULT_MAGE_NEXT_ACTIONS()
    END_SPELL_ACTION()

    BEGIN_SPELL_ACTION(CastArcaneExplosionAction, "arcane explosion")
        DEFAULT_MAGE_NEXT_ACTIONS()
    END_SPELL_ACTION()
    
    // --------------------------------------------------------------------------------

    BEGIN_RANGED_SPELL_ACTION(CastArcaneBlastAction, "arcane blast")
        DEFAULT_MAGE_NEXT_ACTIONS()
    END_SPELL_ACTION()
    
    // --------------------------------------------------------------------------------

    BEGIN_RANGED_SPELL_ACTION(CastCounterspellAction, "counterspell")
        DEFAULT_MAGE_NEXT_ACTIONS()
    END_SPELL_ACTION()


}