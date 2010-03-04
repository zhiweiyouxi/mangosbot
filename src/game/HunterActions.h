#pragma once

#include "GenericActions.h"

namespace ai
{
    BEGIN_RANGED_SPELL_ACTION(CastHuntersMarkAction, "hunter's mark")
    END_SPELL_ACTION()

    BEGIN_RANGED_SPELL_ACTION(CastAutoShotAction, "auto shot")
    END_SPELL_ACTION()

    BEGIN_RANGED_SPELL_ACTION(CastArcaneShotAction, "arcane shot")
        virtual BOOL isUseful();
    END_SPELL_ACTION()

    BEGIN_RANGED_SPELL_ACTION(CastConcussiveShotAction, "concussive shot")
    END_SPELL_ACTION()

    BEGIN_RANGED_SPELL_ACTION(CastDistractingShotAction, "distracting shot")
    END_SPELL_ACTION()

    BEGIN_RANGED_SPELL_ACTION(CastMultiShotAction, "multi-shot")
    END_SPELL_ACTION()

    BEGIN_RANGED_SPELL_ACTION(CastSerpentStingAction, "serpent sting")
    virtual BOOL isUseful();
    END_SPELL_ACTION()

    BEGIN_RANGED_SPELL_ACTION(CastScorpidStingAction, "scorpid sting")
    END_SPELL_ACTION()

    BEGIN_SPELL_ACTION(CastAspectOfTheHawkAction, "aspect of the hawk")
    END_SPELL_ACTION()

    BEGIN_SPELL_ACTION(CastCallPetAction, "call pet")
    END_SPELL_ACTION()

    BEGIN_SPELL_ACTION(CastMendPetAction, "mend pet")
        virtual BOOL isUseful();
    END_SPELL_ACTION()

    BEGIN_SPELL_ACTION(CastRevivePetAction, "revive pet")
    END_SPELL_ACTION()

    BEGIN_SPELL_ACTION(CastRapidFireAction, "rapid fire")
    END_SPELL_ACTION()

    BEGIN_SPELL_ACTION(CastReadynessAction, "readyness")
    END_SPELL_ACTION()
}