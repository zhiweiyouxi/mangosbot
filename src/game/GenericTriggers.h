#pragma once
#include "Trigger.h"

namespace ai
{
    BEGIN_TRIGGER(EnemyTooCloseTrigger, Trigger)
    END_TRIGGER()

    BEGIN_TRIGGER(EnemyOutOfMeleeTrigger, Trigger)
        BEGIN_NEXT_ACTIONS(1)
            NEXT_ACTION(0, "melee", 1.0f)
        END_NEXT_ACTIONS(1)
    END_TRIGGER()

    BEGIN_TRIGGER(LoseAggroTrigger, Trigger)
    END_TRIGGER()

    class RageAvailable : public Trigger
    {
    public:
        RageAvailable(PlayerbotAIFacade* const ai, int amount) : Trigger(ai) 
        {
            this->amount = amount;
        }
    public: 
        virtual BOOL IsActive();

    protected:
        int amount;
    };

    class AttackerCountTrigger : public Trigger
    {
    public:
        AttackerCountTrigger(PlayerbotAIFacade* const ai, int amount) : Trigger(ai) 
        {
            this->amount = amount;
        }
    public: 
        virtual BOOL IsActive();
        virtual const char* getName() { return "attacker count"; }

    protected:
        int amount;
    };

    BEGIN_TRIGGER(LowHealthTrigger, Trigger)
    END_TRIGGER()

    BEGIN_TRIGGER(LowManaTrigger, Trigger)
    END_TRIGGER()
}