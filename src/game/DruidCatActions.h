#pragma once

#include "GenericActions.h"

namespace ai {
	class CastFeralChargeCatAction : public CastReachTargetSpellAction {
	public:
		CastFeralChargeCatAction(PlayerbotAIFacade* const ai) : CastReachTargetSpellAction(ai, "feral charge - cat", 1.5f) {}
	};

	class CastCatSpellAction : public CastSpellAction {
	public:
		CastCatSpellAction(PlayerbotAIFacade* const ai, const char* spell) : CastSpellAction(ai, spell) {}
		
		virtual NextAction** getPrerequisites() {
			return NextAction::merge( NextAction::array(0, new NextAction("cat form"), NULL), CastSpellAction::getPrerequisites());
		}
	};

	class CastCowerAction : public CastCatSpellAction {
	public:
		CastCowerAction(PlayerbotAIFacade* const ai) : CastCatSpellAction(ai, "cower") {}
	};


	class CastBerserkAction : public CastCatSpellAction {
	public:
		CastBerserkAction(PlayerbotAIFacade* const ai) : CastCatSpellAction(ai, "berserk") {}
	};

	class CastTigersFuryAction : public CastCatSpellAction {
	public:
		CastTigersFuryAction(PlayerbotAIFacade* const ai) : CastCatSpellAction(ai, "tiger's fury") {}
	};
	
	class CastRakeAction : public CastDebuffSpellAction {
	public:
		CastRakeAction(PlayerbotAIFacade* const ai) : CastDebuffSpellAction(ai, "rake") {}

		virtual NextAction** getPrerequisites() {
			return NextAction::merge( NextAction::array(0, new NextAction("reach melee"), new NextAction("cat form"), NULL), CastDebuffSpellAction::getPrerequisites());
		}
	};

	class CastCatMeleeSpellAction : public CastMeleeSpellAction {
	public:
		CastCatMeleeSpellAction(PlayerbotAIFacade* const ai, const char* spell) : CastMeleeSpellAction(ai, spell) {}

		virtual NextAction** getPrerequisites() {
			return NextAction::merge( NextAction::array(0, new NextAction("cat form"), NULL), CastMeleeSpellAction::getPrerequisites());
		}
	};

	class CastClawAction : public CastCatMeleeSpellAction {
	public:
		CastClawAction(PlayerbotAIFacade* const ai) : CastCatMeleeSpellAction(ai, "claw") {}
	};

	class CastMangleCatAction : public CastCatMeleeSpellAction {
	public:
		CastMangleCatAction(PlayerbotAIFacade* const ai) : CastCatMeleeSpellAction(ai, "mangle (cat)") {}
	};

	class CastFerociousBiteAction : public CastCatMeleeSpellAction {
	public:
		CastFerociousBiteAction(PlayerbotAIFacade* const ai) : CastCatMeleeSpellAction(ai, "ferocious bite") {}
	};


	class CastRipAction : public CastCatMeleeSpellAction {
	public:
		CastRipAction(PlayerbotAIFacade* const ai) : CastCatMeleeSpellAction(ai, "rip") {}
	};



}