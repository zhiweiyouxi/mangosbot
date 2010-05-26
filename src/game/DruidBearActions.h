#pragma once

#include "GenericActions.h"

namespace ai {
	class CastFeralChargeBearAction : public CastReachTargetSpellAction {
	public:
		CastFeralChargeBearAction(AiManagerRegistry* const ai) : CastReachTargetSpellAction(ai, "feral charge - bear", 1.5f) {}
	};

	class CastGrowlAction : public CastSpellAction {
	public:
		CastGrowlAction(AiManagerRegistry* const ai) : CastSpellAction(ai, "growl") {}
	};

	class CastMaulAction : public CastMeleeSpellAction {
	public:
		CastMaulAction(AiManagerRegistry* const ai) : CastMeleeSpellAction(ai, "maul") {}
	};

	class CastBashAction : public CastMeleeSpellAction {
	public:
		CastBashAction(AiManagerRegistry* const ai) : CastMeleeSpellAction(ai, "bash") {}
	};

	class CastSwipeAction : public CastMeleeSpellAction {
	public:
		CastSwipeAction(AiManagerRegistry* const ai) : CastMeleeSpellAction(ai, "swipe") {}
	};

	class CastDemoralizingRoarAction : public CastMeleeSpellAction {
	public:
		CastDemoralizingRoarAction(AiManagerRegistry* const ai) : CastMeleeSpellAction(ai, "demoralizing roar") {}
	};

	class CastMangleBearAction : public CastMeleeSpellAction {
	public:
		CastMangleBearAction(AiManagerRegistry* const ai) : CastMeleeSpellAction(ai, "mangle (bear)") {}
	};
	
}