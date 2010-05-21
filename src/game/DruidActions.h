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

	class CastMarkOfTheWildAction : public CastBuffSpellAction {
	public:
		CastMarkOfTheWildAction(PlayerbotAIFacade* const ai) : CastBuffSpellAction(ai, "mark of the wild") {}
	};

	class CastMarkOfTheWildOnPartyAction : public BuffOnPartyAction {
	public:
		CastMarkOfTheWildOnPartyAction(PlayerbotAIFacade* const ai) : BuffOnPartyAction(ai, "mark of the wild") {}
		virtual const char* getName() { return "mark of the wild on party";}
	};

	class CastSurvivalInstinctsAction : public CastBuffSpellAction {
	public:
		CastSurvivalInstinctsAction(PlayerbotAIFacade* const ai) : CastBuffSpellAction(ai, "survival instincts") {}
	};

	class CastThornsAction : public CastBuffSpellAction {
	public:
		CastThornsAction(PlayerbotAIFacade* const ai) : CastBuffSpellAction(ai, "thorns") {}
	};

	class CastWrathAction : public CastRangedSpellAction 
	{ 
	public: 
		CastWrathAction(PlayerbotAIFacade* const ai) : CastRangedSpellAction(ai, "wrath") {} 
	};

	class CastMoonfireAction : public CastDebuffSpellAction 
	{ 
	public: 
		CastMoonfireAction(PlayerbotAIFacade* const ai) : CastDebuffSpellAction(ai, "moonfire") {} 
	};

	class CastInsectSwarmAction : public CastDebuffSpellAction 
	{ 
	public: 
		CastInsectSwarmAction(PlayerbotAIFacade* const ai) : CastDebuffSpellAction(ai, "insect swarm") {} 
	};

	class CastStarfireAction : public CastRangedSpellAction 
	{ 
	public: 
		CastStarfireAction(PlayerbotAIFacade* const ai) : CastRangedSpellAction(ai, "starfire") {} 
	};

	class CastEntanglingRootsAction : public CastDebuffSpellAction 
	{ 
	public: 
		CastEntanglingRootsAction(PlayerbotAIFacade* const ai) : CastDebuffSpellAction(ai, "entangling roots") {} 
	};

	class CastNaturesGraspAction : public CastBuffSpellAction 
	{ 
	public: 
		CastNaturesGraspAction(PlayerbotAIFacade* const ai) : CastBuffSpellAction(ai, "nature's grasp") {} 
	};
	
	class CastHibernateAction : public CastDebuffSpellAction 
	{ 
	public: 
		CastHibernateAction(PlayerbotAIFacade* const ai) : CastDebuffSpellAction(ai, "hibernate") {} 
	};

	class CastCurePoisonAction : public CastCureSpellAction 
	{ 
	public: 
		CastCurePoisonAction(PlayerbotAIFacade* const ai) : CastCureSpellAction(ai, "cure poison") {} 
	};

    class CastCurePoisonOnPartyAction : public CurePartyMemberAction
    {
    public:
        CastCurePoisonOnPartyAction(PlayerbotAIFacade* const ai) : CurePartyMemberAction(ai, "cure poison", DISPEL_POISON) {}
		virtual const char* getName() { return "cure poison on party";}
    };

	class CastAbolishPoisonAction : public CastCureSpellAction 
	{ 
	public: 
		CastAbolishPoisonAction(PlayerbotAIFacade* const ai) : CastCureSpellAction(ai, "abolish poison") {} 
		virtual NextAction** getAlternatives();
	};

    class CastAbolishPoisonOnPartyAction : public CurePartyMemberAction
    {
    public:
        CastAbolishPoisonOnPartyAction(PlayerbotAIFacade* const ai) : CurePartyMemberAction(ai, "abolish poison", DISPEL_POISON) {}

        virtual const char* getName() { return "abolish poison on party"; }
        virtual NextAction** getAlternatives();
    };

}