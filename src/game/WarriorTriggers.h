#pragma once
#include "GenericTriggers.h"

namespace ai
{
    class HeroicStrikeAvailable : public RageAvailable
    {
    public:
        HeroicStrikeAvailable(PlayerbotAIFacade* const ai) : RageAvailable(ai, 15)  {}
    public: 
        virtual const char* getName() { return "heroic strike available"; }
    };

    BUFF_TRIGGER(DefensiveStanceTrigger, "defensive stance", "defensive stance")

    DEBUFF_TRIGGER(RendDebuffTrigger, "rend", "rend")
    DEBUFF_TRIGGER(DisarmDebuffTrigger, "disarm", "disarm")
    DEBUFF_TRIGGER(SunderArmorDebuffTrigger, "sunder armor", "sunder armor")

    SPELL_AVAILABLE_TRIGGER(RevengeAvailableTrigger, "revenge", 50.0f)
}