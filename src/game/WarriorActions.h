#pragma once
#include "PlayerbotAIFacade.h"
#include "GenericActions.h"

namespace ai
{
    // battle
    class CastBattleMeleeSpellAction : public CastMeleeSpellAction {
    public:
        CastBattleMeleeSpellAction(PlayerbotAIFacade* const ai, const char* spell) : CastMeleeSpellAction(ai, spell) {}
        virtual NextAction** getPrerequisites() {
            return NextAction::merge( NextAction::array(0, new NextAction("battle stance"), NULL), CastMeleeSpellAction::getPrerequisites());
        }
    };

    // defensive
    class CastDefensiveMeleeSpellAction : public CastMeleeSpellAction {
    public:
        CastDefensiveMeleeSpellAction(PlayerbotAIFacade* const ai, const char* spell) : CastMeleeSpellAction(ai, spell) {}
        virtual NextAction** getPrerequisites() {
            return NextAction::merge( NextAction::array(0, new NextAction("defensive stance"), NULL), CastMeleeSpellAction::getPrerequisites());
        }
    };

    // all
    class CastHeroicStrikeAction : public CastMeleeSpellAction {
    public:
        CastHeroicStrikeAction(PlayerbotAIFacade* const ai) : CastMeleeSpellAction(ai, "heroic strike") {}
    };

    // all
    class CastCleaveAction : public CastMeleeSpellAction {
    public:
        CastCleaveAction(PlayerbotAIFacade* const ai) : CastMeleeSpellAction(ai, "cleave") {}
    };

    // battle, berserker
    class CastMockingBlowAction : public CastMeleeSpellAction {
    public:
        CastMockingBlowAction(PlayerbotAIFacade* const ai) : CastMeleeSpellAction(ai, "mocking blow") {}
    };

    class CastBloodthirstAction : public CastMeleeSpellAction {
    public:
        CastBloodthirstAction(PlayerbotAIFacade* const ai) : CastMeleeSpellAction(ai, "bloodthirst") {}
    };

    // battle, berserker
    class CastExecuteAction : public CastMeleeSpellAction {
    public:
        CastExecuteAction(PlayerbotAIFacade* const ai) : CastMeleeSpellAction(ai, "execute") {}
    };

    // battle
    class CastOverpowerAction : public CastBattleMeleeSpellAction {
    public:
        CastOverpowerAction(PlayerbotAIFacade* const ai) : CastBattleMeleeSpellAction(ai, "overpower") {}
    };

    // battle, berserker
    class CastHamstringAction : public CastMeleeSpellAction {
    public:
        CastHamstringAction(PlayerbotAIFacade* const ai) : CastMeleeSpellAction(ai, "hamstring") {}
    };

    // defensive
    class CastTauntAction : public CastSpellAction {
    public:
        CastTauntAction(PlayerbotAIFacade* const ai) : CastSpellAction(ai, "taunt") {}
        virtual NextAction** getPrerequisites() {
            return NextAction::merge( NextAction::array(0, new NextAction("defensive stance"), NULL), CastSpellAction::getPrerequisites());
        }
    };

    // defensive
    class CastShieldBlockAction : public CastBuffSpellAction {
    public:
        CastShieldBlockAction(PlayerbotAIFacade* const ai) : CastBuffSpellAction(ai, "shield block") {}
		virtual NextAction** getPrerequisites() {
			return NextAction::merge( NextAction::array(0, new NextAction("defensive stance"), NULL), CastSpellAction::getPrerequisites());
		}
    };

    // defensive
    class CastShieldWallAction : public CastDefensiveMeleeSpellAction {
    public:
        CastShieldWallAction(PlayerbotAIFacade* const ai) : CastDefensiveMeleeSpellAction(ai, "shield wall") {}
    };

    class CastBloodrageAction : public CastBuffSpellAction {
    public:
        CastBloodrageAction(PlayerbotAIFacade* const ai) : CastBuffSpellAction(ai, "bloodrage") {}
    };

    // defensive
    class CastDevastateAction : public CastDefensiveMeleeSpellAction {
    public:
        CastDevastateAction(PlayerbotAIFacade* const ai) : CastDefensiveMeleeSpellAction(ai, "devastate") {}
    };

    // all
    class CastSlamAction : public CastMeleeSpellAction {
    public:
        CastSlamAction(PlayerbotAIFacade* const ai) : CastMeleeSpellAction(ai, "slam") {}
    };

	// all
	class CastShieldSlamAction : public CastMeleeSpellAction {
	public:
		CastShieldSlamAction(PlayerbotAIFacade* const ai) : CastMeleeSpellAction(ai, "shield slam") {}
	};

    // after dodge
    BEGIN_MELEE_SPELL_ACTION(CastRevengeAction, "revenge")
        virtual NextAction** getPrerequisites();
    END_SPELL_ACTION()


    //debuffs
    BEGIN_DEBUFF_ACTION(CastRendAction, "rend")
        virtual NextAction** getPrerequisites();
    END_SPELL_ACTION()

    BEGIN_DEBUFF_ACTION(CastDisarmAction, "disarm")
        virtual NextAction** getPrerequisites();
    END_SPELL_ACTION()

    BEGIN_DEBUFF_ACTION(CastSunderArmorAction, "sunder armor") // 5 times
        virtual NextAction** getPrerequisites();
    END_SPELL_ACTION()

    BEGIN_MELEE_SPELL_ACTION(CastDemoralizingShoutAction, "demoralizing shout")
    END_SPELL_ACTION()

    BEGIN_MELEE_SPELL_ACTION(CastChallengingShoutAction, "challenging shout")
    END_SPELL_ACTION()

    // stuns
    BEGIN_MELEE_SPELL_ACTION(CastShieldBashAction, "shield bash")
    END_SPELL_ACTION()

    BEGIN_MELEE_SPELL_ACTION(CastIntimidatingShoutAction, "intimidating shout")
    END_SPELL_ACTION()

    BEGIN_MELEE_SPELL_ACTION(CastThunderClapAction, "thunder clap")
    END_SPELL_ACTION()

    // buffs
    BEGIN_SPELL_ACTION(CastBattleShoutAction, "battle shout")
    END_SPELL_ACTION()

	class CastDefensiveStanceAction : public CastBuffSpellAction {
	public:
		CastDefensiveStanceAction(PlayerbotAIFacade* const ai) : CastBuffSpellAction(ai, "defensive stance") {}
	};

	class CastBattleStanceAction : public CastBuffSpellAction {
	public:
		CastBattleStanceAction(PlayerbotAIFacade* const ai) : CastBuffSpellAction(ai, "battle stance") {}
	};

    BEGIN_RANGED_SPELL_ACTION(CastChargeAction, "charge")
    END_SPELL_ACTION()

	class CastDeathWishAction : public CastBuffSpellAction {
	public:
		CastDeathWishAction(PlayerbotAIFacade* const ai) : CastBuffSpellAction(ai, "death wish") {}
	};

	class CastBerserkerRageAction : public CastBuffSpellAction {
	public:
		CastBerserkerRageAction(PlayerbotAIFacade* const ai) : CastBuffSpellAction(ai, "berserker rage") {}
	};

	class CastLastStandAction : public CastBuffSpellAction {
	public:
		CastLastStandAction(PlayerbotAIFacade* const ai) : CastBuffSpellAction(ai, "last stand") {}
	};

	// defensive
	class CastShockwaveAction : public CastDefensiveMeleeSpellAction {
	public:
		CastShockwaveAction(PlayerbotAIFacade* const ai) : CastDefensiveMeleeSpellAction(ai, "shockwave") {}
	};

	// defensive
	class CastConcussionBlowAction : public CastDefensiveMeleeSpellAction {
	public:
		CastConcussionBlowAction(PlayerbotAIFacade* const ai) : CastDefensiveMeleeSpellAction(ai, "concussion blow") {}
	};

	BEGIN_MELEE_SPELL_ACTION(CastVictoryRushAction, "victory rush")
	END_SPELL_ACTION()   
}