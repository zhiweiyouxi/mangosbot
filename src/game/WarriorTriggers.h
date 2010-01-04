#pragma once
#include "GenericTriggers.h"

namespace ai
{
    class HeroicStrikeAvailable : public RageAvailable
    {
    public:
        HeroicStrikeAvailable(PlayerbotAIFacade* const ai) : RageAvailable(ai, 15)  {}
    public: 
        BEGIN_NEXT_ACTIONS(1)
            NEXT_ACTION(0, "heroic strike", 20.0f)
        END_NEXT_ACTIONS(1)
        virtual const char* getName() { return "heroic strike available"; }
    };

    BUFF_TRIGGER(DefensiveStanceTrigger, "defensive stance", "defensive stance")

    DEBUFF_TRIGGER(RendDebuffTrigger, "rend", "rend")
    DEBUFF_TRIGGER(DisarmDebuffTrigger, "disarm", "disarm")
    DEBUFF_TRIGGER(SunderArmorDebuffTrigger, "sunder armor", "sunder armor")

    BEGIN_TRIGGER(WarriorLoseAggroTrigger, LoseAggroTrigger)
        BEGIN_NEXT_ACTIONS(1)
            NEXT_ACTION(0, "mocking blow", 30.0f)
        END_NEXT_ACTIONS(1)
        virtual const char* getName() { return "lose aggro"; }
    END_TRIGGER()

    class WarriorDemoralizeAttackers : public AttackerCountTrigger
    {
    public:
        WarriorDemoralizeAttackers(PlayerbotAIFacade* const ai) : AttackerCountTrigger(ai, 2)  {}
    public: 
        BEGIN_NEXT_ACTIONS(1)
            NEXT_ACTION(0, "demoralizing shout", 20.0f)
        END_NEXT_ACTIONS(1)
    };

    SPELL_AVAILABLE_TRIGGER(RevengeAvailableTrigger, "revenge", 50.0f)
}