#pragma once

#include "GenericActions.h"

namespace ai
{
    BEGIN_RANGED_SPELL_ACTION(CastFaerieFireAction, "faerie fire")
    END_SPELL_ACTION()

    BEGIN_SPELL_ACTION(CastBearFormAction, "bear form")
        virtual BOOL isPossible();
        virtual BOOL isUseful();
    END_SPELL_ACTION()

    BEGIN_SPELL_ACTION(CastDireBearFormAction, "dire bear form")
        virtual BOOL isPossible();
        virtual NextAction** getAlternatives();
        virtual BOOL isUseful();
    END_SPELL_ACTION()

    BEGIN_MELEE_SPELL_ACTION(CastMaulAction, "maul")
        virtual BOOL isPossible();
    END_SPELL_ACTION()

    BEGIN_MELEE_SPELL_ACTION(CastSwipeAction, "swipe")
        virtual BOOL isPossible();
    END_SPELL_ACTION()

    BEGIN_ACTION(CastCasterFormAction, "caster form")
        virtual BOOL isUseful();
    END_SPELL_ACTION()

    BEGIN_SPELL_ACTION(CastRejuvenationAction, "rejuvenation")
        virtual BOOL isPossible();
        virtual BOOL isUseful();
        virtual NextAction** getPrerequisites();
    END_SPELL_ACTION()

    BEGIN_SPELL_ACTION(CastRegrowthAction, "regrowth")
        virtual BOOL isUseful();
    virtual NextAction** getPrerequisites();
    END_SPELL_ACTION()

    class CastRejuvenationOnPartyAction : public HealPartyMemberAction
    {
    public:
        CastRejuvenationOnPartyAction(PlayerbotAIFacade* const ai) : HealPartyMemberAction(ai, "rejuvenation") {}

        virtual const char* getName() { return "rejuvenation on party"; }
        virtual NextAction** getPrerequisites();
    };

    class CastRegrowthOnPartyAction : public HealPartyMemberAction
    {
    public:
        CastRegrowthOnPartyAction(PlayerbotAIFacade* const ai) : HealPartyMemberAction(ai, "regrowth") {}
        virtual const char* getName() { return "regrowth on party"; }
        virtual NextAction** getPrerequisites();
    };

    BEGIN_RANGED_SPELL_ACTION(CastGrowlAction, "growl")
    END_SPELL_ACTION()

    BEGIN_MELEE_SPELL_ACTION(CastDemoralizingRoarAction, "demoralizing roar")
    END_SPELL_ACTION()

    BEGIN_SPELL_ACTION(CastMarkOfTheWildAction, "mark of the wild")
    END_SPELL_ACTION()

    BEGIN_BUFF_ON_PARTY_ACTION(CastMarkOfTheWildOnPartyAction, "mark of the wild")
        virtual const char* getName() { return "mark of the wild on party";}
    END_ACTION()

    BEGIN_SPELL_ACTION(CastThornsAction, "thorns")
    END_SPELL_ACTION()

    //--------------------------------------------------------------------------------------
    BEGIN_SPELL_ACTION(CastCatFormAction, "cat form")
        virtual BOOL isPossible();
        virtual BOOL isUseful();
    END_SPELL_ACTION()

    BEGIN_DEBUFF_ACTION(CastRakeAction, "rake")
        virtual NextAction** getPrerequisites();
    END_SPELL_ACTION()

    BEGIN_MELEE_SPELL_ACTION(CastClawAction, "claw") // main nuke
        virtual NextAction** getPrerequisites();
    END_SPELL_ACTION()

    BEGIN_MELEE_SPELL_ACTION(CastFerociousBiteAction, "ferocious bite")
        virtual NextAction** getPrerequisites();
    END_SPELL_ACTION()

    BEGIN_MELEE_SPELL_ACTION(CastRipAction, "rip")
        virtual NextAction** getPrerequisites();
    END_SPELL_ACTION()


    BEGIN_SPELL_ACTION(CastCurePoisonAction, "cure poison")
        virtual NextAction** getPrerequisites();
    END_SPELL_ACTION()

    class CastCurePoisonOnPartyAction : public CurePartyMemberAction
    {
    public:
        CastCurePoisonOnPartyAction(PlayerbotAIFacade* const ai) : CurePartyMemberAction(ai, "cure poison", DISPEL_POISON) {}

        virtual const char* getName() { return "cure poison on party"; }
        virtual NextAction** getPrerequisites();
    };

}