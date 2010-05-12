#pragma once

#include "GenericActions.h"
#include "DruidShapeshiftActions.h"
#include "DruidBearActions.h"
#include "DruidCatActions.h"

namespace ai
{
	class CastFaerieFireAction : public CastRangedSpellAction 
	{ 
	public: 
		CastFaerieFireAction(PlayerbotAIFacade* const ai) : CastRangedSpellAction(ai, "faerie fire") {} 
	};

  
	class CastRejuvenationAction : public CastHealingSpellAction {
	public:
		CastRejuvenationAction(PlayerbotAIFacade* const ai) : CastHealingSpellAction(ai, "rejuvenation") {}

		virtual NextAction** getPrerequisites() {
			return NextAction::merge( NextAction::array(0, new NextAction("caster form"), NULL), CastHealingSpellAction::getPrerequisites());
		}

	};

	class CastRegrowthAction : public CastHealingSpellAction {
	public:
		CastRegrowthAction(PlayerbotAIFacade* const ai) : CastHealingSpellAction(ai, "regrowth") {}

		virtual NextAction** getPrerequisites() {
			return NextAction::merge( NextAction::array(0, new NextAction("caster form"), NULL), CastHealingSpellAction::getPrerequisites());
		}

	};
   
  
    class CastRejuvenationOnPartyAction : public HealPartyMemberAction
    {
    public:
        CastRejuvenationOnPartyAction(PlayerbotAIFacade* const ai) : HealPartyMemberAction(ai, "rejuvenation") {}

        virtual const char* getName() { return "rejuvenation on party"; }
		
		virtual NextAction** getPrerequisites() {
			return NextAction::merge( NextAction::array(0, new NextAction("caster form"), NULL), HealPartyMemberAction::getPrerequisites());
		}
    };

    class CastRegrowthOnPartyAction : public HealPartyMemberAction
    {
    public:
        CastRegrowthOnPartyAction(PlayerbotAIFacade* const ai) : HealPartyMemberAction(ai, "regrowth") {}
        virtual const char* getName() { return "regrowth on party"; }
		
		virtual NextAction** getPrerequisites() {
			return NextAction::merge( NextAction::array(0, new NextAction("caster form"), NULL), HealPartyMemberAction::getPrerequisites());
		}
    };

	class CastReviveAction : public ResurrectPartyMemberAction
	{
	public:
		CastReviveAction(PlayerbotAIFacade* const ai) : ResurrectPartyMemberAction(ai, "revive") {}

		virtual NextAction** getPrerequisites() {
			return NextAction::merge( NextAction::array(0, new NextAction("caster form"), NULL), ResurrectPartyMemberAction::getPrerequisites());
		}
	};

	class CastRebirthAction : public ResurrectPartyMemberAction
	{
	public:
		CastRebirthAction(PlayerbotAIFacade* const ai) : ResurrectPartyMemberAction(ai, "rebirth") {}

		virtual NextAction** getPrerequisites() {
			return NextAction::merge( NextAction::array(0, new NextAction("caster form"), NULL), ResurrectPartyMemberAction::getPrerequisites());
		}
	};

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

	BEGIN_SPELL_ACTION(CastNaturesGraspAction, "nature's grasp")
	END_SPELL_ACTION()
	
	BEGIN_SPELL_ACTION(CastHibernateAction, "hibernate")
	END_SPELL_ACTION()
	

    //--------------------------------------------------------------------------------------



    BEGIN_SPELL_ACTION(CastCurePoisonAction, "cure poison")
    END_SPELL_ACTION()

    class CastCurePoisonOnPartyAction : public CurePartyMemberAction
    {
    public:
        CastCurePoisonOnPartyAction(PlayerbotAIFacade* const ai) : CurePartyMemberAction(ai, "cure poison", DISPEL_POISON) {}

        virtual const char* getName() { return "cure poison on party"; }
    };

    BEGIN_SPELL_ACTION(CastAbolishPoisonAction, "abolish poison")
        virtual NextAction** getAlternatives();
    END_SPELL_ACTION()

    class CastAbolishPoisonOnPartyAction : public CurePartyMemberAction
    {
    public:
        CastAbolishPoisonOnPartyAction(PlayerbotAIFacade* const ai) : CurePartyMemberAction(ai, "abolish poison", DISPEL_POISON) {}

        virtual const char* getName() { return "abolish poison on party"; }
        virtual NextAction** getAlternatives();
    };

	//-----------------------------------------------------------------------


}