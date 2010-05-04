#pragma once
#include "GenericTriggers.h"

namespace ai
{
    BUFF_TRIGGER(BattleShoutTrigger, "battle shout", "battle shout")

    DEBUFF_TRIGGER(RendDebuffTrigger, "rend", "rend")
    DEBUFF_TRIGGER(DisarmDebuffTrigger, "disarm", "disarm")
    DEBUFF_TRIGGER(SunderArmorDebuffTrigger, "sunder armor", "sunder armor")

    SPELL_AVAILABLE_TRIGGER(RevengeAvailableTrigger, "revenge", 50.0f)

    class BloodrageDebuffTrigger : public DebuffTrigger {
    public:
        BloodrageDebuffTrigger(PlayerbotAIFacade* const ai) : DebuffTrigger(ai, "bloodrage") {}
        virtual bool IsActive() {
            return DebuffTrigger::IsActive() && ai->GetHealthPercent() >= 75 && ai->GetRage() < 20;
        }
    };
}