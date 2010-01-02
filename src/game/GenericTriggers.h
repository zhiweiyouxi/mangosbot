#pragma once
#include "Trigger.h"

#define BUFF_TRIGGER(clazz, spell, action) \
class clazz : public BuffTrigger \
    { \
    public: \
        clazz(PlayerbotAIFacade* const ai) : BuffTrigger(ai, spell) {} \
        NEXT_ACTIONS(action, 1.0f) \
    };

#define BUFF_ON_PARTY_TRIGGER(clazz, spell, action) \
class clazz : public BuffOnPartyTrigger \
    { \
    public: \
        clazz(PlayerbotAIFacade* const ai) : BuffOnPartyTrigger(ai, spell) {}  \
        NEXT_ACTIONS(action, 1.0f) \
    };

namespace ai
{
    BEGIN_TRIGGER(EnemyTooCloseTrigger, Trigger)
        virtual const char* getName() { return "too close"; }
    END_TRIGGER()

    BEGIN_TRIGGER(EnemyOutOfMeleeTrigger, Trigger)
        BEGIN_NEXT_ACTIONS(1)
            NEXT_ACTION(0, "melee", 1.0f)
        END_NEXT_ACTIONS(1)
        virtual const char* getName() { return "out of melee range"; }
    END_TRIGGER()

    BEGIN_TRIGGER(EnemyOutOfSpellRangeTrigger, Trigger)
        BEGIN_NEXT_ACTIONS(1)
            NEXT_ACTION(0, "reach spell", 2.0f)
        END_NEXT_ACTIONS(1)
        virtual const char* getName() { return "out of spell range"; }
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
        virtual const char* getName() { return "low health"; }
        NEXT_ACTIONS("eat", 9.0f)
    END_TRIGGER()

    BEGIN_TRIGGER(PartyMemberLowHealthTrigger, Trigger)
        virtual const char* getName() { return "party member low health"; }
    END_TRIGGER()

    BEGIN_TRIGGER(LowManaTrigger, Trigger)
        virtual const char* getName() { return "low mana"; }
        NEXT_ACTIONS("drink", 9.0f)
    END_TRIGGER()

    BEGIN_TRIGGER(PanicTrigger, Trigger)
        virtual const char* getName() { return "panic"; }
        NEXT_ACTIONS("panic potion", 100.0f)
    END_TRIGGER()

    class BuffTrigger : public Trigger
    {
    public:
        BuffTrigger(PlayerbotAIFacade* const ai, const char* spell) : Trigger(ai) 
        {
            this->spell = spell;
        }
    public: 
        virtual BOOL IsActive();
        virtual const char* getName() { return spell; }

    protected:
        const char* spell;
    };

    class BuffOnPartyTrigger : public BuffTrigger
    {
    public:
        BuffOnPartyTrigger(PlayerbotAIFacade* const ai, const char* spell) : BuffTrigger(ai, spell) {}
    public: 
       virtual BOOL IsActive();
    };
}