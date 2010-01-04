#pragma once

#include "GenericActions.h"

#define DEFAULT_DRUID_NEXT_ACTIONS() \
    BEGIN_NEXT_ACTIONS(1) \
    NEXT_ACTION(0, "melee", 10.0f) \
    END_NEXT_ACTIONS(1)

namespace ai
{
    BEGIN_RANGED_SPELL_ACTION(CastFaerieFireAction, "faerie fire")
        BEGIN_NEXT_ACTIONS(2)
            NEXT_ACTION(0, "melee", 10.0f)
            NEXT_ACTION(1, "dire bear form", 15.0f)
        END_NEXT_ACTIONS(2)
    END_SPELL_ACTION()

    BEGIN_SPELL_ACTION(CastBearFormAction, "bear form")
        DEFAULT_DRUID_NEXT_ACTIONS()
        virtual BOOL isAvailable();
    END_SPELL_ACTION()

    BEGIN_SPELL_ACTION(CastDireBearFormAction, "dire bear form")
        DEFAULT_DRUID_NEXT_ACTIONS()
        ALTERNATIVE_ACTIONS("bear form")
        virtual BOOL isAvailable();
    END_SPELL_ACTION()

    BEGIN_SPELL_ACTION(CastMaulAction, "maul")
        DEFAULT_DRUID_NEXT_ACTIONS()
        virtual BOOL isAvailable();
        ALTERNATIVE_ACTIONS("melee")
    END_SPELL_ACTION()

    BEGIN_SPELL_ACTION(CastSwipeAction, "swipe")
        DEFAULT_DRUID_NEXT_ACTIONS()
        virtual BOOL isAvailable();
        ALTERNATIVE_ACTIONS("melee")
    END_SPELL_ACTION()

    BEGIN_ACTION(CastCasterFormAction, "caster form")
        virtual BOOL isUseful();
    END_SPELL_ACTION()

    BEGIN_SPELL_ACTION(CastRejuvenationAction, "rejuvenation")
        virtual BOOL isAvailable();
        virtual BOOL isUseful();
        PREREQUISITE_ACTIONS("caster form")
    END_SPELL_ACTION()

    BEGIN_SPELL_ACTION(CastRegrowthAction, "regrowth")
        DEFAULT_DRUID_NEXT_ACTIONS()
        virtual BOOL isUseful();
        PREREQUISITE_ACTIONS("caster form")
    END_SPELL_ACTION()

    class CastRejuvenationOnPartyAction : public HealPartyMemberAction
    {
    public:
        CastRejuvenationOnPartyAction(PlayerbotAIFacade* const ai) : HealPartyMemberAction(ai, "rejuvenation") {}
        PREREQUISITE_ACTIONS("caster form")

        virtual const char* getName() { return "rejuvenation on party"; }
    };

    class CastRegrowthOnPartyAction : public HealPartyMemberAction
    {
    public:
        CastRegrowthOnPartyAction(PlayerbotAIFacade* const ai) : HealPartyMemberAction(ai, "regrowth") {}
        BEGIN_PREREQUISITE_ACTIONS(2)
            PREREQUISITE_ACTION(0, "caster form")
            PREREQUISITE_ACTION(1, "rejuvenation on party")
        END_PREREQUISITE_ACTIONS(2)
        virtual const char* getName() { return "regrowth on party"; }
    };

    BEGIN_SPELL_ACTION(CastGrowlAction, "growl")
        DEFAULT_DRUID_NEXT_ACTIONS()
        BEGIN_PREREQUISITE_ACTIONS(2)
            PREREQUISITE_ACTION(0, "dire bear form")
            PREREQUISITE_ACTION(1, "reach spell")
        END_PREREQUISITE_ACTIONS(2)
        ALTERNATIVE_ACTIONS("faerie fire");
    END_SPELL_ACTION()

    BEGIN_SPELL_ACTION(CastDemoralizingRoarAction, "demoralizing roar")
        DEFAULT_DRUID_NEXT_ACTIONS()
        PREREQUISITE_ACTIONS("dire bear form")
    END_SPELL_ACTION()

    class DruidMeleeAction : public MeleeAction
    {
    public:
        DruidMeleeAction(PlayerbotAIFacade* const ai) : MeleeAction(ai) {}
        PREREQUISITE_ACTIONS("dire bear form")
        virtual BOOL isUseful() { return TRUE; }
    };

    BEGIN_SPELL_ACTION(CastMarkOfTheWildAction, "mark of the wild")
        PREREQUISITE_ACTIONS("caster form")
    END_SPELL_ACTION()

    BEGIN_BUFF_ON_PARTY_ACTION(CastMarkOfTheWildOnPartyAction, "mark of the wild")
        PREREQUISITE_ACTIONS("caster form")
        virtual const char* getName() { return "mark of the wild on party";}
    END_ACTION()

    BEGIN_SPELL_ACTION(CastThornsAction, "thorns")
        PREREQUISITE_ACTIONS("caster form")
    END_SPELL_ACTION()
}