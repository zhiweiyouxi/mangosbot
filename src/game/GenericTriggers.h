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

#include "RangeTriggers.h"
#include "HealthTriggers.h"
#include "CureTriggers.h"

namespace ai
{

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

    class BoostTrigger : public BuffTrigger
    {
    public:
        BoostTrigger(PlayerbotAIFacade* const ai, const char* spell, float balance) : BuffTrigger(ai, spell) 
        {
            this->balance = balance;
        }
    public: 
        virtual BOOL IsActive();

    protected:
        float balance;
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

    class AndTrigger : public Trigger
    {
    public:
        AndTrigger(PlayerbotAIFacade* const ai, Trigger* ls, Trigger* rs) : Trigger(ai) 
        {
            this->ls = ls;
            this->rs = rs;
        }
        virtual ~AndTrigger() 
        {
            delete ls;
            delete rs;
        }
    public: 
        virtual BOOL IsActive();
        virtual const char* getName();

    protected:
        Trigger* ls;
        Trigger* rs;
    };

    class SnareTargetTrigger : public Trigger
    {
    public:
        SnareTargetTrigger(PlayerbotAIFacade* const ai, const char* aura) : Trigger(ai) 
        {
            this->aura = aura;
        }
    public: 
        virtual BOOL IsActive();
        virtual const char* getName() { return "target is moving"; }

    protected:
        const char* aura;
    };
    BEGIN_TRIGGER(LowManaTrigger, Trigger)
        virtual const char* getName() { return "low mana"; }
    END_TRIGGER()

        BEGIN_TRIGGER(PanicTrigger, Trigger)
        virtual const char* getName() { return "panic"; }
    END_TRIGGER()

}