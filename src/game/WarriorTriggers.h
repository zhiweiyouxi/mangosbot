#pragma once
#include "GenericTriggers.h"

namespace ai
{
    BUFF_TRIGGER(BattleShoutTrigger, "battle shout", "battle shout")

    DEBUFF_TRIGGER(RendDebuffTrigger, "rend", "rend")
    DEBUFF_TRIGGER(DisarmDebuffTrigger, "disarm", "disarm")
    DEBUFF_TRIGGER(SunderArmorDebuffTrigger, "sunder armor", "sunder armor")

	class RevengeAvailableTrigger : public SpellCanBeCastTrigger
	{
	public:
		RevengeAvailableTrigger(PlayerbotAIFacade* const ai) : SpellCanBeCastTrigger(ai, "revenge") {}
	};

    class BloodrageDebuffTrigger : public DebuffTrigger {
    public:
        BloodrageDebuffTrigger(PlayerbotAIFacade* const ai) : DebuffTrigger(ai, "bloodrage") {}
        virtual bool IsActive() {
            return DebuffTrigger::IsActive() && 
				statsManager->GetHealthPercent(targetManager->GetSelf()) >= 75 && 
				statsManager->GetRage(targetManager->GetSelf()) < 20;
        }
    };
}