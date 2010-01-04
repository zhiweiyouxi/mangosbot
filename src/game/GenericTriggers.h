#pragma once
#include "Trigger.h"

#define BUFF_TRIGGER(clazz, spell, action) \
    class clazz : public BuffTrigger \
    { \
    public: \
        clazz(PlayerbotAIFacade* const ai) : BuffTrigger(ai, spell) {} \
        BEGIN_NEXT_ACTIONS(1) \
            NEXT_ACTION(0, action, 1.0f) \
        END_NEXT_ACTIONS(1) \
    };

#define BUFF_ON_PARTY_TRIGGER(clazz, spell, action) \
    class clazz : public BuffOnPartyTrigger \
    { \
    public: \
        clazz(PlayerbotAIFacade* const ai) : BuffOnPartyTrigger(ai, spell) {}  \
        BEGIN_NEXT_ACTIONS(1) \
            NEXT_ACTION(0, action, 1.0f) \
        END_NEXT_ACTIONS(1) \
    };

#define DEBUFF_TRIGGER(clazz, spell, action) \
    class clazz : public DebuffTrigger \
    { \
    public: \
        clazz(PlayerbotAIFacade* const ai) : DebuffTrigger(ai, spell) {} \
        BEGIN_NEXT_ACTIONS(1) \
            NEXT_ACTION(0, action, 1.0f) \
        END_NEXT_ACTIONS(1) \
    };

#define SPELL_AVAILABLE_TRIGGER(clazz, spell, relevance) \
class clazz : public SpellAvailableTrigger \
    { \
    public: \
        clazz(PlayerbotAIFacade* const ai) : SpellAvailableTrigger(ai, spell) {} \
        BEGIN_NEXT_ACTIONS(1) \
            NEXT_ACTION(0, spell, relevance) \
        END_NEXT_ACTIONS(1) \
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
        BEGIN_NEXT_ACTIONS(1)
            NEXT_ACTION(0, "eat", 9.0f)
        END_NEXT_ACTIONS(1)
    END_TRIGGER()

    BEGIN_TRIGGER(PartyMemberLowHealthTrigger, Trigger)
        virtual const char* getName() { return "party member low health"; }
    END_TRIGGER()

    BEGIN_TRIGGER(LowManaTrigger, Trigger)
        virtual const char* getName() { return "low mana"; }
        BEGIN_NEXT_ACTIONS(1)
            NEXT_ACTION(0, "drink", 9.0f)
        END_NEXT_ACTIONS(1)
    END_TRIGGER()

    BEGIN_TRIGGER(PanicTrigger, Trigger)
        virtual const char* getName() { return "panic"; }
        BEGIN_NEXT_ACTIONS(1)
            NEXT_ACTION(0, "panic potion", 100.0f)
        END_NEXT_ACTIONS(1)
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

    BEGIN_TRIGGER(NoAttackersTrigger, Trigger)
        BEGIN_NEXT_ACTIONS(1)
            NEXT_ACTION(0, "attack least threat", 9.0f)
        END_NEXT_ACTIONS(1)
    END_TRIGGER()

    class DebuffTrigger : public BuffTrigger
    {
    public:
        DebuffTrigger(PlayerbotAIFacade* const ai, const char* spell) : BuffTrigger(ai, spell) {}
    public: 
        virtual BOOL IsActive();
    };

    class SpellAvailableTrigger : public BuffTrigger
    {
    public:
        SpellAvailableTrigger(PlayerbotAIFacade* const ai, const char* spell) : BuffTrigger(ai, spell) {}
    public: 
        virtual BOOL IsActive();
    };

    class TankNoAttackersTrigger : public NoAttackersTrigger
    {
    public:
        TankNoAttackersTrigger(PlayerbotAIFacade* const ai) : NoAttackersTrigger(ai)  {}
    public: 
        BEGIN_NEXT_ACTIONS(1)
            NEXT_ACTION(0, "attack bigger threat", 9.0f)
            END_NEXT_ACTIONS(1)
    };
}