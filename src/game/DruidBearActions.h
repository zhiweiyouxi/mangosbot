#pragma once

#include "GenericActions.h"

namespace ai {
	class CastFeralChargeBearAction : public CastReachTargetSpellAction {
	public:
		CastFeralChargeBearAction(PlayerbotAIFacade* const ai) : CastReachTargetSpellAction(ai, "feral charge - bear", 1.5f) {}
	};

	class CastGrowlAction : public CastRangedSpellAction {
	public:
		CastGrowlAction(PlayerbotAIFacade* const ai) : CastRangedSpellAction(ai, "growl") {}
	};

	class CastMaulAction : public CastMeleeSpellAction {
	public:
		CastMaulAction(PlayerbotAIFacade* const ai) : CastMeleeSpellAction(ai, "maul") {}
	};

	class CastBashAction : public CastMeleeSpellAction {
	public:
		CastBashAction(PlayerbotAIFacade* const ai) : CastMeleeSpellAction(ai, "bash") {}
	};

	class CastSwipeAction : public CastMeleeSpellAction {
	public:
		CastSwipeAction(PlayerbotAIFacade* const ai) : CastMeleeSpellAction(ai, "swipe") {}
	};

	class CastDemoralizingRoarAction : public CastMeleeSpellAction {
	public:
		CastDemoralizingRoarAction(PlayerbotAIFacade* const ai) : CastMeleeSpellAction(ai, "demoralizing roar") {}
	};

	class CastMangleBearAction : public CastMeleeSpellAction {
	public:
		CastMangleBearAction(PlayerbotAIFacade* const ai) : CastMeleeSpellAction(ai, "mangle (bear)") {}
	};
	
}