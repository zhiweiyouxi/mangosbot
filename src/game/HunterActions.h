#pragma once

#include "GenericActions.h"

#define DEFAULT_HUNTER_NEXT_ACTIONS() \
    BEGIN_NEXT_ACTIONS(2) \
        NEXT_ACTION(0, "arcane shot", 11.0f) \
        NEXT_ACTION(1, "auto shot", 10.0f) \
    END_NEXT_ACTIONS(2)

namespace ai
{
    BEGIN_RANGED_SPELL_ACTION(CastHuntersMarkAction, "hunter's mark")
        DEFAULT_HUNTER_NEXT_ACTIONS()
    END_SPELL_ACTION()

    BEGIN_RANGED_SPELL_ACTION(CastAutoShotAction, "auto shot")
        DEFAULT_HUNTER_NEXT_ACTIONS()
    END_SPELL_ACTION()

    BEGIN_RANGED_SPELL_ACTION(CastArcaneShotAction, "arcane shot")
        DEFAULT_HUNTER_NEXT_ACTIONS()
        virtual BOOL isUseful();
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
    virtual BOOL isUseful();
    END_SPELL_ACTION()

    BEGIN_RANGED_SPELL_ACTION(CastScorpidStingAction, "scorpid sting")
    DEFAULT_HUNTER_NEXT_ACTIONS()
    END_SPELL_ACTION()

    BEGIN_SPELL_ACTION(CastAspectOfTheHawkAction, "aspect of the hawk")
    END_SPELL_ACTION()
}