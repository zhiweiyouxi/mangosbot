#pragma once
#include "Trigger.h"

#define BUFF_TRIGGER(clazz, spell, action) \
    class clazz : public BuffTrigger \
    { \
    public: \
        clazz(PlayerbotAIFacade* const ai) : BuffTrigger(ai, spell) {} \
    };

#define BUFF_ON_PARTY_TRIGGER(clazz, spell, action) \
    class clazz : public BuffOnPartyTrigger \
    { \
    public: \
        clazz(PlayerbotAIFacade* const ai) : BuffOnPartyTrigger(ai, spell) {}  \
    };

#define DEBUFF_TRIGGER(clazz, spell, action) \
    class clazz : public DebuffTrigger \
    { \
    public: \
        clazz(PlayerbotAIFacade* const ai) : DebuffTrigger(ai, spell) {} \
    };

#define SPELL_AVAILABLE_TRIGGER(clazz, spell, relevance) \
class clazz : public SpellAvailableTrigger \
    { \
    public: \
        clazz(PlayerbotAIFacade* const ai) : SpellAvailableTrigger(ai, spell) {} \
    };

namespace ai
{
    BEGIN_TRIGGER(EnemyTooCloseTrigger, Trigger)
        virtual const char* getName() { return "too close"; }
    END_TRIGGER()

    BEGIN_TRIGGER(EnemyOutOfMeleeTrigger, Trigger)
        virtual const char* getName() { return "out of melee range"; }
    END_TRIGGER()

    BEGIN_TRIGGER(EnemyOutOfSpellRangeTrigger, Trigger)
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

    class ComboPointsAvailable : public Trigger
    {
    public:
        ComboPointsAvailable(PlayerbotAIFacade* const ai, int amount) : Trigger(ai) 
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

    class LowHealthTrigger : public Trigger
    {
    public:
        LowHealthTrigger(PlayerbotAIFacade* const ai, float value = EAT_DRINK_PERCENT) : Trigger(ai) 
        {
            this->value = value;
        }
    public: 
        virtual BOOL IsActive();
        virtual const char* getName() { return "low health"; }

    protected:
        float value;
    };

    class PartyMemberLowHealthTrigger : public LowHealthTrigger
    {
    public:
        PartyMemberLowHealthTrigger(PlayerbotAIFacade* const ai, float value = EAT_DRINK_PERCENT) : LowHealthTrigger(ai, value) 
        {
            this->value = value;
        }
    public: 
        virtual BOOL IsActive();
        virtual const char* getName() { return "party member low health"; }

    protected:
        float value;
    };

    BEGIN_TRIGGER(LowManaTrigger, Trigger)
        virtual const char* getName() { return "low mana"; }
    END_TRIGGER()

    BEGIN_TRIGGER(PanicTrigger, Trigger)
        virtual const char* getName() { return "panic"; }
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

    BEGIN_TRIGGER(LootAvailableTrigger, Trigger)
    END_TRIGGER()

    class RandomTrigger : public Trigger
    {
    public:
        RandomTrigger(PlayerbotAIFacade* const ai, int probability) : Trigger(ai) 
        {
            this->probability = probability;
        }
    public: 
        virtual BOOL IsActive();
        virtual const char* getName() { return "random"; }

    protected:
        int probability;
    };
}