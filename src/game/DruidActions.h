#pragma once

#include "GenericActions.h"

namespace ai
{
    BEGIN_RANGED_SPELL_ACTION(CastFaerieFireAction, "faerie fire")
    END_SPELL_ACTION()

    BEGIN_SPELL_ACTION(CastBearFormAction, "bear form")
        virtual bool isPossible();
        virtual bool isUseful();
    END_SPELL_ACTION()

    BEGIN_SPELL_ACTION(CastDireBearFormAction, "dire bear form")
        virtual bool isPossible();
        virtual NextAction** getAlternatives();
        virtual bool isUseful();
    END_SPELL_ACTION()

    BEGIN_MELEE_SPELL_ACTION(CastMaulAction, "maul")
    END_SPELL_ACTION()

    BEGIN_MELEE_SPELL_ACTION(CastBashAction, "bash")
    END_SPELL_ACTION()

    BEGIN_MELEE_SPELL_ACTION(CastSwipeAction, "swipe")
    END_SPELL_ACTION()

    BEGIN_SPELL_ACTION(CastCasterFormAction, "caster form")
        virtual bool isUseful();
        virtual bool isPossible() { return TRUE; }
        virtual bool ExecuteResult();
    END_SPELL_ACTION()

    BEGIN_SPELL_ACTION(CastRejuvenationAction, "rejuvenation")
        virtual bool isPossible();
        virtual bool isUseful();
        virtual NextAction** getPrerequisites();
    END_SPELL_ACTION()

    BEGIN_SPELL_ACTION(CastRegrowthAction, "regrowth")
        virtual bool isUseful();
    virtual NextAction** getPrerequisites();
    END_SPELL_ACTION()

    class CastFeralChargeBearAction : public CastReachTargetSpellAction {
    public:
        CastFeralChargeBearAction(PlayerbotAIFacade* const ai) : CastReachTargetSpellAction(ai, "feral charge - bear", 1.5f) {}
    };

    class CastFeralChargeCatAction : public CastReachTargetSpellAction {
    public:
        CastFeralChargeCatAction(PlayerbotAIFacade* const ai) : CastReachTargetSpellAction(ai, "feral charge - cat", 1.5f) {}
    };
    
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
    END_SPELL_ACTION()

    BEGIN_SPELL_ACTION(CastSurvivalInstinctsAction, "survival instincts")
    END_SPELL_ACTION()

    BEGIN_SPELL_ACTION(CastThornsAction, "thorns")
    END_SPELL_ACTION()

	BEGIN_SPELL_ACTION(CastWrathAction, "wrath")
	END_SPELL_ACTION()

	BEGIN_SPELL_ACTION(CastMoonfireAction, "moonfire")
	END_SPELL_ACTION()

	BEGIN_SPELL_ACTION(CastInsectSwarmAction, "insect swarm")
	END_SPELL_ACTION()

	BEGIN_SPELL_ACTION(CastStarfireAction, "starfire")
	END_SPELL_ACTION()

	BEGIN_SPELL_ACTION(CastEntanglingRootsAction, "entangling roots")
	END_SPELL_ACTION()
	

    //--------------------------------------------------------------------------------------
    BEGIN_SPELL_ACTION(CastCatFormAction, "cat form")
        virtual bool isPossible();
        virtual bool isUseful();
    END_SPELL_ACTION()

    BEGIN_SPELL_ACTION(CastCowerAction, "cower")
        virtual NextAction** getPrerequisites();
    END_SPELL_ACTION()
        
    BEGIN_DEBUFF_ACTION(CastRakeAction, "rake")
        virtual NextAction** getPrerequisites();
    END_SPELL_ACTION()

    BEGIN_MELEE_SPELL_ACTION(CastClawAction, "claw") // main nuke
        virtual NextAction** getPrerequisites();
    END_SPELL_ACTION()

    BEGIN_MELEE_SPELL_ACTION(CastMangleCatAction, "mangle (cat)") // main nuke
        virtual NextAction** getPrerequisites();
    END_SPELL_ACTION()

    BEGIN_MELEE_SPELL_ACTION(CastMangleBearAction, "mangle (bear)") // main nuke
    END_SPELL_ACTION()

    BEGIN_MELEE_SPELL_ACTION(CastFerociousBiteAction, "ferocious bite")
        virtual NextAction** getPrerequisites();
    END_SPELL_ACTION()

    BEGIN_MELEE_SPELL_ACTION(CastRipAction, "rip")
        virtual NextAction** getPrerequisites();
    END_SPELL_ACTION()

    BEGIN_SPELL_ACTION(CastBerserkAction, "berserk")
        virtual NextAction** getPrerequisites();
    END_SPELL_ACTION()

    BEGIN_SPELL_ACTION(CastTigersFuryAction, "tiger's fury")
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

    BEGIN_SPELL_ACTION(CastAbolishPoisonAction, "abolish poison")
        virtual NextAction** getPrerequisites();
        virtual NextAction** getAlternatives();
    END_SPELL_ACTION()

    class CastAbolishPoisonOnPartyAction : public CurePartyMemberAction
    {
    public:
        CastAbolishPoisonOnPartyAction(PlayerbotAIFacade* const ai) : CurePartyMemberAction(ai, "abolish poison", DISPEL_POISON) {}

        virtual const char* getName() { return "abolish poison on party"; }
        virtual NextAction** getPrerequisites();
        virtual NextAction** getAlternatives();
    };

	//-----------------------------------------------------------------------

	BEGIN_SPELL_ACTION(CastMoonkinFormAction, "moonkin form")
		virtual bool isPossible();
		virtual bool isUseful();
	END_SPELL_ACTION()

}