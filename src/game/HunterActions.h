#pragma once

#include "GenericActions.h"

#define DEFAULT_HUNTER_NEXT_ACTIONS() \
    BEGIN_NEXT_ACTIONS(1) \
    NEXT_ACTION(0, "auto shot", 1.0f) \
    END_NEXT_ACTIONS(1)

namespace ai
{
    BEGIN_RANGED_SPELL_ACTION(CastArcaneShotAction, "arcane shot")
        DEFAULT_HUNTER_NEXT_ACTIONS()
    END_SPELL_ACTION()

    BEGIN_RANGED_SPELL_ACTION(CastConcussiveShotAction, "concussive shot")
    DEFAULT_HUNTER_NEXT_ACTIONS()
    END_SPELL_ACTION()

    BEGIN_RANGED_SPELL_ACTION(CastDistractingShotAction, "distracting shot")
    DEFAULT_HUNTER_NEXT_ACTIONS()
    END_SPELL_ACTION()

    BEGIN_RANGED_SPELL_ACTION(CastMultiShotAction, "multi-shot")
    DEFAULT_HUNTER_NEXT_ACTIONS()
    END_SPELL_ACTION()

    BEGIN_RANGED_SPELL_ACTION(CastSerpentStingAction, "serpent sting")
    DEFAULT_HUNTER_NEXT_ACTIONS()
    END_SPELL_ACTION()

    BEGIN_RANGED_SPELL_ACTION(CastScorpidStingAction, "scorpid sting")
    DEFAULT_HUNTER_NEXT_ACTIONS()
    END_SPELL_ACTION()

}