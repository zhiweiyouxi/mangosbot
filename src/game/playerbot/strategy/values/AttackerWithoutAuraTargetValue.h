#pragma once
#include "../Value.h"

namespace ai
{
    class AttackerWithoutAuraTargetValue : public CalculatedValue<Unit*>, public Qualified
	{
	public:
        AttackerWithoutAuraTargetValue(PlayerbotAI* ai) :
            CalculatedValue<Unit*>(ai, "attacker without aura") {}

    protected:
        virtual Unit* Calculate();
	};
}
