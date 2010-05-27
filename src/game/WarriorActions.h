#pragma once
#include "GenericActions.h"

namespace ai
{
    // battle
    class CastBattleMeleeSpellAction : public CastMeleeSpellAction {
    public:
        CastBattleMeleeSpellAction(AiManagerRegistry* const ai, const char* spell) : CastMeleeSpellAction(ai, spell) {}
        virtual NextAction** getPrerequisites() {
            return NextAction::merge( NextAction::array(0, new NextAction("battle stance"), NULL), CastMeleeSpellAction::getPrerequisites());
        }
    };

    // defensive
    class CastDefensiveMeleeSpellAction : public CastMeleeSpellAction {
    public:
        CastDefensiveMeleeSpellAction(AiManagerRegistry* const ai, const char* spell) : CastMeleeSpellAction(ai, spell) {}
        virtual NextAction** getPrerequisites() {
            return NextAction::merge( NextAction::array(0, new NextAction("defensive stance"), NULL), CastMeleeSpellAction::getPrerequisites());
        }
    };

    // all
    class CastHeroicStrikeAction : public CastMeleeSpellAction {
    public:
        CastHeroicStrikeAction(AiManagerRegistry* const ai) : CastMeleeSpellAction(ai, "heroic strike") {}
    };

    // all
    class CastCleaveAction : public CastMeleeSpellAction {
    public:
        CastCleaveAction(AiManagerRegistry* const ai) : CastMeleeSpellAction(ai, "cleave") {}
    };

    // battle, berserker
    class CastMockingBlowAction : public CastMeleeSpellAction {
    public:
        CastMockingBlowAction(AiManagerRegistry* const ai) : CastMeleeSpellAction(ai, "mocking blow") {}
    };

    class CastBloodthirstAction : public CastMeleeSpellAction {
    public:
        CastBloodthirstAction(AiManagerRegistry* const ai) : CastMeleeSpellAction(ai, "bloodthirst") {}
    };

    // battle, berserker
    class CastExecuteAction : public CastMeleeSpellAction {
    public:
        CastExecuteAction(AiManagerRegistry* const ai) : CastMeleeSpellAction(ai, "execute") {}
    };

    // battle
    class CastOverpowerAction : public CastBattleMeleeSpellAction {
    public:
        CastOverpowerAction(AiManagerRegistry* const ai) : CastBattleMeleeSpellAction(ai, "overpower") {}
    };

    // battle, berserker
    class CastHamstringAction : public CastMeleeSpellAction {
    public:
        CastHamstringAction(AiManagerRegistry* const ai) : CastMeleeSpellAction(ai, "hamstring") {}
    };

    // defensive
    class CastTauntAction : public CastSpellAction {
    public:
        CastTauntAction(AiManagerRegistry* const ai) : CastSpellAction(ai, "taunt") {}
        virtual NextAction** getPrerequisites() {
            return NextAction::merge( NextAction::array(0, new NextAction("defensive stance"), NULL), CastSpellAction::getPrerequisites());
        }
    };

    // defensive
    class CastShieldBlockAction : public CastBuffSpellAction {
    public:
        CastShieldBlockAction(AiManagerRegistry* const ai) : CastBuffSpellAction(ai, "shield block") {}
		virtual NextAction** getPrerequisites() {
			return NextAction::merge( NextAction::array(0, new NextAction("defensive stance"), NULL), CastSpellAction::getPrerequisites());
		}
    };

    // defensive
    class CastShieldWallAction : public CastDefensiveMeleeSpellAction {
    public:
        CastShieldWallAction(AiManagerRegistry* const ai) : CastDefensiveMeleeSpellAction(ai, "shield wall") {}
    };

    class CastBloodrageAction : public CastBuffSpellAction {
    public:
        CastBloodrageAction(AiManagerRegistry* const ai) : CastBuffSpellAction(ai, "bloodrage") {}
    };

    // defensive
    class CastDevastateAction : public CastDefensiveMeleeSpellAction {
    public:
        CastDevastateAction(AiManagerRegistry* const ai) : CastDefensiveMeleeSpellAction(ai, "devastate") {}
    };

    // all
    class CastSlamAction : public CastMeleeSpellAction {
    public:
        CastSlamAction(AiManagerRegistry* const ai) : CastMeleeSpellAction(ai, "slam") {}
    };

	// all
	class CastShieldSlamAction : public CastMeleeSpellAction {
	public:
		CastShieldSlamAction(AiManagerRegistry* const ai) : CastMeleeSpellAction(ai, "shield slam") {}
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
	class CastBattleShoutAction : public CastBuffSpellAction {
	public:
		CastBattleShoutAction(AiManagerRegistry* const ai) : CastBuffSpellAction(ai, "battle shout") {}
	};

	class CastDefensiveStanceAction : public CastBuffSpellAction {
	public:
		CastDefensiveStanceAction(AiManagerRegistry* const ai) : CastBuffSpellAction(ai, "defensive stance") {}
	};

	class CastBattleStanceAction : public CastBuffSpellAction {
	public:
		CastBattleStanceAction(AiManagerRegistry* const ai) : CastBuffSpellAction(ai, "battle stance") {}
	};

    BEGIN_RANGED_SPELL_ACTION(CastChargeAction, "charge")
    END_SPELL_ACTION()

	class CastDeathWishAction : public CastBuffSpellAction {
	public:
		CastDeathWishAction(AiManagerRegistry* const ai) : CastBuffSpellAction(ai, "death wish") {}
	};

	class CastBerserkerRageAction : public CastBuffSpellAction {
	public:
		CastBerserkerRageAction(AiManagerRegistry* const ai) : CastBuffSpellAction(ai, "berserker rage") {}
	};

	class CastLastStandAction : public CastBuffSpellAction {
	public:
		CastLastStandAction(AiManagerRegistry* const ai) : CastBuffSpellAction(ai, "last stand") {}
	};

	// defensive
	class CastShockwaveAction : public CastDefensiveMeleeSpellAction {
	public:
		CastShockwaveAction(AiManagerRegistry* const ai) : CastDefensiveMeleeSpellAction(ai, "shockwave") {}
	};

	// defensive
	class CastConcussionBlowAction : public CastDefensiveMeleeSpellAction {
	public:
		CastConcussionBlowAction(AiManagerRegistry* const ai) : CastDefensiveMeleeSpellAction(ai, "concussion blow") {}
	};

	BEGIN_MELEE_SPELL_ACTION(CastVictoryRushAction, "victory rush")
	END_SPELL_ACTION()   
}