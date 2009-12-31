#pragma once

#include "Action.h"

#define DEFAULT_DRUID_NEXT_ACTIONS() \
    BEGIN_NEXT_ACTIONS(1) \
    NEXT_ACTION(0, "melee", 1.0f) \
    END_NEXT_ACTIONS(1)

namespace ai
{
    BEGIN_SPELL_ACTION(CastFaerieFireAction, "faerie fire")
        BEGIN_NEXT_ACTIONS(3)
            NEXT_ACTION(0, "melee", 1.0f)
            NEXT_ACTION(1, "dire bear form", 1.2f)
            NEXT_ACTION(2, "bear form", 1.1f)
        END_NEXT_ACTIONS(3)
    END_SPELL_ACTION()

    BEGIN_SPELL_ACTION(CastBearFormAction, "bear form")
        DEFAULT_DRUID_NEXT_ACTIONS()
        virtual BOOL isAvailable();
    END_SPELL_ACTION()

    BEGIN_SPELL_ACTION(CastDireBearFormAction, "dire bear form")
        DEFAULT_DRUID_NEXT_ACTIONS()
        virtual BOOL isAvailable();
    END_SPELL_ACTION()

    BEGIN_SPELL_ACTION(CastMaulAction, "maul")
        DEFAULT_DRUID_NEXT_ACTIONS()
    END_SPELL_ACTION()

    BEGIN_SPELL_ACTION(CastSwipeAction, "swipe")
        DEFAULT_DRUID_NEXT_ACTIONS()
    END_SPELL_ACTION()

    BEGIN_SPELL_ACTION(CastCasterFormAction, "caster form")
    END_SPELL_ACTION()

    BEGIN_SPELL_ACTION(CastRejuvenationAction, "rejuvenation")
        virtual BOOL isAvailable();
    END_SPELL_ACTION()

    BEGIN_SPELL_ACTION(CastRegrowthAction, "regrowth")
        DEFAULT_DRUID_NEXT_ACTIONS()
    END_SPELL_ACTION()

    BEGIN_SPELL_ACTION(CastGrowlAction, "growl")
        DEFAULT_DRUID_NEXT_ACTIONS()
    END_SPELL_ACTION()
}